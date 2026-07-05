#pragma once
#include <string>

// A file attached to a profile (PDF, image, video, etc.).
class MediaAttachment {
public:
    MediaAttachment(const std::string& filePath, const std::string& mimeType);
    virtual ~MediaAttachment() = default;

    const std::string& getFilePath() const;
    const std::string& getMimeType() const;
    virtual std::string getFileInfo() const;

private:
    std::string filePath_;
    std::string mimeType_;
};
