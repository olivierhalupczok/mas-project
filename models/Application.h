#pragma once
#include <string>
#include <optional>
#include <vector>

class Candidate;
class JobPosting;

// Link class between Candidate and JobPosting, holding data that belongs to the
// link itself. The constructor wires back-references on both ends.
class Application {
public:
    Application(int id, Candidate* candidate, JobPosting* jobPosting,
                const std::string& appliedAt,
                std::optional<std::string> coverLetter = std::nullopt);

    int getId()                                       const;
    Candidate*  getCandidate()                        const;
    JobPosting* getJobPosting()                       const;
    const std::string& getAppliedAt()                 const;
    const std::optional<std::string>& getCoverLetter() const;

    static const std::vector<Application*>& getExtent();

private:
    int         id_;
    Candidate*  candidate_;
    JobPosting* jobPosting_;
    std::string appliedAt_;
    std::optional<std::string> coverLetter_;

    static std::vector<Application*> extent_;
};
