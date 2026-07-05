#include "JobPosting.h"

std::vector<JobPosting*>           JobPosting::extent_;
std::map<std::string, JobPosting*> JobPosting::byTitle_;

JobPosting::JobPosting(int id, const std::string& title, const std::string& description,
                       Company* company, std::optional<SalaryRange> salaryRange)
    : id_(id), title_(title), description_(description),
      company_(company), salaryRange_(salaryRange) {
    extent_.push_back(this);
    byTitle_[title] = this;   // qualified association: index by title
}

int                JobPosting::getId()          const { return id_; }
const std::string& JobPosting::getTitle()       const { return title_; }
const std::string& JobPosting::getDescription() const { return description_; }
Company*           JobPosting::getCompany()     const { return company_; }
const std::optional<SalaryRange>& JobPosting::getSalaryRange() const { return salaryRange_; }

void JobPosting::addApplication(Application* app) { applications_.push_back(app); }
const std::vector<Application*>& JobPosting::getApplications() const { return applications_; }

const std::vector<JobPosting*>& JobPosting::getExtent() { return extent_; }

JobPosting* JobPosting::findByTitle(const std::string& title) {
    auto it = byTitle_.find(title);
    return it != byTitle_.end() ? it->second : nullptr;
}
