#include "RecruiterRepository.h"
#include "Database.h"
#include "../models/Recruiter.h"
#include "../models/Candidate.h"

namespace {
    template<typename T>
    T* findById(const std::vector<T*>& v, int id) {
        for (auto* p : v) if (p->getId() == id) return p;
        return nullptr;
    }
}

void RecruiterRepository::saveAll() {
    auto& db = Database::instance().storage();
    db.remove_all<RecruiterRecord>();
    for (auto* r : Recruiter::getExtent()) {
        RecruiterRecord rec;
        rec.id        = r->getId();
        rec.name      = r->getName();
        rec.email     = r->getEmail();
        rec.companyId = 0;
        db.replace(rec);
    }
}

void RecruiterRepository::loadAll() {
    auto& db = Database::instance().storage();
    for (auto& r : db.get_all<RecruiterRecord>()) {
        new Recruiter(r.id, r.name, r.email);
    }
}

void RecruiterRepository::saveLinks() {
    auto& db = Database::instance().storage();
    db.remove_all<RecruiterCandidateRecord>();
    for (auto* r : Recruiter::getExtent()) {
        for (auto* c : r->getCandidates()) {
            db.replace(RecruiterCandidateRecord{r->getId(), c->getId()});
        }
    }
}

void RecruiterRepository::loadLinks() {
    auto& db = Database::instance().storage();
    for (auto& link : db.get_all<RecruiterCandidateRecord>()) {
        auto* recruiter  = findById(Recruiter::getExtent(),  link.recruiterId);
        auto* candidate  = findById(Candidate::getExtent(),  link.candidateId);
        if (recruiter && candidate) {
            recruiter->assign(candidate);
        }
    }
}
