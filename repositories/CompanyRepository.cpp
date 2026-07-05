#include "CompanyRepository.h"
#include "Database.h"
#include "../models/Company.h"

void CompanyRepository::saveAll() {
    auto& db = Database::instance().storage();
    db.remove_all<CompanyRecord>();
    for (auto* c : Company::getExtent()) {
        const Address& addr = c->getAddress();
        CompanyRecord r;
        r.id       = c->getId();
        r.name     = c->getName();
        r.street   = addr.street;
        r.city     = addr.city;
        r.country  = addr.country;
        r.industry = c->getIndustry();
        db.replace(r);
    }
}

void CompanyRepository::loadAll() {
    auto& db = Database::instance().storage();
    for (auto& r : db.get_all<CompanyRecord>()) {
        new Company(r.id, r.name, Address{r.street, r.city, r.country}, r.industry);
    }
}
