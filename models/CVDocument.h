#pragma once
#include <string>
#include <vector>

class CVSection;

// Owns its CVSections: they can only be created through the factory methods
// below, never independently, so their lifetime is tied to the document.
class CVDocument {
public:
    CVDocument(int id, const std::string& ownerName,
               const std::string& format, const std::string& language);
    ~CVDocument();

    int getId()                       const;
    const std::string& getOwnerName() const;
    const std::string& getFormat()    const;
    const std::string& getLanguage()  const;

    CVSection* addWorkExperience(const std::string& title, const std::string& company,
                                  const std::string& period, const std::string& description);
    CVSection* addEducation(const std::string& title, const std::string& institution,
                             const std::string& degree, int graduationYear);
    CVSection* addVolunteerWork(const std::string& title, const std::string& organization,
                                 const std::string& cause);

    const std::vector<CVSection*>& getSections() const;
    void renderAll() const;

    static const std::vector<CVDocument*>& getExtent();

private:
    int         id_;
    std::string ownerName_;
    std::string format_;
    std::string language_;
    std::vector<CVSection*> sections_;

    static std::vector<CVDocument*> extent_;
};
