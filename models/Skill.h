#pragma once
#include <string>
#include "ITechnical.h"
#include "ISoft.h"

// A Skill can hold a technical role, a soft role, or both at once — overlapping
// subtypes are modelled as optional roles rather than by duplicating the object.
class Skill {
public:
    explicit Skill(const std::string& name, int proficiencyLevel);
    Skill(int id, const std::string& name, int proficiencyLevel);
    ~Skill();

    void setTechnicalRole(ITechnical* role);
    void setSoftRole(ISoft* role);

    bool isTechnical() const;
    bool isSoft()      const;

    int                getId()              const;
    const std::string& getName()             const;
    int                getProficiencyLevel() const;
    void print() const;

private:
    int         id_ = 0;
    std::string name_;
    int         proficiencyLevel_;
    ITechnical* technicalRole_ = nullptr;
    ISoft*      softRole_      = nullptr;
};
