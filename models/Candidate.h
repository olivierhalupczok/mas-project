#pragma once
#include <string>
#include <vector>
#include "ApplicationState.h"

class Skill;
class Application;
class PortfolioEntry;
class CVDocument;

// Class with extension: Candidate tracks all instances in a static vector.
class Candidate {
public:
    Candidate(int id, const std::string& name,
              const std::string& email, const std::string& phone);
    ~Candidate();

    int getId()                   const;
    const std::string& getName()  const;
    const std::string& getEmail() const;
    const std::string& getPhone() const;

    // Class attribute: shared across all instances.
    static int instanceCount;

    // Class method: search the whole extension.
    static const std::vector<Candidate*>& getExtent();
    static Candidate* findByName(const std::string& name);

    // Derived attribute: computed from applications_, never stored.
    int getApplicationCount() const;

    // Method overloading: add a skill by object or by name + level.
    void addSkill(Skill* skill);
    void addSkill(const std::string& name, int level);

    // Repeatable attribute: a candidate has multiple skills.
    const std::vector<Skill*>& getSkills() const;

    // Dynamic inheritance: swap the ApplicationState role object at runtime.
    void setState(ApplicationState* newState);
    std::string getStatusLabel() const;
    std::string getNextAction()  const;

    // Association navigation.
    void addApplication(Application* app);
    const std::vector<Application*>& getApplications() const;

    void addPortfolioEntry(PortfolioEntry* entry);
    const std::vector<PortfolioEntry*>& getPortfolioEntries() const;

    void addCVDocument(CVDocument* doc);
    const std::vector<CVDocument*>& getCVDocuments() const;

private:
    int         id_;
    std::string name_;
    std::string email_;
    std::string phone_;

    ApplicationState*         state_ = nullptr;
    std::vector<Skill*>       skills_;
    std::vector<Application*> applications_;
    std::vector<PortfolioEntry*> portfolio_;
    std::vector<CVDocument*>     cvDocuments_;

    static std::vector<Candidate*> extent_;
};
