#pragma once
#include <string>

// Soft dimension of a skill; a Skill may implement this and ITechnical at once.
class ISoft {
public:
    virtual ~ISoft() = default;
    virtual std::string getSoftCategory() const = 0;        // e.g. "Communication", "Leadership"
};
