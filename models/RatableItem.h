#pragma once
#include <string>

// An item that can receive a star rating from reviewers.
class RatableItem {
public:
    RatableItem(int rating, int reviewCount);
    virtual ~RatableItem() = default;

    int getRating()      const;
    int getReviewCount() const;
    virtual std::string getRatingInfo() const;

private:
    int rating_;
    int reviewCount_;
};
