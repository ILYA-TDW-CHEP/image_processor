#include "crop_filter.h"
#include <iostream>

bool CropFilter::Apply(Image* img) const {
    if (y_ <= 0 || x_ <= 0) {
        std::cerr << "Crop arguments must be positive" << std::endl;
        return false;
    }
    size_t y = std::min(y_, img->GetHeight() - 1);
    size_t x = std::min(x_, img->GetWidth() - 1);
    Matrix<Pixel> img_tmp(y, x);
    size_t ver_offset = img->GetHeight() - y;
    for (size_t i = 0; i < y; ++i) {
        for (size_t j = 0; j < x; ++j) {
            img_tmp[i][j] = *img->GetPixel(ver_offset + i, j);
        }
    }
    img->SetData(img_tmp);
    img->SetWidth(x);
    img->SetHeight(y);
    return true;
}