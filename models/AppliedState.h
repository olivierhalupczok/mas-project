#pragma once
#include "ApplicationState.h"

// Concrete state: Candidate has submitted an application, awaiting recruiter review.
// This is the initial "subclass" assigned to a newly created Candidate.
class AppliedState : public ApplicationState {
public:
    std::string getStatusLabel() const override;
    std::string getNextAction()  const override;
};
