#pragma once
#include "CVSection.h"

class WorkExperience : public CVSection {
public:
    WorkExperience(const std::string& title, const std::string& company,
                   const std::string& period, const std::string& description);

    void render() const override;
    std::string getType() const override;

    const std::string& getCompany()      const;
    const std::string& getPeriod()       const;
    const std::string& getDescription()  const;

private:
    std::string company_;
    std::string period_;
    std::string description_;
};
