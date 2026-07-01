#pragma once
#include "ITechnical.h"

// Concrete implementation of the ITechnical interface.
// Assigned to a Skill to mark it as having a technical dimension (overlapping subtype).
class TechnicalSkillRole : public ITechnical {
public:
    explicit TechnicalSkillRole(const std::string& category);
    std::string getTechnicalCategory() const override;
private:
    std::string category_;
};
