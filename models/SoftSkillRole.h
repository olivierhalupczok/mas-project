#pragma once
#include "ISoft.h"

class SoftSkillRole : public ISoft {
public:
    explicit SoftSkillRole(const std::string& category);
    std::string getSoftCategory() const override;
private:
    std::string category_;
};
