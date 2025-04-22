#include "gs_filter.h"
#include "filter.h"

bool GsFilter::Apply(Image* img) const {
    size_t x = img->GetWidth();
    size_t y = img->GetHeight();
    for (size_t i = 0; i < y; ++i) {
        for (size_t j = 0; j < x; ++j) {
            constexpr double BlueCoeff = 0.114;
            constexpr double GreenCoeff = 0.587;
            constexpr double RedCoeff = 0.299;
            double coeff = RedCoeff * img->GetPixel(i, j)->r + GreenCoeff * img->GetPixel(i, j)->g +
                           BlueCoeff * img->GetPixel(i, j)->b;
            Pixel new_pixel = {coeff, coeff, coeff};
            img->SetPixel(j, i, new_pixel);
        }
    }
    return true;
}