#ifndef CROP_FILTER_H
#define CROP_FILTER_H

#include "filter.h"

class CropFilter : public BaseFilter {
public:
    CropFilter(size_t x, size_t y) : x_{x}, y_{y} {};
    ~CropFilter() override = default;

public:
    bool Apply(Image* img) const override;

public:
    size_t GetX() const {
        return x_;
    }
    size_t GetY() const {
        return y_;
    }
    void SetX(size_t x) {
        x_ = x;
    }
    void SetY(size_t y) {
        y_ = y;
    }

protected:
    size_t x_;
    size_t y_;
};

#endif  // CROP_FILTER_H
