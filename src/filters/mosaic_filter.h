#ifndef MOSAIC_FILTER_H
#define MOSAIC_FILTER_H

#include "filter.h"

class MosaicFilter : public BaseFilter {
public:
    explicit MosaicFilter(size_t dist) : dist_{dist} {};
    ~MosaicFilter() override = default;
    bool Apply(Image* img) const override;
    size_t GetDist() const {
        return dist_;
    }
    void SetDist(size_t d) {
        dist_ = d;
    }

protected:
    size_t dist_;
    void CalculateCell(Matrix<Pixel>& img_temp, size_t x, size_t y) const;
};

#endif  // MOSAIC_FILTER_H
