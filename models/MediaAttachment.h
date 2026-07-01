#pragma once
#include <string>

// First parent class for multiple inheritance.
// Represents a file that can be attached to a profile (PDF, image, video, etc.).
class MediaAttachment {
public:
    MediaAttachment(const std::string& filePath, const std::string& mimeType);
    virtual ~MediaAttachment() = default;

    const std::string& getFilePath() const;
    const std::string& getMimeType() const;
    virtual std::string getFileInfo() const;    // virtual — allows subclass override

private:
    std::string filePath_;
    std::string mimeType_;
};
