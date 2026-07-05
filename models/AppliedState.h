#pragma once
#include "ApplicationState.h"

// Candidate has submitted an application and awaits recruiter review.
class AppliedState : public ApplicationState {
public:
    std::string getStatusLabel() const override;
    std::string getNextAction()  const override;
};
