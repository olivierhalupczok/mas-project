#include "ApplyDialog.h"

#include <QFormLayout>
#include <QVBoxLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QDate>

#include "../models/Candidate.h"
#include "../models/JobPosting.h"

ApplyDialog::ApplyDialog(QWidget* parent) : QDialog(parent) {
    setWindowTitle("Apply");

    candidateCombo_   = new QComboBox(this);
    jobCombo_         = new QComboBox(this);
    appliedAtEdit_    = new QLineEdit(this);
    coverLetterEdit_  = new QTextEdit(this);

    appliedAtEdit_->setText(QDate::currentDate().toString("yyyy-MM-dd"));
    coverLetterEdit_->setPlaceholderText("Optional cover letter...");

    for (Candidate* c : Candidate::getExtent())
        candidateCombo_->addItem(QString::fromStdString(c->getName()));

    for (JobPosting* jp : JobPosting::getExtent())
        jobCombo_->addItem(QString::fromStdString(jp->getTitle()));

    auto* form = new QFormLayout();
    form->addRow("Candidate:",    candidateCombo_);
    form->addRow("Job Posting:",  jobCombo_);
    form->addRow("Applied At:",   appliedAtEdit_);
    form->addRow("Cover Letter:", coverLetterEdit_);

    buttons_ = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

    auto* layout = new QVBoxLayout(this);
    layout->addLayout(form);
    layout->addWidget(buttons_);

    connect(buttons_, &QDialogButtonBox::accepted, this, &ApplyDialog::onAccept);
    connect(buttons_, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

void ApplyDialog::onAccept() {
    if (candidateCombo_->currentIndex() < 0) {
        QMessageBox::warning(this, "Validation", "Please select a candidate.");
        return;
    }
    if (jobCombo_->currentIndex() < 0) {
        QMessageBox::warning(this, "Validation", "Please select a job posting.");
        return;
    }
    accept();
}

int         ApplyDialog::getCandidateIndex()  const { return candidateCombo_->currentIndex(); }
int         ApplyDialog::getJobPostingIndex() const { return jobCombo_->currentIndex(); }
std::string ApplyDialog::getAppliedAt()       const { return appliedAtEdit_->text().trimmed().toStdString(); }
std::string ApplyDialog::getCoverLetter()     const { return coverLetterEdit_->toPlainText().trimmed().toStdString(); }
