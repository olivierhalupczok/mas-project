#pragma once
#include <string>

// Swappable role object: a Candidate delegates to one of these so its effective
// subclass can change at runtime without changing its C++ type (Role pattern).
class ApplicationState {
public:
    virtual ~ApplicationState() = default;
    virtual std::string getStatusLabel() const = 0;
    virtual std::string getNextAction()  const = 0;
};
