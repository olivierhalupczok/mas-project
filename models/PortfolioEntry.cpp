#include "PortfolioEntry.h"
#include <iostream>

PortfolioEntry::PortfolioEntry(const std::string& projectName,
                                const std::string& filePath, const std::string& mimeType,
                                int rating, int reviewCount)
    : MediaAttachment(filePath, mimeType), RatableItem(rating, reviewCount),  // both parent ctors
      projectName_(projectName) {}

const std::string& PortfolioEntry::getProjectName() const { return projectName_; }

void PortfolioEntry::print() const {
    std::cout << "Portfolio: " << projectName_ << "\n"
              << "  File   : " << getFileInfo()   << "\n"   // from MediaAttachment
              << "  Rating : " << getRatingInfo() << "\n";  // from RatableItem
}
