#pragma once
#include <string>
#include <optional>

// Plain structs that sqlite_orm maps to database tables.
// Each mirrors one business class; the Repository layer converts between them.

struct CompanyRecord {
    int id = 0;
    std::string name;
    std::string street, city, country;
    std::string industry;
};

struct RecruiterRecord {
    int id = 0;
    std::string name;
    std::string email;
    int companyId = 0;
};

struct CandidateRecord {
    int id = 0;
    std::string name;
    std::string email;
    std::string phone;
    std::string status;
};

struct JobPostingRecord {
    int id = 0;
    std::string title;
    std::string description;
    std::optional<double> salaryMin;  // optional composite — two nullable columns
    std::optional<double> salaryMax;
    int companyId = 0;
    int recruiterId = 0;
};

struct ApplicationRecord {
    int id = 0;
    int candidateId = 0;
    int jobPostingId = 0;
    std::string appliedAt;
    std::optional<std::string> coverLetter;
};

struct InterviewRecord {
    int id = 0;
    int applicationId = 0;
    std::string scheduledAt;
    std::string location;
    std::string notes;
};

struct CVDocumentRecord {
    int id = 0;
    std::string ownerName;
    std::string format;
    std::string language;
    int candidateId = 0;
};

struct CVSectionRecord {
    int id = 0;
    std::string type;         // "WorkExperience" | "Education" | "VolunteerWork"
    std::string title;
    int cvDocumentId = 0;
    std::optional<std::string> company;
    std::optional<std::string> period;
    std::optional<std::string> description;
    std::optional<std::string> institution;
    std::optional<std::string> degree;
    std::optional<int>         graduationYear;
    std::optional<std::string> organization;
    std::optional<std::string> cause;
};

struct SkillRecord {
    int id = 0;
    std::string name;
    int proficiencyLevel = 1;
    int isTechnical = 0;
    std::optional<std::string> technicalCategory;
    int isSoft = 0;
    std::optional<std::string> softCategory;
    int candidateId = 0;
};

struct PortfolioEntryRecord {
    int id = 0;
    std::string projectName;
    std::string filePath;
    std::string mimeType;
    int rating = 0;
    int reviewCount = 0;
    int candidateId = 0;
};

struct RecruiterCandidateRecord {
    int recruiterId = 0;
    int candidateId = 0;
};
