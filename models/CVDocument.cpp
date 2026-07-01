#include "CVDocument.h"
#include <iostream>

CVDocument::CVDocument(const std::string& ownerName) : ownerName_(ownerName) {}
const std::string& CVDocument::getOwnerName() const { return ownerName_; }

void CVDocument::print() const {
    std::cout << "CV of " << ownerName_
              << " | Format: "   << getFormatLabel()    // dispatched to format axis
              << " | Language: " << getLanguageLabel()  // dispatched to language axis
              << "\n";
}
