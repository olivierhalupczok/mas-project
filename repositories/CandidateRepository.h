#pragma once

class CandidateRepository {
public:
    static void saveAll();
    static void loadAll();
    static void saveSkills();
    static void loadSkills();
    static void savePortfolios();
    static void loadPortfolios();
    // Note: CVDocuments owned by candidates — handled in CandidateRepository
    static void saveCVDocuments();
    static void loadCVDocuments();
};
