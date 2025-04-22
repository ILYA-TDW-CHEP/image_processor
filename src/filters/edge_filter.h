#ifndef EDGE_FILTER_H
#define EDGE_FILTER_H
#include "filter.h"

class EdgeFilter : public MatrixFilter {
public:
    ~EdgeFilter() override = default;
    explicit EdgeFilter(double threshold);
    bool Apply(Image* img) const override;

protected:
    Matrix<double> m_ = {3, 3, 0.};
    double threshold_;
};
#endif  // EDGE_FILTER_H
