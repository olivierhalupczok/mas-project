#pragma once
#include "CVSection.h"

// A volunteering activity entry in a CV.
class VolunteerWork : public CVSection {
public:
    VolunteerWork(const std::string& title, const std::string& organization,
                  const std::string& cause);

    void render() const override;
    std::string getType() const override;

    const std::string& getOrganization() const;
    const std::string& getCause()        const;

private:
    std::string organization_;
    std::string cause_;
};
