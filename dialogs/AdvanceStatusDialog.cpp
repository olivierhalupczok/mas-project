#include "AdvanceStatusDialog.h"

#include <QFormLayout>
#include <QVBoxLayout>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QMessageBox>

#include "../models/Candidate.h"

AdvanceStatusDialog::AdvanceStatusDialog(QWidget* parent) : QDialog(parent) {
    setWindowTitle("Advance Status");

    candidateCombo_ = new QComboBox(this);
    statusCombo_    = new QComboBox(this);

    for (Candidate* c : Candidate::getExtent()) {
        QString label = QString::fromStdString(c->getName())
                        + " (" + QString::fromStdString(c->getStatusLabel()) + ")";
        candidateCombo_->addItem(label);
    }

    statusCombo_->addItems({"Applied", "Interviewing", "Hired", "Rejected"});

    auto* form = new QFormLayout();
    form->addRow("Candidate:",  candidateCombo_);
    form->addRow("New Status:", statusCombo_);

    buttons_ = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

    auto* layout = new QVBoxLayout(this);
    layout->addLayout(form);
    layout->addWidget(buttons_);

    connect(buttons_, &QDialogButtonBox::accepted, this, &AdvanceStatusDialog::onAccept);
    connect(buttons_, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

void AdvanceStatusDialog::onAccept() {
    accept();
}

int         AdvanceStatusDialog::getCandidateIndex() const { return candidateCombo_->currentIndex(); }
std::string AdvanceStatusDialog::getNewStatus()      const { return statusCombo_->currentText().toStdString(); }
