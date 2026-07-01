#pragma once
#include <string>

// Interface for the swappable role object used in dynamic inheritance.
// Each concrete state represents a runtime "subclass" of Candidate.
// Swapping the state object changes the Candidate's effective subclass without
// changing its C++ type — this is the Role pattern for dynamic inheritance.
class ApplicationState {
public:
    virtual ~ApplicationState() = default;
    virtual std::string getStatusLabel() const = 0;  // current status name
    virtual std::string getNextAction()  const = 0;  // what happens next in this state
};
