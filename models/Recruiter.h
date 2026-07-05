#pragma once
#include <string>
#include <vector>

class Candidate;

// Binary association 1..*: one Recruiter manages many Candidates.
class Recruiter {
public:
    Recruiter(int id, const std::string& name, const std::string& email);

    int getId()                   const;
    const std::string& getName()  const;
    const std::string& getEmail() const;

    // Method overloading: assign by existing object or by creating inline.
    void assign(Candidate* candidate);
    void assign(const std::string& name, const std::string& email, const std::string& phone);

    const std::vector<Candidate*>& getCandidates() const;
    static const std::vector<Recruiter*>& getExtent();

private:
    int         id_;
    std::string name_;
    std::string email_;
    std::vector<Candidate*> candidates_;

    static std::vector<Recruiter*> extent_;
};
