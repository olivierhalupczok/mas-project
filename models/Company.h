#pragma once
#include <string>
#include <vector>

struct Address {
    std::string street;
    std::string city;
    std::string country;
};

class Company {
public:
    Company(int id, const std::string& name,
            const Address& address, const std::string& industry);

    int getId()                       const;
    const std::string& getName()      const;
    const Address& getAddress()       const;
    const std::string& getIndustry()  const;

    static const std::vector<Company*>& getExtent();
    static Company* findByName(const std::string& name);

    static int instanceCount;

private:
    int         id_;
    std::string name_;
    Address     address_;
    std::string industry_;

    static std::vector<Company*> extent_;
};
