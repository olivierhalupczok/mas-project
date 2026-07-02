#include "Skill.h"
#include <iostream>

Skill::Skill(const std::string& name, int proficiencyLevel)
    : name_(name), proficiencyLevel_(proficiencyLevel) {}

Skill::Skill(int id, const std::string& name, int proficiencyLevel)
    : id_(id), name_(name), proficiencyLevel_(proficiencyLevel) {}

Skill::~Skill() {
    delete technicalRole_;
    delete softRole_;
}

void Skill::setTechnicalRole(ITechnical* role) { delete technicalRole_; technicalRole_ = role; }
void Skill::setSoftRole(ISoft* role)           { delete softRole_;      softRole_      = role; }

bool Skill::isTechnical() const { return technicalRole_ != nullptr; }
bool Skill::isSoft()      const { return softRole_      != nullptr; }

int                Skill::getId()              const { return id_; }
const std::string& Skill::getName()             const { return name_; }
int                Skill::getProficiencyLevel() const { return proficiencyLevel_; }

void Skill::print() const {
    std::cout << "Skill: " << name_ << " (level " << proficiencyLevel_ << "/5)";
    if (isTechnical()) std::cout << " [Technical: " << technicalRole_->getTechnicalCategory() << "]";
    if (isSoft())      std::cout << " [Soft: "      << softRole_->getSoftCategory()           << "]";
    std::cout << "\n";
}
