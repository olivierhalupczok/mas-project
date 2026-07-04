#pragma once
#include <string>
#include <vector>

// Composite attribute: Address groups street, city, country into one object.
struct Address {
    std::string street;
    std::string city;
    std::string country;
};

// Class with extension: Company tracks all instances in a static vector.
class Company {
public:
    Company(int id, const std::string& name,
            const Address& address, const std::string& industry);

    int getId()                       const;
    const std::string& getName()      const;
    const Address& getAddress()       const;
    const std::string& getIndustry()  const;

    // Class method: operates on the whole extension.
    static const std::vector<Company*>& getExtent();
    static Company* findByName(const std::string& name);

    // Class attribute: total Company instances ever created.
    static int instanceCount;

private:
    int         id_;
    std::string name_;
    Address     address_;   // composite attribute
    std::string industry_;

    static std::vector<Company*> extent_;
};
