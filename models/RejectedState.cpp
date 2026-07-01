#include "RejectedState.h"

std::string RejectedState::getStatusLabel() const { return "Rejected"; }
std::string RejectedState::getNextAction()  const { return "Application closed"; }
