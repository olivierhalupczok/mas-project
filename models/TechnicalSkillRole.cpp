#include "TechnicalSkillRole.h"

TechnicalSkillRole::TechnicalSkillRole(const std::string& category) : category_(category) {}

std::string TechnicalSkillRole::getTechnicalCategory() const { return category_; }
