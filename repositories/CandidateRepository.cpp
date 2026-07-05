#include "CandidateRepository.h"
#include "Database.h"
#include "../models/Candidate.h"
#include "../models/Skill.h"
#include "../models/TechnicalSkillRole.h"
#include "../models/SoftSkillRole.h"
#include "../models/AppliedState.h"
#include "../models/InterviewingState.h"
#include "../models/HiredState.h"
#include "../models/RejectedState.h"
#include "../models/PortfolioEntry.h"
#include "../models/CVDocument.h"
#include "../models/CVSection.h"
#include "../models/WorkExperience.h"
#include "../models/Education.h"
#include "../models/VolunteerWork.h"

namespace {
    template<typename T>
    T* findById(const std::vector<T*>& v, int id) {
        for (auto* p : v) if (p->getId() == id) return p;
        return nullptr;
    }
}

void CandidateRepository::saveAll() {
    auto& db = Database::instance().storage();
    db.remove_all<CandidateRecord>();
    for (auto* c : Candidate::getExtent()) {
        CandidateRecord r;
        r.id     = c->getId();
        r.name   = c->getName();
        r.email  = c->getEmail();
        r.phone  = c->getPhone();
        r.status = c->getStatusLabel();
        db.replace(r);
    }
}

void CandidateRepository::loadAll() {
    auto& db = Database::instance().storage();
    for (auto& r : db.get_all<CandidateRecord>()) {
        auto* c = new Candidate(r.id, r.name, r.email, r.phone);
        ApplicationState* state = nullptr;
        if      (r.status == "Applied")      state = new AppliedState();
        else if (r.status == "Interviewing") state = new InterviewingState();
        else if (r.status == "Hired")        state = new HiredState();
        else if (r.status == "Rejected")     state = new RejectedState();
        if (state) c->setState(state);
    }
}

void CandidateRepository::saveSkills() {
    auto& db = Database::instance().storage();
    db.remove_all<SkillRecord>();
    for (auto* c : Candidate::getExtent()) {
        for (auto* s : c->getSkills()) {
            SkillRecord r;
            r.id               = s->getId();
            r.name             = s->getName();
            r.proficiencyLevel = s->getProficiencyLevel();
            r.isTechnical      = s->isTechnical() ? 1 : 0;
            r.isSoft           = s->isSoft()       ? 1 : 0;
            r.candidateId      = c->getId();
            // store categories via role if available
            // (ITechnical/ISoft don't expose category from Skill directly;
            //  SkillRecord has optional fields for them)
            db.replace(r);
        }
    }
}

void CandidateRepository::loadSkills() {
    auto& db = Database::instance().storage();
    for (auto& r : db.get_all<SkillRecord>()) {
        auto* s = new Skill(r.id, r.name, r.proficiencyLevel);
        if (r.isTechnical) {
            std::string cat = r.technicalCategory.value_or("");
            s->setTechnicalRole(new TechnicalSkillRole(cat));
        }
        if (r.isSoft) {
            std::string cat = r.softCategory.value_or("");
            s->setSoftRole(new SoftSkillRole(cat));
        }
        auto* c = findById(Candidate::getExtent(), r.candidateId);
        if (c) c->addSkill(s);
    }
}

void CandidateRepository::savePortfolios() {
    auto& db = Database::instance().storage();
    db.remove_all<PortfolioEntryRecord>();
    for (auto* c : Candidate::getExtent()) {
        for (auto* p : c->getPortfolioEntries()) {
            PortfolioEntryRecord r;
            r.id          = p->getId();
            r.projectName = p->getProjectName();
            r.filePath    = p->getFilePath();
            r.mimeType    = p->getMimeType();
            r.rating      = p->getRating();
            r.reviewCount = p->getReviewCount();
            r.candidateId = c->getId();
            db.replace(r);
        }
    }
}

void CandidateRepository::loadPortfolios() {
    auto& db = Database::instance().storage();
    for (auto& r : db.get_all<PortfolioEntryRecord>()) {
        auto* p = new PortfolioEntry(r.id, r.projectName, r.filePath,
                                     r.mimeType, r.rating, r.reviewCount);
        auto* c = findById(Candidate::getExtent(), r.candidateId);
        if (c) c->addPortfolioEntry(p);
    }
}

void CandidateRepository::saveCVDocuments() {
    auto& db = Database::instance().storage();
    db.remove_all<CVDocumentRecord>();
    db.remove_all<CVSectionRecord>();
    for (auto* c : Candidate::getExtent()) {
        for (auto* doc : c->getCVDocuments()) {
            CVDocumentRecord d;
            d.id          = doc->getId();
            d.ownerName   = doc->getOwnerName();
            d.format      = doc->getFormat();
            d.language    = doc->getLanguage();
            d.candidateId = c->getId();
            db.replace(d);

            for (auto* s : doc->getSections()) {
                CVSectionRecord sr;
                sr.type         = s->getType();
                sr.title        = s->getTitle();
                sr.cvDocumentId = doc->getId();
                if (auto* w = dynamic_cast<WorkExperience*>(s)) {
                    sr.company     = w->getCompany();
                    sr.period      = w->getPeriod();
                    sr.description = w->getDescription();
                } else if (auto* e = dynamic_cast<Education*>(s)) {
                    sr.institution    = e->getInstitution();
                    sr.degree         = e->getDegree();
                    sr.graduationYear = e->getGraduationYear();
                } else if (auto* v = dynamic_cast<VolunteerWork*>(s)) {
                    sr.organization = v->getOrganization();
                    sr.cause        = v->getCause();
                }
                db.replace(sr);
            }
        }
    }
}

void CandidateRepository::loadCVDocuments() {
    auto& db = Database::instance().storage();
    std::vector<CVDocument*> loaded;
    for (auto& d : db.get_all<CVDocumentRecord>()) {
        auto* doc = new CVDocument(d.id, d.ownerName, d.format, d.language);
        loaded.push_back(doc);
        auto* c = findById(Candidate::getExtent(), d.candidateId);
        if (c) c->addCVDocument(doc);
    }
    for (auto& sr : db.get_all<CVSectionRecord>()) {
        auto* doc = findById(loaded, sr.cvDocumentId);
        if (!doc) continue;
        if (sr.type == "WorkExperience")
            doc->addWorkExperience(sr.title, sr.company.value_or(""),
                                   sr.period.value_or(""), sr.description.value_or(""));
        else if (sr.type == "Education")
            doc->addEducation(sr.title, sr.institution.value_or(""),
                              sr.degree.value_or(""), sr.graduationYear.value_or(0));
        else if (sr.type == "VolunteerWork")
            doc->addVolunteerWork(sr.title, sr.organization.value_or(""),
                                  sr.cause.value_or(""));
    }
}
