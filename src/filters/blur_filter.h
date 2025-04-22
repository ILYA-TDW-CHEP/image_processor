#ifndef BLUR_FILTER_H
#define BLUR_FILTER_H

#include "filter.h"
#include <vector>

class BlurFilter : public BaseFilter {
public:
    ~BlurFilter() override = default;
    explicit BlurFilter(double sigma);
    bool Apply(Image* img) const override;
    void ApplyHoriz(Matrix<Pixel>& img, Matrix<Pixel>& temp, bool rotate) const;
    void CalculateCore();

protected:
    std::vector<double> core_;
    double sigma_;
    int radius_;
};

#endif  // BLUR_FILTER_H
