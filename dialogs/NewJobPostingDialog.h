#pragma once
#include <QDialog>
#include <string>

class QLineEdit;
class QTextEdit;
class QComboBox;
class QDoubleSpinBox;
class QCheckBox;
class QDialogButtonBox;

class NewJobPostingDialog : public QDialog {
    Q_OBJECT
public:
    explicit NewJobPostingDialog(QWidget* parent = nullptr);
    std::string getTitle()        const;
    std::string getDescription()  const;
    int         getCompanyIndex() const;
    bool        hasSalary()       const;
    double      getSalaryMin()    const;
    double      getSalaryMax()    const;
private slots:
    void onAccept();
    void onSalaryToggled(bool checked);
private:
    QLineEdit*        titleEdit_;
    QTextEdit*        descEdit_;
    QComboBox*        companyCombo_;
    QCheckBox*        salaryCheck_;
    QDoubleSpinBox*   salaryMinSpin_;
    QDoubleSpinBox*   salaryMaxSpin_;
    QDialogButtonBox* buttons_;
};
