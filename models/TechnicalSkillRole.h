#pragma once
#include "ITechnical.h"

class TechnicalSkillRole : public ITechnical {
public:
    explicit TechnicalSkillRole(const std::string& category);
    std::string getTechnicalCategory() const override;
private:
    std::string category_;
};
