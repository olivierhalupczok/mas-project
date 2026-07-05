#pragma once
#include <string>
#include <vector>

class Application;

class Interview {
public:
    Interview(int id, Application* application,
              const std::string& scheduledAt, const std::string& location,
              const std::string& notes = "");

    int getId()                         const;
    Application* getApplication()       const;
    const std::string& getScheduledAt() const;
    const std::string& getLocation()    const;
    const std::string& getNotes()       const;

    static const std::vector<Interview*>& getExtent();

private:
    int          id_;
    Application* application_;
    std::string  scheduledAt_;
    std::string  location_;
    std::string  notes_;

    static std::vector<Interview*> extent_;
};
