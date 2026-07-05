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
    // TODO: add getPortfolioEntries() to Candidate to enable persistence
}

void CandidateRepository::loadPortfolios() {
    // TODO: add getPortfolioEntries() to Candidate to enable persistence
}

void CandidateRepository::saveCVDocuments() {
    // TODO: add getCVDocuments() to Candidate to enable persistence
}

void CandidateRepository::loadCVDocuments() {
    // TODO: add getCVDocuments() to Candidate to enable persistence
}
