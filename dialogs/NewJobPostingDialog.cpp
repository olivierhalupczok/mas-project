#include "NewJobPostingDialog.h"

#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QLabel>

#include "../models/Company.h"

NewJobPostingDialog::NewJobPostingDialog(QWidget* parent) : QDialog(parent) {
    setWindowTitle("New Job Posting");

    titleEdit_    = new QLineEdit(this);
    descEdit_     = new QTextEdit(this);
    companyCombo_ = new QComboBox(this);
    salaryCheck_  = new QCheckBox("Include salary range", this);
    salaryMinSpin_ = new QDoubleSpinBox(this);
    salaryMaxSpin_ = new QDoubleSpinBox(this);

    salaryMinSpin_->setRange(0.0, 999999.0);
    salaryMaxSpin_->setRange(0.0, 999999.0);
    salaryMinSpin_->setEnabled(false);
    salaryMaxSpin_->setEnabled(false);

    for (Company* c : Company::getExtent())
        companyCombo_->addItem(QString::fromStdString(c->getName()));

    auto* form = new QFormLayout();
    form->addRow("Title:",       titleEdit_);
    form->addRow("Description:", descEdit_);
    form->addRow("Company:",     companyCombo_);
    form->addRow(salaryCheck_);
    form->addRow("Salary Min:",  salaryMinSpin_);
    form->addRow("Salary Max:",  salaryMaxSpin_);

    buttons_ = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

    auto* layout = new QVBoxLayout(this);
    layout->addLayout(form);
    layout->addWidget(buttons_);

    connect(salaryCheck_, &QCheckBox::toggled, this, &NewJobPostingDialog::onSalaryToggled);
    connect(buttons_, &QDialogButtonBox::accepted, this, &NewJobPostingDialog::onAccept);
    connect(buttons_, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

void NewJobPostingDialog::onSalaryToggled(bool checked) {
    salaryMinSpin_->setEnabled(checked);
    salaryMaxSpin_->setEnabled(checked);
}

void NewJobPostingDialog::onAccept() {
    if (titleEdit_->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Validation", "Title is required.");
        return;
    }
    if (descEdit_->toPlainText().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Validation", "Description is required.");
        return;
    }
    if (companyCombo_->currentIndex() < 0) {
        QMessageBox::warning(this, "Validation", "Please select a company.");
        return;
    }
    if (salaryCheck_->isChecked() && salaryMaxSpin_->value() < salaryMinSpin_->value()) {
        QMessageBox::warning(this, "Validation", "Salary max must be >= salary min.");
        return;
    }
    accept();
}

std::string NewJobPostingDialog::getTitle()       const { return titleEdit_->text().trimmed().toStdString(); }
std::string NewJobPostingDialog::getDescription() const { return descEdit_->toPlainText().trimmed().toStdString(); }
int         NewJobPostingDialog::getCompanyIndex() const { return companyCombo_->currentIndex(); }
bool        NewJobPostingDialog::hasSalary()       const { return salaryCheck_->isChecked(); }
double      NewJobPostingDialog::getSalaryMin()    const { return salaryMinSpin_->value(); }
double      NewJobPostingDialog::getSalaryMax()    const { return salaryMaxSpin_->value(); }
