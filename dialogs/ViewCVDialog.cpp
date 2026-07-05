#include "ViewCVDialog.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QTreeWidget>
#include <QGroupBox>
#include <QDialogButtonBox>

#include "../models/Candidate.h"
#include "../models/Skill.h"
#include "../models/ITechnical.h"
#include "../models/ISoft.h"
#include "../models/CVDocument.h"
#include "../models/CVSection.h"
#include "../models/WorkExperience.h"
#include "../models/Education.h"
#include "../models/VolunteerWork.h"

ViewCVDialog::ViewCVDialog(Candidate* candidate, QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle(QString("CV — %1").arg(QString::fromStdString(candidate->getName())));
    resize(600, 500);

    QVBoxLayout* layout = new QVBoxLayout(this);

    // Header
    QLabel* header = new QLabel(
        QString("<b>%1</b>  ·  %2  ·  %3")
            .arg(QString::fromStdString(candidate->getName()))
            .arg(QString::fromStdString(candidate->getEmail()))
            .arg(QString::fromStdString(candidate->getPhone())),
        this);
    header->setTextFormat(Qt::RichText);
    layout->addWidget(header);

    // Skills group
    QGroupBox* skillsBox = new QGroupBox("Skills", this);
    QVBoxLayout* skillsLayout = new QVBoxLayout(skillsBox);
    skillList_ = new QListWidget(skillsBox);
    for (Skill* s : candidate->getSkills()) {
        QString item = QString::fromStdString(s->getName())
                       + QString(" (level %1)").arg(s->getProficiencyLevel());
        if (s->isTechnical()) item += " [Technical]";
        if (s->isSoft())      item += " [Soft]";
        skillList_->addItem(item);
    }
    skillsLayout->addWidget(skillList_);
    layout->addWidget(skillsBox);

    // CV sections group
    QGroupBox* cvBox = new QGroupBox("CV Sections", this);
    QVBoxLayout* cvLayout = new QVBoxLayout(cvBox);
    cvTree_ = new QTreeWidget(cvBox);
    cvTree_->setColumnCount(2);
    cvTree_->setHeaderLabels({"Type / Title", "Details"});
    cvTree_->setColumnWidth(0, 220);

    // Find CVDocuments by matching ownerName to candidate name
    for (CVDocument* doc : CVDocument::getExtent()) {
        if (doc->getOwnerName() != candidate->getName()) continue;
        QTreeWidgetItem* docItem = new QTreeWidgetItem(cvTree_);
        docItem->setText(0, QString("CV: %1 (%2 / %3)")
            .arg(QString::fromStdString(doc->getOwnerName()))
            .arg(QString::fromStdString(doc->getFormat()))
            .arg(QString::fromStdString(doc->getLanguage())));
        cvTree_->addTopLevelItem(docItem);

        for (CVSection* section : doc->getSections()) {
            QTreeWidgetItem* secItem = new QTreeWidgetItem(docItem);
            secItem->setText(0, QString("[%1] %2")
                .arg(QString::fromStdString(section->getType()))
                .arg(QString::fromStdString(section->getTitle())));

            if (section->getType() == "WorkExperience") {
                auto* we = dynamic_cast<WorkExperience*>(section);
                if (we)
                    secItem->setText(1, QString("%1 · %2 — %3")
                        .arg(QString::fromStdString(we->getCompany()))
                        .arg(QString::fromStdString(we->getPeriod()))
                        .arg(QString::fromStdString(we->getDescription())));
            } else if (section->getType() == "Education") {
                auto* ed = dynamic_cast<Education*>(section);
                if (ed)
                    secItem->setText(1, QString("%1 · %2 (%3)")
                        .arg(QString::fromStdString(ed->getInstitution()))
                        .arg(QString::fromStdString(ed->getDegree()))
                        .arg(ed->getGraduationYear()));
            } else if (section->getType() == "VolunteerWork") {
                auto* vw = dynamic_cast<VolunteerWork*>(section);
                if (vw)
                    secItem->setText(1, QString("%1 — %2")
                        .arg(QString::fromStdString(vw->getOrganization()))
                        .arg(QString::fromStdString(vw->getCause())));
            }
        }
        docItem->setExpanded(true);
    }
    cvLayout->addWidget(cvTree_);
    layout->addWidget(cvBox);

    buttons_ = new QDialogButtonBox(QDialogButtonBox::Ok, this);
    connect(buttons_, &QDialogButtonBox::accepted, this, &QDialog::accept);
    layout->addWidget(buttons_);
}
