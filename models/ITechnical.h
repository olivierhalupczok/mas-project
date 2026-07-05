#pragma once
#include <string>

// Technical dimension of a skill; a Skill may implement this and ISoft at once.
class ITechnical {
public:
    virtual ~ITechnical() = default;
    virtual std::string getTechnicalCategory() const = 0;   // e.g. "Backend", "DevOps"
};
