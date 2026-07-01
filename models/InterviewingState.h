#pragma once
#include "ApplicationState.h"

// Concrete state: Candidate has been invited to interview.
// Assigned via setState() — replaces AppliedState at runtime.
class InterviewingState : public ApplicationState {
public:
    std::string getStatusLabel() const override;
    std::string getNextAction()  const override;
};
