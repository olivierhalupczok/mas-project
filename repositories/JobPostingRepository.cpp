#include "JobPostingRepository.h"
#include "Database.h"
#include "../models/JobPosting.h"
#include "../models/Company.h"

namespace {
    template<typename T>
    T* findById(const std::vector<T*>& v, int id) {
        for (auto* p : v) if (p->getId() == id) return p;
        return nullptr;
    }
}

void JobPostingRepository::saveAll() {
    auto& db = Database::instance().storage();
    db.remove_all<JobPostingRecord>();
    for (auto* jp : JobPosting::getExtent()) {
        JobPostingRecord r;
        r.id          = jp->getId();
        r.title       = jp->getTitle();
        r.description = jp->getDescription();
        r.companyId   = jp->getCompany()->getId();
        r.recruiterId = 0;
        const auto& sr = jp->getSalaryRange();
        if (sr) {
            r.salaryMin = sr->min;
            r.salaryMax = sr->max;
        } else {
            r.salaryMin = std::nullopt;
            r.salaryMax = std::nullopt;
        }
        db.replace(r);
    }
}

void JobPostingRepository::loadAll() {
    auto& db = Database::instance().storage();
    for (auto& r : db.get_all<JobPostingRecord>()) {
        auto* company = findById(Company::getExtent(), r.companyId);
        std::optional<SalaryRange> salaryRange;
        if (r.salaryMin && r.salaryMax) {
            salaryRange = SalaryRange{*r.salaryMin, *r.salaryMax};
        }
        new JobPosting(r.id, r.title, r.description, company, salaryRange);
    }
}
