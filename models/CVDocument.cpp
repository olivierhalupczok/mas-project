#include "CVDocument.h"
#include "CVSection.h"
#include "WorkExperience.h"
#include "Education.h"
#include "VolunteerWork.h"
#include <algorithm>

std::vector<CVDocument*> CVDocument::extent_;

CVDocument::CVDocument(int id, const std::string& ownerName,
                       const std::string& format, const std::string& language)
    : id_(id), ownerName_(ownerName), format_(format), language_(language)
{
    extent_.push_back(this);
}

CVDocument::~CVDocument() {
    extent_.erase(std::remove(extent_.begin(), extent_.end(), this), extent_.end());
    for (auto* s : sections_) delete s;
}

int                CVDocument::getId()        const { return id_; }
const std::string& CVDocument::getOwnerName() const { return ownerName_; }
const std::string& CVDocument::getFormat()    const { return format_; }
const std::string& CVDocument::getLanguage()  const { return language_; }

CVSection* CVDocument::addWorkExperience(const std::string& title, const std::string& company,
                                          const std::string& period, const std::string& description) {
    auto* s = new WorkExperience(title, company, period, description);
    sections_.push_back(s);
    return s;
}

CVSection* CVDocument::addEducation(const std::string& title, const std::string& institution,
                                     const std::string& degree, int graduationYear) {
    auto* s = new Education(title, institution, degree, graduationYear);
    sections_.push_back(s);
    return s;
}

CVSection* CVDocument::addVolunteerWork(const std::string& title, const std::string& organization,
                                         const std::string& cause) {
    auto* s = new VolunteerWork(title, organization, cause);
    sections_.push_back(s);
    return s;
}

const std::vector<CVSection*>& CVDocument::getSections() const { return sections_; }

void CVDocument::renderAll() const {
    for (const CVSection* s : sections_)
        s->render();  // polymorphic dispatch — correct subclass render() called at runtime
}

const std::vector<CVDocument*>& CVDocument::getExtent() { return extent_; }
