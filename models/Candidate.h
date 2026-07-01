#pragma once
#include <string>
#include "ApplicationState.h"

// Subject of dynamic inheritance via the Role pattern.
// Candidate's effective "subclass" is its current ApplicationState role object.
// setState() destroys the old role and assigns a new one — the object changes
// its runtime subclass without changing its C++ type (dynamic inheritance).
class Candidate {
public:
    Candidate(const std::string& name, const std::string& targetRole);
    ~Candidate();

    // Role swap: changes the effective subclass at runtime (dynamic inheritance).
    // Deletes the previous state and takes ownership of newState.
    void setState(ApplicationState* newState);

    std::string getStatusLabel() const;  // delegates to current state role
    std::string getNextAction()  const;  // delegates to current state role

    const std::string& getName()       const;
    const std::string& getTargetRole() const;
    void print() const;

private:
    std::string       name_;
    std::string       targetRole_;
    ApplicationState* state_;   // current role object (owned by Candidate)
};
