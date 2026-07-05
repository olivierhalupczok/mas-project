#pragma once
#include "ApplicationState.h"

// Candidate accepted a job offer (terminal state).
class HiredState : public ApplicationState {
public:
    std::string getStatusLabel() const override;
    std::string getNextAction()  const override;
};
