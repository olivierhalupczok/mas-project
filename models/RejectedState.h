#pragma once
#include "ApplicationState.h"

// Concrete state: application was unsuccessful.
// Demonstrates the alternative terminal transition from InterviewingState.
class RejectedState : public ApplicationState {
public:
    std::string getStatusLabel() const override;
    std::string getNextAction()  const override;
};
