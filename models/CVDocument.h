#pragma once
#include <string>

// Common virtual base for the multi-aspect CV hierarchy.
// Virtual inheritance prevents a duplicate CVDocument subobject when
// DigitalEnglishCV inherits from both DigitalCV and EnglishCV (diamond topology).
// Each axis overrides one pure virtual method; the concrete class provides both.
class CVDocument {
public:
    explicit CVDocument(const std::string& ownerName);
    virtual ~CVDocument() = default;

    virtual std::string getFormatLabel()   const = 0;  // overridden by the format axis
    virtual std::string getLanguageLabel() const = 0;  // overridden by the language axis

    const std::string& getOwnerName() const;
    void print() const;

protected:
    std::string ownerName_;
};
