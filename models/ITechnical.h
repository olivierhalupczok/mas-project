#pragma once
#include <string>

// Interface (pure abstract class) for the technical dimension of a skill.
// A Skill can optionally hold a TechnicalSkillRole that implements this interface.
// Used for overlapping subclasses: a Skill can be ITechnical AND ISoft simultaneously.
class ITechnical {
public:
    virtual ~ITechnical() = default;
    virtual std::string getTechnicalCategory() const = 0;   // e.g. "Backend", "DevOps"
};
