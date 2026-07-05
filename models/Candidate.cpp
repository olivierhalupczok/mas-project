#include "Candidate.h"
#include "Skill.h"
#include <algorithm>

std::vector<Candidate*> Candidate::extent_;
int Candidate::instanceCount = 0;

Candidate::Candidate(int id, const std::string& name,
                     const std::string& email, const std::string& phone)
    : id_(id), name_(name), email_(email), phone_(phone) {
    extent_.push_back(this);
    ++instanceCount;
}

Candidate::~Candidate() { delete state_; }

int                Candidate::getId()    const { return id_; }
const std::string& Candidate::getName()  const { return name_; }
const std::string& Candidate::getEmail() const { return email_; }
const std::string& Candidate::getPhone() const { return phone_; }

const std::vector<Candidate*>& Candidate::getExtent() { return extent_; }

Candidate* Candidate::findByName(const std::string& name) {
    auto it = std::find_if(extent_.begin(), extent_.end(),
        [&name](Candidate* c) { return c->getName() == name; });
    return it != extent_.end() ? *it : nullptr;
}

// Derived attribute: computed, never stored.
int Candidate::getApplicationCount() const {
    return static_cast<int>(applications_.size());
}

void Candidate::addSkill(Skill* skill)                       { skills_.push_back(skill); }
void Candidate::addSkill(const std::string& name, int level) { skills_.push_back(new Skill(name, level)); }

const std::vector<Skill*>& Candidate::getSkills() const { return skills_; }

void Candidate::setState(ApplicationState* newState) {
    delete state_;
    state_ = newState;
}

std::string Candidate::getStatusLabel() const {
    return state_ ? state_->getStatusLabel() : "No status";
}

std::string Candidate::getNextAction() const {
    return state_ ? state_->getNextAction() : "";
}

void Candidate::addApplication(Application* app) { applications_.push_back(app); }
const std::vector<Application*>& Candidate::getApplications() const { return applications_; }

void Candidate::addPortfolioEntry(PortfolioEntry* entry) { portfolio_.push_back(entry); }
const std::vector<PortfolioEntry*>& Candidate::getPortfolioEntries() const { return portfolio_; }

void Candidate::addCVDocument(CVDocument* doc) { cvDocuments_.push_back(doc); }
const std::vector<CVDocument*>& Candidate::getCVDocuments() const { return cvDocuments_; }
