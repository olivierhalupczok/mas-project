#pragma once
#include <string>
#include <vector>
#include <map>
#include <optional>

class Application;
class Company;

// Optional composite attribute: salary range may be absent.
struct SalaryRange {
    double min;
    double max;
};

class JobPosting {
public:
    JobPosting(int id, const std::string& title, const std::string& description,
               Company* company,
               std::optional<SalaryRange> salaryRange = std::nullopt);

    int getId()                           const;
    const std::string& getTitle()         const;
    const std::string& getDescription()   const;
    Company* getCompany()                 const;
    const std::optional<SalaryRange>& getSalaryRange() const;  // optional attribute

    void addApplication(Application* app);
    const std::vector<Application*>& getApplications() const;

    static const std::vector<JobPosting*>& getExtent();
    // Qualified association: find a posting by title key.
    static JobPosting* findByTitle(const std::string& title);

private:
    int         id_;
    std::string title_;
    std::string description_;
    Company*    company_;
    std::optional<SalaryRange> salaryRange_;   // optional composite attribute

    std::vector<Application*> applications_;

    static std::vector<JobPosting*>           extent_;
    static std::map<std::string, JobPosting*> byTitle_;  // qualified association index
};
