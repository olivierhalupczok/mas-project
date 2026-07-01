#include "CVSection.h"

CVSection::CVSection(const std::string& title) : title_(title) {}

const std::string& CVSection::getTitle() const { return title_; }
