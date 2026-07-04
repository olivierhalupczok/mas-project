#include "Recruiter.h"
#include "Candidate.h"
#include <algorithm>

std::vector<Recruiter*> Recruiter::extent_;

Recruiter::Recruiter(int id, const std::string& name, const std::string& email)
    : id_(id), name_(name), email_(email) {
    extent_.push_back(this);
}

int                Recruiter::getId()    const { return id_; }
const std::string& Recruiter::getName()  const { return name_; }
const std::string& Recruiter::getEmail() const { return email_; }

void Recruiter::assign(Candidate* candidate) {
    if (std::find(candidates_.begin(), candidates_.end(), candidate) == candidates_.end())
        candidates_.push_back(candidate);
}

void Recruiter::assign(const std::string& name, const std::string& email, const std::string& phone) {
    int id = static_cast<int>(Candidate::getExtent().size()) + 1;
    assign(new Candidate(id, name, email, phone));
}

const std::vector<Candidate*>& Recruiter::getCandidates() const { return candidates_; }
const std::vector<Recruiter*>& Recruiter::getExtent()     { return extent_; }
