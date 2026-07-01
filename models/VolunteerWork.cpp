#include "VolunteerWork.h"
#include <iostream>

VolunteerWork::VolunteerWork(const std::string& title, const std::string& organization,
                              const std::string& cause)
    : CVSection(title), organization_(organization), cause_(cause) {}

void VolunteerWork::render() const {
    std::cout << "[Volunteer Work] " << title_ << " at " << organization_
              << "\n  Cause: " << cause_ << "\n";
}

std::string VolunteerWork::getType()           const { return "VolunteerWork"; }
const std::string& VolunteerWork::getOrganization() const { return organization_; }
