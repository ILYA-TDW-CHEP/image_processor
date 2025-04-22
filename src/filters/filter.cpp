#include "filter.h"
#include "../image_and_etc/matrix.h"
#include "../image_and_etc/dib.h"
#include "iostream"

bool MatrixFilter::Apply(Image* img) const {
    Matrix<Pixel> img_tmp(img->GetHeight(), img->GetWidth());
    for (int y = 0; y < static_cast<int>(img->GetHeight()); ++y) {
        for (int x = 0; x < static_cast<int>(img->GetWidth()); ++x) {
            const Pixel current = *img->GetPixel(y, x);
            const Pixel top = *img->At(y - 1, x);
            const Pixel left = *img->At(y, x - 1);
            const Pixel bottom = *img->At(y + 1, x);
            const Pixel right = *img->At(y, x + 1);
            double new_r = std::min(1., std::max(0., (m_[1][1] * current.r + m_[0][1] * top.r + m_[1][0] * left.r +
                                                      m_[2][1] * bottom.r + m_[1][2] * right.r)));
            double new_g = std::min(1., std::max(0., (m_[1][1] * current.g + m_[0][1] * top.g + m_[1][0] * left.g +
                                                      m_[2][1] * bottom.g + m_[1][2] * right.g)));
            double new_b = std::min(1., std::max(0., (m_[1][1] * current.b + m_[0][1] * top.b + m_[1][0] * left.b +
                                                      m_[2][1] * bottom.b + m_[1][2] * right.b)));

            img_tmp[y][x] = Pixel{new_b, new_g, new_r};
        }
    }
    img->SetData(img_tmp);
    return true;
}
