#include "Candidate.h"
#include <iostream>
#include <stdexcept>

Candidate::Candidate(const std::string& name, const std::string& targetRole)
    : name_(name), targetRole_(targetRole), state_(nullptr) {}

Candidate::~Candidate() { delete state_; }

void Candidate::setState(ApplicationState* newState) {
    delete state_;      // destroy the old role object (old "subclass")
    state_ = newState;  // assign the new role object (new "subclass")
}

std::string Candidate::getStatusLabel() const {
    if (!state_) throw std::logic_error("Candidate has no state assigned");
    return state_->getStatusLabel();    // delegation to current role
}

std::string Candidate::getNextAction() const {
    if (!state_) throw std::logic_error("Candidate has no state assigned");
    return state_->getNextAction();     // delegation to current role
}

const std::string& Candidate::getName()       const { return name_; }
const std::string& Candidate::getTargetRole() const { return targetRole_; }

void Candidate::print() const {
    std::cout << "Candidate: " << name_ << " (applying for: " << targetRole_ << ")\n"
              << "  Status : " << getStatusLabel() << "\n"
              << "  Next   : " << getNextAction()  << "\n";
}
