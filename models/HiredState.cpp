#include "HiredState.h"

std::string HiredState::getStatusLabel() const { return "Hired"; }
std::string HiredState::getNextAction()  const { return "Onboarding in progress"; }
