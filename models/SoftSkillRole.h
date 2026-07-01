#pragma once
#include "ISoft.h"

// Concrete implementation of the ISoft interface.
// Assigned to a Skill to mark it as having a soft dimension (overlapping subtype).
class SoftSkillRole : public ISoft {
public:
    explicit SoftSkillRole(const std::string& category);
    std::string getSoftCategory() const override;
private:
    std::string category_;
};
