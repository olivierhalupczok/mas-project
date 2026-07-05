#pragma once
#include <QMainWindow>
#include <vector>

class QSplitter;
class QListWidget;
class QPushButton;
class QLabel;

class JobPosting;
class Application;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

private slots:
    void onJobSelected(int row);
    void onSave();
    void onLoad();
    void refreshJobList();

private:
    // Widgets
    QSplitter*   splitter_;
    QListWidget* jobList_;
    QListWidget* applicantList_;
    QPushButton* newPostingBtn_;
    QPushButton* viewCvBtn_;
    QPushButton* scheduleInterviewBtn_;

    // Parallel data vectors
    std::vector<JobPosting*>  jobPostings_;
    std::vector<Application*> applications_;
};
