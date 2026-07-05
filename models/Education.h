#pragma once
#include "CVSection.h"

// An academic qualification entry in a CV.
class Education : public CVSection {
public:
    Education(const std::string& title, const std::string& institution,
              const std::string& degree, int graduationYear);

    void render() const override;
    std::string getType() const override;

    const std::string& getInstitution()  const;
    const std::string& getDegree()       const;
    int                getGraduationYear() const;

private:
    std::string institution_;
    std::string degree_;
    int graduationYear_;
};
