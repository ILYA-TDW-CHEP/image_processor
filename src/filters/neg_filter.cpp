#include "neg_filter.h"

bool NegFilter::Apply(Image* img) const {
    size_t x = img->GetWidth();
    size_t y = img->GetHeight();
    for (size_t i = 0; i < y; ++i) {
        for (size_t j = 0; j < x; ++j) {
            Pixel new_pixel = {1 - img->GetPixel(i, j)->b, 1 - img->GetPixel(i, j)->g, 1 - img->GetPixel(i, j)->r};
            img->SetPixel(j, i, new_pixel);
        }
    }
    return true;
}