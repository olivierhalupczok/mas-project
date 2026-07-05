#include "SampleData.h"

#include "../models/Company.h"
#include "../models/Recruiter.h"
#include "../models/Candidate.h"
#include "../models/JobPosting.h"
#include "../models/Application.h"
#include "../models/Interview.h"
#include "../models/Skill.h"
#include "../models/TechnicalSkillRole.h"
#include "../models/SoftSkillRole.h"
#include "../models/PortfolioEntry.h"
#include "../models/CVDocument.h"
#include "../models/AppliedState.h"
#include "../models/InterviewingState.h"

void SampleData::seedIfEmpty() {
    if (!Candidate::getExtent().empty() || !Company::getExtent().empty()
        || !JobPosting::getExtent().empty())
        return;

    Company* acme = new Company(1, "Acme Software",
        Address{"12 Market St", "Warsaw", "Poland"}, "IT");
    Company* globex = new Company(2, "Globex Analytics",
        Address{"5 Data Ave", "Krakow", "Poland"}, "Analytics");

    Recruiter* rec = new Recruiter(1, "Anna Nowak", "anna@acme.example");

    Candidate* ewa = new Candidate(101, "Ewa Kowalczyk", "ewa@example.com", "600100200");
    ewa->setState(new InterviewingState());
    Skill* cpp = new Skill("C++", 5);
    cpp->setTechnicalRole(new TechnicalSkillRole("Programming"));
    ewa->addSkill(cpp);
    Skill* teamwork = new Skill("Teamwork", 4);
    teamwork->setSoftRole(new SoftSkillRole("Collaboration"));
    ewa->addSkill(teamwork);
    ewa->addPortfolioEntry(new PortfolioEntry(201, "Trading Engine",
        "portfolio/trading.pdf", "application/pdf", 5, 12));
    CVDocument* ewaCv = new CVDocument(301, "Ewa Kowalczyk", "PDF", "English");
    ewaCv->addWorkExperience("Backend Developer", "Fintech Sp. z o.o.",
        "2021-2024", "Built low-latency order matching services.");
    ewaCv->addEducation("Computer Science", "PJWSTK", "BSc", 2021);
    ewa->addCVDocument(ewaCv);
    rec->assign(ewa);

    Candidate* piotr = new Candidate(102, "Piotr Zając", "piotr@example.com", "600300400");
    piotr->setState(new AppliedState());
    Skill* sql = new Skill("SQL", 4);
    sql->setTechnicalRole(new TechnicalSkillRole("Databases"));
    piotr->addSkill(sql);
    CVDocument* piotrCv = new CVDocument(302, "Piotr Zając", "PDF", "Polish");
    piotrCv->addVolunteerWork("Coding Mentor", "Code Europe", "Education");
    piotr->addCVDocument(piotrCv);
    rec->assign(piotr);

    JobPosting* backend = new JobPosting(1001, "Senior C++ Engineer",
        "Own the core matching engine.", acme, SalaryRange{18000, 25000});
    JobPosting* analyst = new JobPosting(1002, "Data Analyst",
        "Build reporting pipelines.", globex, SalaryRange{12000, 16000});

    Application* app1 = new Application(5001, ewa, backend, "2024-05-10");
    new Application(5002, piotr, analyst, "2024-05-12");
    new Interview(6001, app1, "2024-05-20 10:00", "Warsaw HQ", "Technical round.");
}
