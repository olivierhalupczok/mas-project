#include "ScheduleInterviewDialog.h"

#include <QFormLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QDate>
#include <QTime>

#include "../models/Application.h"
#include "../models/Candidate.h"
#include "../models/JobPosting.h"

ScheduleInterviewDialog::ScheduleInterviewDialog(Application* application, QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle("Schedule Interview");

    QVBoxLayout* outer = new QVBoxLayout(this);

    QString info = QString("Candidate: <b>%1</b>  →  %2")
        .arg(QString::fromStdString(application->getCandidate()->getName()))
        .arg(QString::fromStdString(application->getJobPosting()->getTitle()));
    QLabel* infoLabel = new QLabel(info, this);
    infoLabel->setTextFormat(Qt::RichText);
    outer->addWidget(infoLabel);

    QFormLayout* form = new QFormLayout();

    scheduledAtEdit_ = new QLineEdit(this);
    scheduledAtEdit_->setText(QDate::currentDate().toString("yyyy-MM-dd") + " 10:00");
    form->addRow("Scheduled At:", scheduledAtEdit_);

    locationEdit_ = new QLineEdit(this);
    locationEdit_->setPlaceholderText("e.g. Room A / Online");
    form->addRow("Location:", locationEdit_);

    notesEdit_ = new QTextEdit(this);
    notesEdit_->setPlaceholderText("Optional notes...");
    notesEdit_->setFixedHeight(80);
    form->addRow("Notes:", notesEdit_);

    outer->addLayout(form);

    buttons_ = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttons_, &QDialogButtonBox::accepted, this, &ScheduleInterviewDialog::onAccept);
    connect(buttons_, &QDialogButtonBox::rejected, this, &QDialog::reject);
    outer->addWidget(buttons_);
}

void ScheduleInterviewDialog::onAccept() {
    if (locationEdit_->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Validation", "Location is required.");
        return;
    }
    accept();
}

std::string ScheduleInterviewDialog::getScheduledAt() const {
    return scheduledAtEdit_->text().toStdString();
}

std::string ScheduleInterviewDialog::getLocation() const {
    return locationEdit_->text().toStdString();
}

std::string ScheduleInterviewDialog::getNotes() const {
    return notesEdit_->toPlainText().toStdString();
}
