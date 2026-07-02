#pragma once
#include "MediaAttachment.h"
#include "RatableItem.h"
#include <string>

// Multiple inheritance: PortfolioEntry IS-A MediaAttachment AND IS-A RatableItem.
// It inherits file-attachment capabilities from MediaAttachment and
// rating capabilities from RatableItem — two completely independent parent classes.
// No virtual inheritance needed here: no shared base, no diamond problem.
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
