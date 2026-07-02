#pragma once
#include <string>

// Abstract base class for all CV sections.
// Declares pure virtual render() — subclasses MUST override it.
// CVSection cannot be instantiated directly (abstract class).
class CVSection {
    friend class CVDocument;  // only CVDocument's factory methods may construct sections
public:
    virtual ~CVSection() = default;

    // Pure virtual method — forces each subclass to implement its own rendering.
    // Polymorphic dispatch: calling render() on a CVSection* invokes the correct subclass version.
    virtual void render() const = 0;

    // Pure virtual — each subclass returns its own type label (used to confirm disjoint).
    virtual std::string getType() const = 0;

    const std::string& getTitle() const;

protected:
    explicit CVSection(const std::string& title);
    std::string title_;
};
