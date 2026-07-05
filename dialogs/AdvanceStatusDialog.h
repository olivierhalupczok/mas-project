#pragma once
#include <QDialog>
#include <string>

class QComboBox;
class QDialogButtonBox;

class AdvanceStatusDialog : public QDialog {
    Q_OBJECT
public:
    explicit AdvanceStatusDialog(QWidget* parent = nullptr);
    int         getCandidateIndex() const;
    std::string getNewStatus()      const;
private slots:
    void onAccept();
private:
    QComboBox*        candidateCombo_;
    QComboBox*        statusCombo_;
    QDialogButtonBox* buttons_;
};
