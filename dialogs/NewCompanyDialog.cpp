#include "NewCompanyDialog.h"

#include <QFormLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QMessageBox>

NewCompanyDialog::NewCompanyDialog(QWidget* parent) : QDialog(parent) {
    setWindowTitle("New Company");

    nameEdit_     = new QLineEdit(this);
    streetEdit_   = new QLineEdit(this);
    cityEdit_     = new QLineEdit(this);
    countryEdit_  = new QLineEdit(this);
    industryEdit_ = new QLineEdit(this);

    auto* form = new QFormLayout();
    form->addRow("Name:",     nameEdit_);
    form->addRow("Street:",   streetEdit_);
    form->addRow("City:",     cityEdit_);
    form->addRow("Country:",  countryEdit_);
    form->addRow("Industry:", industryEdit_);

    buttons_ = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

    auto* layout = new QVBoxLayout(this);
    layout->addLayout(form);
    layout->addWidget(buttons_);

    connect(buttons_, &QDialogButtonBox::accepted, this, &NewCompanyDialog::onAccept);
    connect(buttons_, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

void NewCompanyDialog::onAccept() {
    if (nameEdit_->text().trimmed().isEmpty() ||
        cityEdit_->text().trimmed().isEmpty() ||
        countryEdit_->text().trimmed().isEmpty() ||
        industryEdit_->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Validation",
            "Name, city, country and industry are required.");
        return;
    }
    accept();
}

std::string NewCompanyDialog::getName()     const { return nameEdit_->text().trimmed().toStdString(); }
std::string NewCompanyDialog::getStreet()   const { return streetEdit_->text().trimmed().toStdString(); }
std::string NewCompanyDialog::getCity()     const { return cityEdit_->text().trimmed().toStdString(); }
std::string NewCompanyDialog::getCountry()  const { return countryEdit_->text().trimmed().toStdString(); }
std::string NewCompanyDialog::getIndustry() const { return industryEdit_->text().trimmed().toStdString(); }
