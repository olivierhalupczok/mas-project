#include "NewCandidateDialog.h"

#include <QFormLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QMessageBox>

NewCandidateDialog::NewCandidateDialog(QWidget* parent) : QDialog(parent) {
    setWindowTitle("New Candidate");

    nameEdit_  = new QLineEdit(this);
    emailEdit_ = new QLineEdit(this);
    phoneEdit_ = new QLineEdit(this);

    auto* form = new QFormLayout();
    form->addRow("Name:",  nameEdit_);
    form->addRow("Email:", emailEdit_);
    form->addRow("Phone:", phoneEdit_);

    buttons_ = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

    auto* layout = new QVBoxLayout(this);
    layout->addLayout(form);
    layout->addWidget(buttons_);

    connect(buttons_, &QDialogButtonBox::accepted, this, &NewCandidateDialog::onAccept);
    connect(buttons_, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

void NewCandidateDialog::onAccept() {
    if (nameEdit_->text().trimmed().isEmpty() ||
        emailEdit_->text().trimmed().isEmpty() ||
        phoneEdit_->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Validation", "All fields are required.");
        return;
    }
    accept();
}

std::string NewCandidateDialog::getName()  const { return nameEdit_->text().trimmed().toStdString(); }
std::string NewCandidateDialog::getEmail() const { return emailEdit_->text().trimmed().toStdString(); }
std::string NewCandidateDialog::getPhone() const { return phoneEdit_->text().trimmed().toStdString(); }
