#pragma once
#include "ApplicationState.h"

// Application was unsuccessful (terminal state).
class RejectedState : public ApplicationState {
public:
    std::string getStatusLabel() const override;
    std::string getNextAction()  const override;
};
