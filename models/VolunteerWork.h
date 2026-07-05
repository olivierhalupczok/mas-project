#pragma once
#include "CVSection.h"

// Disjoint subclass of CVSection.
// Represents a volunteering activity. Disjoint from WorkExperience and Education.
class VolunteerWork : public CVSection {
public:
    VolunteerWork(const std::string& title, const std::string& organization,
                  const std::string& cause);

    void render() const override;           // polymorphic override
    std::string getType() const override;

    const std::string& getOrganization() const;
    const std::string& getCause()        const;

private:
    std::string organization_;
    std::string cause_;
};
