#include "Application.h"
#include "Candidate.h"
#include "JobPosting.h"

std::vector<Application*> Application::extent_;

Application::Application(int id, Candidate* candidate, JobPosting* jobPosting,
                         const std::string& appliedAt,
                         std::optional<std::string> coverLetter)
    : id_(id), candidate_(candidate), jobPosting_(jobPosting),
      appliedAt_(appliedAt), coverLetter_(coverLetter) {
    extent_.push_back(this);
    candidate_->addApplication(this);   // automatic back-reference
    jobPosting_->addApplication(this);  // automatic back-reference
}

int                Application::getId()         const { return id_; }
Candidate*         Application::getCandidate()  const { return candidate_; }
JobPosting*        Application::getJobPosting() const { return jobPosting_; }
const std::string& Application::getAppliedAt()  const { return appliedAt_; }
const std::optional<std::string>& Application::getCoverLetter() const { return coverLetter_; }

const std::vector<Application*>& Application::getExtent() { return extent_; }
