#pragma once
#include <string>
#include <vector>

class CVSection;

// Composition: CVDocument owns its CVSections.
// Sections are created via factory methods — they cannot be constructed independently.
// format and language are plain string attributes (multi-aspect hierarchy dropped).
class CVDocument {
public:
    CVDocument(int id, const std::string& ownerName,
               const std::string& format, const std::string& language);
    ~CVDocument();

    int getId()                       const;
    const std::string& getOwnerName() const;
    const std::string& getFormat()    const;
    const std::string& getLanguage()  const;

    // Factory methods enforce composition: sections belong to this document.
    CVSection* addWorkExperience(const std::string& title, const std::string& company,
                                  const std::string& period, const std::string& description);
    CVSection* addEducation(const std::string& title, const std::string& institution,
                             const std::string& degree, int graduationYear);
    CVSection* addVolunteerWork(const std::string& title, const std::string& organization,
                                 const std::string& cause);

    const std::vector<CVSection*>& getSections() const;
    void renderAll() const;  // polymorphic dispatch to each section

private:
    int         id_;
    std::string ownerName_;
    std::string format_;
    std::string language_;
    std::vector<CVSection*> sections_;  // owned parts (composition)
};
