#include "sharp_filter.h"

SharpFilter::SharpFilter() : MatrixFilter() {
    constexpr double SharpCoeff = 5.;
    m_[0][1] = -1;
    m_[2][1] = -1;
    m_[1][0] = -1;
    m_[1][2] = -1;
    m_[1][1] = SharpCoeff;
}

bool SharpFilter::Apply(Image* img) const {
    MatrixFilter filter2;
    filter2.SetMatrix(m_);
    filter2.Apply(img);
    return true;
}
