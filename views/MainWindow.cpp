#include "MainWindow.h"

#include <QApplication>
#include <QSplitter>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QMenuBar>
#include <QStatusBar>
#include <QMessageBox>

#include "../dialogs/NewCandidateDialog.h"
#include "../dialogs/NewJobPostingDialog.h"
#include "../dialogs/ApplyDialog.h"
#include "../dialogs/AdvanceStatusDialog.h"

#include "../models/JobPosting.h"
#include "../models/Application.h"
#include "../models/Candidate.h"
#include "../models/Company.h"
#include "../models/ApplicationState.h"
#include "../models/AppliedState.h"
#include "../models/InterviewingState.h"
#include "../models/HiredState.h"
#include "../models/RejectedState.h"

#include "../repositories/CompanyRepository.h"
#include "../repositories/RecruiterRepository.h"
#include "../repositories/CandidateRepository.h"
#include "../repositories/JobPostingRepository.h"
#include "../repositories/ApplicationRepository.h"
#include "../repositories/InterviewRepository.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle("Recruitment Manager");
    resize(900, 600);

    // ── Menu bar ──────────────────────────────────────────────────────────────
    QMenu* fileMenu = menuBar()->addMenu("File");
    QAction* saveAction = fileMenu->addAction("Save");
    QAction* loadAction = fileMenu->addAction("Load");
    fileMenu->addSeparator();
    QAction* exitAction = fileMenu->addAction("Exit");

    QMenu* dataMenu = menuBar()->addMenu("Data");
    QAction* newCandidateAction   = dataMenu->addAction("New Candidate");
    QAction* newJobPostingAction  = dataMenu->addAction("New Job Posting");
    QAction* applyAction          = dataMenu->addAction("Apply");
    QAction* advanceStatusAction  = dataMenu->addAction("Advance Status");

    QMenu* helpMenu = menuBar()->addMenu("Help");
    QAction* aboutAction = helpMenu->addAction("About");

    // ── Central widget / splitter ─────────────────────────────────────────────
    splitter_ = new QSplitter(Qt::Horizontal, this);
    setCentralWidget(splitter_);

    // Left pane
    QWidget* leftPane = new QWidget(splitter_);
    QVBoxLayout* leftLayout = new QVBoxLayout(leftPane);
    leftLayout->addWidget(new QLabel("Job Postings", leftPane));
    jobList_ = new QListWidget(leftPane);
    leftLayout->addWidget(jobList_);
    newPostingBtn_ = new QPushButton("+ New Posting", leftPane);
    leftLayout->addWidget(newPostingBtn_);

    // Right pane
    QWidget* rightPane = new QWidget(splitter_);
    QVBoxLayout* rightLayout = new QVBoxLayout(rightPane);
    rightLayout->addWidget(new QLabel("Applicants", rightPane));
    applicantList_ = new QListWidget(rightPane);
    rightLayout->addWidget(applicantList_);
    QHBoxLayout* btnLayout = new QHBoxLayout();
    viewCvBtn_ = new QPushButton("View CV", rightPane);
    scheduleInterviewBtn_ = new QPushButton("Schedule Interview", rightPane);
    btnLayout->addWidget(viewCvBtn_);
    btnLayout->addWidget(scheduleInterviewBtn_);
    rightLayout->addLayout(btnLayout);

    splitter_->addWidget(leftPane);
    splitter_->addWidget(rightPane);

    // ── Status bar ────────────────────────────────────────────────────────────
    statusBar()->showMessage("Ready");

    // ── Signal / slot connections ─────────────────────────────────────────────
    connect(jobList_, &QListWidget::currentRowChanged, this, &MainWindow::onJobSelected);

    connect(saveAction, &QAction::triggered, this, &MainWindow::onSave);
    connect(loadAction, &QAction::triggered, this, &MainWindow::onLoad);
    connect(exitAction, &QAction::triggered, &QApplication::quit);

    connect(newCandidateAction, &QAction::triggered, this, [this]() {
        NewCandidateDialog dlg(this);
        if (dlg.exec() == QDialog::Accepted) {
            static int nextId = 1000;
            new Candidate(nextId++, dlg.getName(), dlg.getEmail(), dlg.getPhone());
            statusBar()->showMessage("Candidate added");
        }
    });
    connect(newJobPostingAction, &QAction::triggered, this, [this]() {
        if (Company::getExtent().empty()) {
            QMessageBox::warning(this, "No Companies", "Add a company first.");
            return;
        }
        NewJobPostingDialog dlg(this);
        if (dlg.exec() == QDialog::Accepted) {
            static int nextId = 2000;
            Company* company = Company::getExtent()[dlg.getCompanyIndex()];
            std::optional<SalaryRange> salary;
            if (dlg.hasSalary())
                salary = SalaryRange{dlg.getSalaryMin(), dlg.getSalaryMax()};
            auto* jp = new JobPosting(nextId++, dlg.getTitle(), dlg.getDescription(), company, salary);
            refreshJobList();
            statusBar()->showMessage(QString("Job posting '%1' added").arg(QString::fromStdString(jp->getTitle())));
        }
    });
    connect(applyAction, &QAction::triggered, this, [this]() {
        if (Candidate::getExtent().empty() || JobPosting::getExtent().empty()) {
            QMessageBox::warning(this, "Missing data", "Need at least one candidate and one job posting.");
            return;
        }
        ApplyDialog dlg(this);
        if (dlg.exec() == QDialog::Accepted) {
            static int nextId = 3000;
            Candidate*  c  = Candidate::getExtent()[dlg.getCandidateIndex()];
            JobPosting* jp = JobPosting::getExtent()[dlg.getJobPostingIndex()];
            std::optional<std::string> cover;
            if (!dlg.getCoverLetter().empty())
                cover = dlg.getCoverLetter();
            new Application(nextId++, c, jp, dlg.getAppliedAt(), cover);
            statusBar()->showMessage("Application submitted");
        }
    });
    connect(advanceStatusAction, &QAction::triggered, this, [this]() {
        if (Candidate::getExtent().empty()) {
            QMessageBox::warning(this, "No Candidates", "No candidates exist.");
            return;
        }
        AdvanceStatusDialog dlg(this);
        if (dlg.exec() == QDialog::Accepted) {
            Candidate* c = Candidate::getExtent()[dlg.getCandidateIndex()];
            const std::string newStatus = dlg.getNewStatus();
            ApplicationState* state = nullptr;
            if (newStatus == "Applied")           state = new AppliedState();
            else if (newStatus == "Interviewing") state = new InterviewingState();
            else if (newStatus == "Hired")        state = new HiredState();
            else if (newStatus == "Rejected")     state = new RejectedState();
            if (state) c->setState(state);
            statusBar()->showMessage(QString::fromStdString(c->getName() + " -> " + newStatus));
            int row = jobList_->currentRow();
            if (row >= 0) onJobSelected(row);
        }
    });

    connect(newPostingBtn_, &QPushButton::clicked, newJobPostingAction, &QAction::trigger);
    connect(viewCvBtn_, &QPushButton::clicked, this, [this]() {
        QMessageBox::information(this, "View CV", "CV viewer not yet implemented");
    });
    connect(scheduleInterviewBtn_, &QPushButton::clicked, this, [this]() {
        QMessageBox::information(this, "Schedule Interview", "Interview scheduler not yet implemented");
    });

    connect(aboutAction, &QAction::triggered, this, [this]() {
        QMessageBox::about(this, "About", "Recruitment Manager\nMAS Final Project");
    });

    // Populate initial job list
    refreshJobList();
}

void MainWindow::refreshJobList() {
    jobList_->clear();
    jobPostings_.clear();

    for (JobPosting* jp : JobPosting::getExtent()) {
        jobPostings_.push_back(jp);
        jobList_->addItem(QString::fromStdString(jp->getTitle()));
    }

    statusBar()->showMessage(
        QString("%1 posting(s) loaded").arg(jobPostings_.size()));
}

void MainWindow::onJobSelected(int row) {
    applicantList_->clear();
    applications_.clear();

    if (row < 0 || row >= static_cast<int>(jobPostings_.size()))
        return;

    JobPosting* jp = jobPostings_[row];
    const std::vector<Application*>& apps = jp->getApplications();

    for (Application* app : apps) {
        applications_.push_back(app);
        Candidate* c = app->getCandidate();
        QString text = QString::fromStdString(c->getName())
                       + "\n  "
                       + QString::fromStdString(c->getStatusLabel())
                       + " · "
                       + QString::fromStdString(app->getAppliedAt());
        applicantList_->addItem(text);
    }

    statusBar()->showMessage(
        QString("%1 posting(s) · %2 applicant(s) for \"%3\"")
            .arg(jobPostings_.size())
            .arg(applications_.size())
            .arg(QString::fromStdString(jp->getTitle())));
}

void MainWindow::onSave() {
    CompanyRepository::saveAll();
    RecruiterRepository::saveAll();
    CandidateRepository::saveAll();
    CandidateRepository::saveSkills();
    JobPostingRepository::saveAll();
    ApplicationRepository::saveAll();
    InterviewRepository::saveAll();
    RecruiterRepository::saveLinks();

    statusBar()->showMessage("Saved successfully");
}

void MainWindow::onLoad() {
    CompanyRepository::loadAll();
    RecruiterRepository::loadAll();
    CandidateRepository::loadAll();
    CandidateRepository::loadSkills();
    JobPostingRepository::loadAll();
    ApplicationRepository::loadAll();
    InterviewRepository::loadAll();
    RecruiterRepository::loadLinks();

    refreshJobList();

    QMessageBox::information(this, "Load",
        QString("%1 job posting(s) loaded").arg(jobPostings_.size()));
}
