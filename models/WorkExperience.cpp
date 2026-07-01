#include "WorkExperience.h"
#include <iostream>

WorkExperience::WorkExperience(const std::string& title, const std::string& company,
                                const std::string& period, const std::string& description)
    : CVSection(title), company_(company), period_(period), description_(description) {}

void WorkExperience::render() const {
    std::cout << "[Work Experience] " << title_ << " @ " << company_
              << " (" << period_ << ")\n"
              << "  " << description_ << "\n";
}

std::string WorkExperience::getType() const { return "WorkExperience"; }
const std::string& WorkExperience::getCompany() const { return company_; }
const std::string& WorkExperience::getPeriod()  const { return period_; }
