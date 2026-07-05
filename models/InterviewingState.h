#pragma once
#include "ApplicationState.h"

// Candidate has been invited to interview.
class InterviewingState : public ApplicationState {
public:
    std::string getStatusLabel() const override;
    std::string getNextAction()  const override;
};
