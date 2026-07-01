#include "MediaAttachment.h"

MediaAttachment::MediaAttachment(const std::string& filePath, const std::string& mimeType)
    : filePath_(filePath), mimeType_(mimeType) {}

const std::string& MediaAttachment::getFilePath() const { return filePath_; }
const std::string& MediaAttachment::getMimeType() const { return mimeType_; }

std::string MediaAttachment::getFileInfo() const {
    return filePath_ + " (" + mimeType_ + ")";
}
