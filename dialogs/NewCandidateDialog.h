#pragma once
#include <QDialog>
#include <string>

class QLineEdit;
class QDialogButtonBox;

class NewCandidateDialog : public QDialog {
    Q_OBJECT
public:
    explicit NewCandidateDialog(QWidget* parent = nullptr);
    std::string getName()  const;
    std::string getEmail() const;
    std::string getPhone() const;
private slots:
    void onAccept();
private:
    QLineEdit* nameEdit_;
    QLineEdit* emailEdit_;
    QLineEdit* phoneEdit_;
    QDialogButtonBox* buttons_;
};
