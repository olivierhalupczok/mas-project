#pragma once
#include <string>

// Abstract base for CV sections.
class CVSection {
    friend class CVDocument;  // only CVDocument's factory methods may construct sections
public:
    virtual ~CVSection() = default;

    virtual void render() const = 0;
    virtual std::string getType() const = 0;

    const std::string& getTitle() const;

protected:
    explicit CVSection(const std::string& title);
    std::string title_;
};
