#pragma once
#include <string>

// Interface (pure abstract class) for the soft dimension of a skill.
// A Skill can optionally hold a SoftSkillRole that implements this interface.
// Used for overlapping subclasses: a Skill can be ISoft AND ITechnical simultaneously.
class ISoft {
public:
    virtual ~ISoft() = default;
    virtual std::string getSoftCategory() const = 0;        // e.g. "Communication", "Leadership"
};
