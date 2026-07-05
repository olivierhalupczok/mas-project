#pragma once
#include <QDialog>
#include <string>

class Application;
class QLineEdit;
class QTextEdit;
class QDialogButtonBox;

class ScheduleInterviewDialog : public QDialog {
    Q_OBJECT
public:
    explicit ScheduleInterviewDialog(Application* application, QWidget* parent = nullptr);
    std::string getScheduledAt() const;
    std::string getLocation()    const;
    std::string getNotes()       const;
private slots:
    void onAccept();
private:
    QLineEdit*        scheduledAtEdit_;
    QLineEdit*        locationEdit_;
    QTextEdit*        notesEdit_;
    QDialogButtonBox* buttons_;
};
