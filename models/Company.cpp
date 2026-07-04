#include "Company.h"
#include <algorithm>

std::vector<Company*> Company::extent_;
int Company::instanceCount = 0;

Company::Company(int id, const std::string& name,
                 const Address& address, const std::string& industry)
    : id_(id), name_(name), address_(address), industry_(industry) {
    extent_.push_back(this);
    ++instanceCount;
}

int                Company::getId()       const { return id_; }
const std::string& Company::getName()     const { return name_; }
const Address&     Company::getAddress()  const { return address_; }
const std::string& Company::getIndustry() const { return industry_; }

const std::vector<Company*>& Company::getExtent() { return extent_; }

Company* Company::findByName(const std::string& name) {
    auto it = std::find_if(extent_.begin(), extent_.end(),
        [&name](Company* c) { return c->getName() == name; });
    return it != extent_.end() ? *it : nullptr;
}
