#pragma once
#include "CVSection.h"

// Disjoint subclass of CVSection.
// An instance of WorkExperience is exclusively this type — it can never
// simultaneously be an Education or VolunteerWork (disjoint subclasses).
class WorkExperience : public CVSection {
public:
    WorkExperience(const std::string& title, const std::string& company,
                   const std::string& period, const std::string& description);

    void render() const override;           // polymorphic override of CVSection::render()
    std::string getType() const override;

    const std::string& getCompany() const;
    const std::string& getPeriod()  const;

private:
    std::string company_;
    std::string period_;
    std::string description_;
};
