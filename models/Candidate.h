#pragma once
#include <string>
#include <vector>
#include "ApplicationState.h"

class Skill;
class Application;
class PortfolioEntry;
class CVDocument;

class Candidate {
public:
    Candidate(int id, const std::string& name,
              const std::string& email, const std::string& phone);
    ~Candidate();

    int getId()                   const;
    const std::string& getName()  const;
    const std::string& getEmail() const;
    const std::string& getPhone() const;

    static int instanceCount;

    static const std::vector<Candidate*>& getExtent();
    static Candidate* findByName(const std::string& name);

    int getApplicationCount() const;

    void addSkill(Skill* skill);
    void addSkill(const std::string& name, int level);

    const std::vector<Skill*>& getSkills() const;

    // Swaps the state role object at runtime (dynamic inheritance).
    void setState(ApplicationState* newState);
    std::string getStatusLabel() const;
    std::string getNextAction()  const;

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
