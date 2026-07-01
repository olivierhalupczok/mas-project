#include "Education.h"
#include <iostream>

Education::Education(const std::string& title, const std::string& institution,
                     const std::string& degree, int graduationYear)
    : CVSection(title), institution_(institution), degree_(degree),
      graduationYear_(graduationYear) {}

void Education::render() const {
    std::cout << "[Education] " << degree_ << " at " << institution_
              << " (" << graduationYear_ << ")\n"
              << "  " << title_ << "\n";
}

std::string Education::getType()          const { return "Education"; }
const std::string& Education::getInstitution() const { return institution_; }
const std::string& Education::getDegree()      const { return degree_; }
