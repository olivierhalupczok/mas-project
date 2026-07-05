#pragma once
#include <QDialog>
#include <string>

class QComboBox;
class QLineEdit;
class QTextEdit;
class QDialogButtonBox;

class ApplyDialog : public QDialog {
    Q_OBJECT
public:
    explicit ApplyDialog(QWidget* parent = nullptr);
    int         getCandidateIndex()  const;
    int         getJobPostingIndex() const;
    std::string getAppliedAt()       const;
    std::string getCoverLetter()     const;
private slots:
    void onAccept();
private:
    QComboBox*        candidateCombo_;
    QComboBox*        jobCombo_;
    QLineEdit*        appliedAtEdit_;
    QTextEdit*        coverLetterEdit_;
    QDialogButtonBox* buttons_;
};
