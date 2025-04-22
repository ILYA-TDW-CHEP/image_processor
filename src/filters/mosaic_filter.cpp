#include "mosaic_filter.h"

#include "sharp_filter.h"

bool MosaicFilter::Apply(Image* img) const {
    Matrix<Pixel> img_temp = *img->GetData();
    for (size_t y = 0; y < img->GetHeight(); y += dist_) {
        for (size_t x = 0; x < img->GetWidth(); x += dist_) {
            CalculateCell(img_temp, x, y);
        }
    }
    img->SetData(img_temp);
    SharpFilter filter;
    filter.Apply(img);
    filter.Apply(img);
    filter.Apply(img);
    return true;
}

void MosaicFilter::CalculateCell(Matrix<Pixel>& img, size_t x, size_t y) const {
    Pixel average_pixel{0., 0., 0.};
    int count = 0;
    for (size_t i = y; i < std::min(y + dist_, img.GetRowNum()); ++i) {
        for (size_t j = x; j < std::min(x + dist_, img.GetColNum()); ++j) {
            average_pixel = average_pixel + img.GetElement(i, j);
            ++count;
        }
    }
    if (count > 0) {
        average_pixel = average_pixel * (1. / count);
    }

    for (size_t i = y; i < std::min(y + dist_, img.GetRowNum()); ++i) {
        for (size_t j = x; j < std::min(x + dist_, img.GetColNum()); ++j) {
            img[i][j] = average_pixel;
        }
    }
}
