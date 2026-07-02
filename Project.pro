QT += core widgets sql
CONFIG += c++17
TARGET = RecruitmentManager
TEMPLATE = app

INCLUDEPATH += . third_party

SOURCES += main.cpp \
    models/Candidate.cpp \
    models/Company.cpp \
    models/Recruiter.cpp \
    models/JobPosting.cpp \
    models/Application.cpp \
    models/Interview.cpp \
    models/CVDocument.cpp \
    models/CVSection.cpp \
    models/WorkExperience.cpp \
    models/Education.cpp \
    models/VolunteerWork.cpp \
    models/Skill.cpp \
    models/TechnicalSkillRole.cpp \
    models/SoftSkillRole.cpp \
    models/MediaAttachment.cpp \
    models/RatableItem.cpp \
    models/PortfolioEntry.cpp \
    models/AppliedState.cpp \
    models/InterviewingState.cpp \
    models/HiredState.cpp \
    models/RejectedState.cpp \
    repositories/Database.cpp \
    repositories/CandidateRepository.cpp \
    repositories/CompanyRepository.cpp \
    repositories/RecruiterRepository.cpp \
    repositories/JobPostingRepository.cpp \
    repositories/ApplicationRepository.cpp \
    repositories/InterviewRepository.cpp \
    views/MainWindow.cpp \
    dialogs/NewCandidateDialog.cpp \
    dialogs/NewJobPostingDialog.cpp \
    dialogs/ApplyDialog.cpp \
    dialogs/AdvanceStatusDialog.cpp

HEADERS += \
    models/Candidate.h \
    models/Company.h \
    models/Recruiter.h \
    models/JobPosting.h \
    models/Application.h \
    models/Interview.h \
    models/CVDocument.h \
    models/CVSection.h \
    models/WorkExperience.h \
    models/Education.h \
    models/VolunteerWork.h \
    models/Skill.h \
    models/ITechnical.h \
    models/ISoft.h \
    models/TechnicalSkillRole.h \
    models/SoftSkillRole.h \
    models/MediaAttachment.h \
    models/RatableItem.h \
    models/PortfolioEntry.h \
    models/ApplicationState.h \
    models/AppliedState.h \
    models/InterviewingState.h \
    models/HiredState.h \
    models/RejectedState.h \
    repositories/Database.h \
    repositories/Records.h \
    repositories/CandidateRepository.h \
    repositories/CompanyRepository.h \
    repositories/RecruiterRepository.h \
    repositories/JobPostingRepository.h \
    repositories/ApplicationRepository.h \
    repositories/InterviewRepository.h \
    views/MainWindow.h \
    dialogs/NewCandidateDialog.h \
    dialogs/NewJobPostingDialog.h \
    dialogs/ApplyDialog.h \
    dialogs/AdvanceStatusDialog.h
