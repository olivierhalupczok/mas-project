#pragma once
#include <QDialog>

class Candidate;
class QListWidget;
class QTreeWidget;
class QDialogButtonBox;

class ViewCVDialog : public QDialog {
    Q_OBJECT
public:
    explicit ViewCVDialog(Candidate* candidate, QWidget* parent = nullptr);
private:
    QListWidget*      skillList_;
    QTreeWidget*      cvTree_;
    QDialogButtonBox* buttons_;
};
