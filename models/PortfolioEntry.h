#pragma once
#include "MediaAttachment.h"
#include "RatableItem.h"
#include <string>

// Inherits from two independent parents; no virtual inheritance needed since
// they share no base, so there is no diamond.
class PortfolioEntry : public MediaAttachment, public RatableItem {
public:
    PortfolioEntry(const std::string& projectName,
                   const std::string& filePath, const std::string& mimeType,
                   int rating, int reviewCount);
    PortfolioEntry(int id, const std::string& projectName,
                   const std::string& filePath, const std::string& mimeType,
                   int rating, int reviewCount);

    int                getId()          const;
    const std::string& getProjectName() const;
    void print() const;

private:
    int         id_ = 0;
    std::string projectName_;
};
