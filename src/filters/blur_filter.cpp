#include "blur_filter.h"
#include <cmath>
#include <algorithm>

BlurFilter::BlurFilter(double s) {
    sigma_ = s;
    radius_ = ceil(3 * sigma_);
    core_ = std::vector<double>(2 * radius_ + 1);
    CalculateCore();
}

void BlurFilter::CalculateCore() {
    double sum = 0.;

    for (int i = 0; i < 2 * radius_ + 1; ++i) {
        core_[i] = exp(-(i - radius_) * (i - radius_) / (2 * sigma_ * sigma_));
        sum += core_[i];
    }
    for (int i = 0; i < 2 * radius_ + 1; ++i) {
        core_[i] /= sum;
    }
}
void BlurFilter::ApplyHoriz(Matrix<Pixel>& img, Matrix<Pixel>& temp, bool rotate) const {
    int width = static_cast<int>(img.GetColNum());
    int height = static_cast<int>(img.GetRowNum());
    if (rotate) {
        std::swap(width, height);
    }
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Pixel sum{};
            double weight_sum = 0.0;
            for (int i = -radius_; i < radius_ + 1; ++i) {
                int current_x = x;
                int current_y = y;
                if (!rotate) {
                    current_x = std::max(0, std::min(x + i, width - 1));
                } else {
                    current_y = std::max(0, std::min(y + i, height - 1));
                }
                double weight = core_[i + radius_];
                Pixel current_pixel = img[current_y][current_x];
                current_pixel = current_pixel * weight;
                sum = sum + current_pixel;
                weight_sum += weight;
            }
            temp[y][x] = sum / weight_sum;
        }
    }
}

bool BlurFilter::Apply(Image* img) const {
    Matrix<Pixel> temp(img->GetHeight(), img->GetWidth());

    ApplyHoriz(*img->GetData(), temp, false);
    ApplyHoriz(temp, *img->GetData(), true);

    return true;
}