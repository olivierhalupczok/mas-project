#include "AppliedState.h"

std::string AppliedState::getStatusLabel() const { return "Applied"; }
std::string AppliedState::getNextAction()  const { return "Awaiting recruiter review"; }
