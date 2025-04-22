#include "dib.h"

#include <fstream>
#include <vector>
#include <iostream>

constexpr uint16_t BMPSign = 0x4d42;
constexpr uint16_t BitPerPixel = 24;
constexpr size_t BmpHeaderSize = 14;
constexpr size_t DibHeaderSize = 40;
constexpr double ColorDepth = 255.;

bool Image::ReadFromBMPFile(const std::string& file_name) {
    std::ifstream file(file_name, std::ios_base::in | std::ios_base::binary);
    if (!file.is_open()) {
        return false;
    }
    return ReadFromBMPStream(file);
}

bool Image::ReadFromBMPStream(std::istream& istr) {
    if (!istr.good()) {
        return false;
    }
    BMPWrapper::BMPHeader bmp_header;
    BMPWrapper::DIBHeader dib_header;

    istr.read(reinterpret_cast<char*>(&bmp_header), BmpHeaderSize);
    if (bmp_header.sign != BMPSign) {
        std::cerr << "BMP header doesn't match expected format." << std::endl;
        return false;
    }
    istr.read(reinterpret_cast<char*>(&dib_header), DibHeaderSize);

    width_ = dib_header.width;
    height_ = dib_header.height;
    img_ = Matrix<Pixel>(height_, width_);
    const size_t row_size = ((width_ * 3 + 3) / 4) * 4;
    std::vector<uint8_t> row(row_size);
    for (size_t y = 0; y < height_; ++y) {
        istr.read(reinterpret_cast<char*>(row.data()), static_cast<int64_t>(row_size));
        for (size_t x = 0; x < width_; ++x) {
            img_[y][x].b = row[x * 3] / ColorDepth;
            img_[y][x].g = row[x * 3 + 1] / ColorDepth;
            img_[y][x].r = row[x * 3 + 2] / ColorDepth;
        }
    }
    return true;
}

bool Image::SaveToBMPFile(const std::string& file_name) {
    std::ofstream file(file_name, std::ios_base::out | std::ios_base::binary);
    if (!file.is_open()) {
        return false;
    }
    return SaveToBMPStream(file);
}

bool Image::SaveToBMPStream(std::ostream& ostr) {
    if (!ostr.good()) {
        return false;
    }
    const BMPWrapper bmp_wrapper{static_cast<uint32_t>(width_), static_cast<uint32_t>(height_)};
    constexpr size_t BmpHeaderSize = 14;
    constexpr size_t DibHeaderSize = 40;

    ostr.write(reinterpret_cast<const char*>(&bmp_wrapper.bmp_header_), BmpHeaderSize);
    ostr.write(reinterpret_cast<const char*>(&bmp_wrapper.dib_header_), DibHeaderSize);

    const size_t row_size = ((width_ * 3 + 3) / 4) * 4;

    std::vector<uint8_t> row(row_size, 0);

    for (size_t y = 0; y < height_; ++y) {
        for (size_t x = 0; x < width_; ++x) {
            row[x * 3] = static_cast<uint8_t>(img_[y][x].b * ColorDepth);
            row[x * 3 + 1] = static_cast<uint8_t>(img_[y][x].g * ColorDepth);
            row[x * 3 + 2] = static_cast<uint8_t>(img_[y][x].r * ColorDepth);
        }
        ostr.write(reinterpret_cast<const char*>(row.data()), static_cast<int64_t>(row_size));
    }
    return ostr.good();
}

BMPWrapper::BMPWrapper(const uint32_t width, const uint32_t height) {
    bmp_header_.sign = BMPSign;
    bmp_header_.size = sizeof(BMPHeader) + sizeof(DIBHeader) + width * height * 3;
    bmp_header_.reserved_a = 0;
    bmp_header_.reserved_b = 0;
    bmp_header_.pixel_offset = sizeof(BMPHeader) + sizeof(DIBHeader);

    dib_header_.size = sizeof(DIBHeader);
    dib_header_.width = width;
    dib_header_.height = height;
    dib_header_.planes = 1;
    dib_header_.bpp = BitPerPixel;
    dib_header_.compression = 0;
    dib_header_.imagesize = width * height * 3;
    dib_header_.horizontal_resolution = 0;
    dib_header_.vertical_resolution = 0;
    dib_header_.colors_used = 0;
    dib_header_.colors_important = 0;
}

Pixel* Image::At(int row, int col) {
    int width = static_cast<int>(width_);
    int height = static_cast<int>(height_);
    if (row < 0 && col < 0) {
        return &img_[0][0];
    }
    if (row < 0 && col >= width) {
        return &img_[0][width - 1];
    }
    if (row < 0) {
        return &img_[0][col];
    }
    if (row >= height && col < 0) {
        return &img_[height - 1][0];
    }
    if (row >= height && col >= width) {
        return &img_[height - 1][width - 1];
    }
    if (row >= height) {
        return &img_[height - 1][col];
    }
    if (col < 0) {
        return &img_[row][0];
    }
    if (col >= width) {
        return &img_[row][width - 1];
    }
    return &img_[row][col];
}
