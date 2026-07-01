#pragma once
#include "ApplicationState.h"

// Concrete state: Candidate accepted a job offer.
// Assigned via setState() — replaces InterviewingState at runtime.
class HiredState : public ApplicationState {
public:
    std::string getStatusLabel() const override;
    std::string getNextAction()  const override;
};
