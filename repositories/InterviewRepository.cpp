#include "InterviewRepository.h"
#include "Database.h"
#include "../models/Interview.h"
#include "../models/Application.h"

namespace {
    template<typename T>
    T* findById(const std::vector<T*>& v, int id) {
        for (auto* p : v) if (p->getId() == id) return p;
        return nullptr;
    }
}

void InterviewRepository::saveAll() {
    auto& db = Database::instance().storage();
    db.remove_all<InterviewRecord>();
    for (auto* i : Interview::getExtent()) {
        InterviewRecord r;
        r.id            = i->getId();
        r.applicationId = i->getApplication()->getId();
        r.scheduledAt   = i->getScheduledAt();
        r.location      = i->getLocation();
        r.notes         = i->getNotes();
        db.replace(r);
    }
}

void InterviewRepository::loadAll() {
    auto& db = Database::instance().storage();
    for (auto& r : db.get_all<InterviewRecord>()) {
        auto* app = findById(Application::getExtent(), r.applicationId);
        new Interview(r.id, app, r.scheduledAt, r.location, r.notes);
    }
}
