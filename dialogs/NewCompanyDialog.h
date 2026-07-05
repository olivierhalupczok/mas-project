#pragma once
#include <QDialog>
#include <string>

class QLineEdit;
class QDialogButtonBox;

class NewCompanyDialog : public QDialog {
    Q_OBJECT
public:
    explicit NewCompanyDialog(QWidget* parent = nullptr);
    std::string getName()     const;
    std::string getStreet()   const;
    std::string getCity()     const;
    std::string getCountry()  const;
    std::string getIndustry() const;
private slots:
    void onAccept();
private:
    QLineEdit* nameEdit_;
    QLineEdit* streetEdit_;
    QLineEdit* cityEdit_;
    QLineEdit* countryEdit_;
    QLineEdit* industryEdit_;
    QDialogButtonBox* buttons_;
};
