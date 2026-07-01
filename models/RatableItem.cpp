#include "RatableItem.h"

RatableItem::RatableItem(int rating, int reviewCount)
    : rating_(rating), reviewCount_(reviewCount) {}

int RatableItem::getRating()      const { return rating_; }
int RatableItem::getReviewCount() const { return reviewCount_; }

std::string RatableItem::getRatingInfo() const {
    return std::to_string(rating_) + "/5 (" + std::to_string(reviewCount_) + " reviews)";
}
