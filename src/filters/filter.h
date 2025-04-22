#ifndef FILTER_H
#define FILTER_H

#include "../image_and_etc/dib.h"

class BaseFilter {
public:
    virtual ~BaseFilter() = default;
    virtual bool Apply(Image* img) const = 0;
};

class MatrixFilter : public BaseFilter {
public:
    MatrixFilter() = default;
    ~MatrixFilter() override = default;
    bool Apply(Image* img) const override;
    void SetMatrix(const Matrix<double>& m) {
        m_ = m;
    };

protected:
    Matrix<double> m_;
};

#endif  // FILTER_H
