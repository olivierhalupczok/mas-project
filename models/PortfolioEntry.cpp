#include "PortfolioEntry.h"
#include <iostream>

PortfolioEntry::PortfolioEntry(const std::string& projectName,
                                const std::string& filePath, const std::string& mimeType,
                                int rating, int reviewCount)
    : MediaAttachment(filePath, mimeType), RatableItem(rating, reviewCount),
      projectName_(projectName) {}

PortfolioEntry::PortfolioEntry(int id, const std::string& projectName,
                                const std::string& filePath, const std::string& mimeType,
                                int rating, int reviewCount)
    : MediaAttachment(filePath, mimeType), RatableItem(rating, reviewCount),
      id_(id), projectName_(projectName) {}

int                PortfolioEntry::getId()          const { return id_; }
const std::string& PortfolioEntry::getProjectName() const { return projectName_; }

void PortfolioEntry::print() const {
    std::cout << "Portfolio: " << projectName_ << "\n"
              << "  File   : " << getFileInfo()   << "\n"
              << "  Rating : " << getRatingInfo() << "\n";
}
