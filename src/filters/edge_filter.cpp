#include "edge_filter.h"
#include "filter.h"
#include "gs_filter.h"

EdgeFilter::EdgeFilter(double th) {
    constexpr double EdgeCoeff = 4.;
    m_[0][1] = -1;
    m_[2][1] = -1;
    m_[1][0] = -1;
    m_[1][2] = -1;
    m_[1][1] = EdgeCoeff;
    threshold_ = th;
}
bool EdgeFilter::Apply(Image* img) const {
    GsFilter filter;
    filter.Apply(img);
    MatrixFilter filter2;
    filter2.SetMatrix(m_);
    filter2.Apply(img);
    Matrix<Pixel> img_tmp(*img->GetData());
    for (size_t y = 0; y < img->GetHeight(); ++y) {
        for (size_t x = 0; x < img->GetWidth(); ++x) {
            Pixel* pixel = img->GetPixel(y, x);
            if (pixel->b > threshold_) {
                img_tmp[y][x] = Pixel{1, 1, 1};
            } else {
                img_tmp[y][x] = Pixel{0, 0, 0};
            }
        }
    }
    img->SetData(img_tmp);
    return true;
}