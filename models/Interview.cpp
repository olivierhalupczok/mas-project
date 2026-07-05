#include "Interview.h"

std::vector<Interview*> Interview::extent_;

Interview::Interview(int id, Application* application,
                     const std::string& scheduledAt, const std::string& location,
                     const std::string& notes)
    : id_(id), application_(application), scheduledAt_(scheduledAt),
      location_(location), notes_(notes) {
    extent_.push_back(this);
}

int          Interview::getId()            const { return id_; }
Application* Interview::getApplication()   const { return application_; }
const std::string& Interview::getScheduledAt() const { return scheduledAt_; }
const std::string& Interview::getLocation()    const { return location_; }
const std::string& Interview::getNotes()       const { return notes_; }

const std::vector<Interview*>& Interview::getExtent() { return extent_; }
