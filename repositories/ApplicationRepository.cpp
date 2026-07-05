#include "ApplicationRepository.h"
#include "Database.h"
#include "../models/Application.h"
#include "../models/Candidate.h"
#include "../models/JobPosting.h"

namespace {
    template<typename T>
    T* findById(const std::vector<T*>& v, int id) {
        for (auto* p : v) if (p->getId() == id) return p;
        return nullptr;
    }
}

void ApplicationRepository::saveAll() {
    auto& db = Database::instance().storage();
    db.remove_all<ApplicationRecord>();
    for (auto* a : Application::getExtent()) {
        ApplicationRecord r;
        r.id           = a->getId();
        r.candidateId  = a->getCandidate()->getId();
        r.jobPostingId = a->getJobPosting()->getId();
        r.appliedAt    = a->getAppliedAt();
        r.coverLetter  = a->getCoverLetter();
        db.replace(r);
    }
}

void ApplicationRepository::loadAll() {
    auto& db = Database::instance().storage();
    for (auto& r : db.get_all<ApplicationRecord>()) {
        auto* candidate   = findById(Candidate::getExtent(),   r.candidateId);
        auto* jobPosting  = findById(JobPosting::getExtent(),  r.jobPostingId);
        new Application(r.id, candidate, jobPosting, r.appliedAt, r.coverLetter);
    }
}
