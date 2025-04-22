#ifndef SHARP_FILTER_H
#define SHARP_FILTER_H

#include "filter.h"

class SharpFilter : public MatrixFilter {
public:
    ~SharpFilter() override = default;
    SharpFilter();
    bool Apply(Image* img) const override;

private:
    Matrix<double> m_ = {3, 3, 0.};
};

#endif  // SHARP_FILTER_H
