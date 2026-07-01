#pragma once
#include "CVSection.h"

// Disjoint subclass of CVSection.
// Represents an academic qualification. Disjoint from WorkExperience and VolunteerWork —
// an Education object is never simultaneously a WorkExperience.
class Education : public CVSection {
public:
    Education(const std::string& title, const std::string& institution,
              const std::string& degree, int graduationYear);

    void render() const override;           // polymorphic override
    std::string getType() const override;

    const std::string& getInstitution() const;
    const std::string& getDegree()      const;

private:
    std::string institution_;
    std::string degree_;
    int graduationYear_;
};
