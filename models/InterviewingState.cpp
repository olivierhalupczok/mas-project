#include "InterviewingState.h"

std::string InterviewingState::getStatusLabel() const { return "Interviewing"; }
std::string InterviewingState::getNextAction()  const { return "Pending final decision"; }
