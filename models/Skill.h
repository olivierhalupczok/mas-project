#pragma once
#include <string>
#include "ITechnical.h"
#include "ISoft.h"

// Overlapping subclasses: a Skill can belong to multiple subtypes simultaneously.
// It may be purely technical, purely soft, or BOTH (e.g. "Technical Writing").
// Roles are held as optional pointers: nullptr means "not that subtype".
// One object instance can occupy overlapping subclasses without data duplication.
class Skill {
public:
    explicit Skill(const std::string& name, int proficiencyLevel);
    ~Skill();

    // Assign the technical role — marks this skill as belonging to the technical subtype.
    // Can coexist with a soft role (overlapping).
    void setTechnicalRole(ITechnical* role);

    // Assign the soft role — marks this skill as belonging to the soft subtype.
    // Can coexist with a technical role (overlapping).
    void setSoftRole(ISoft* role);

    bool isTechnical() const;   // true if technical role is set
    bool isSoft()      const;   // true if soft role is set

    const std::string& getName()             const;
    int                getProficiencyLevel() const;
    void print() const;

private:
    std::string name_;
    int         proficiencyLevel_;          // 1–5
    ITechnical* technicalRole_ = nullptr;   // nullptr = not a technical skill
    ISoft*      softRole_      = nullptr;   // nullptr = not a soft skill
};
