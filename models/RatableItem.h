#pragma once
#include <string>

// Second parent class for multiple inheritance.
// Represents an item that can receive a star rating from reviewers.
// Completely independent from MediaAttachment — no shared base (no diamond).
class RatableItem {
public:
    RatableItem(int rating, int reviewCount);
    virtual ~RatableItem() = default;

    int getRating()      const;
    int getReviewCount() const;
    virtual std::string getRatingInfo() const;  // virtual — allows subclass override

private:
    int rating_;        // 1–5 stars
    int reviewCount_;
};
