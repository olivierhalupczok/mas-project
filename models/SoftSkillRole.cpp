#include "SoftSkillRole.h"

SoftSkillRole::SoftSkillRole(const std::string& category) : category_(category) {}

std::string SoftSkillRole::getSoftCategory() const { return category_; }
