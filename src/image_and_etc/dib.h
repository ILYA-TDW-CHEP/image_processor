#ifndef DIB_H
#define DIB_H

#include "matrix.h"
#include "fstream"
#include <cstdint>

struct Pixel {
    double b;
    double g;
    double r;
    Pixel operator*(const double d) {
        b *= d;
        g *= d;
        r *= d;
        return *this;
    }
    Pixel operator/(const double d) {
        b /= d;
        g /= d;
        r /= d;
        return *this;
    }
    Pixel operator+(const Pixel& p) {
        b += p.b;
        g += p.g;
        r += p.r;
        return *this;
    }
};

struct BMPWrapper {
    struct BMPHeader {
        uint16_t sign;
        uint32_t size;
        uint16_t reserved_a;
        uint16_t reserved_b;
        uint32_t pixel_offset;
    } __attribute__((packed));

    struct DIBHeader {
        uint32_t size;
        uint32_t width;
        uint32_t height;
        uint16_t planes;
        uint16_t bpp;
        uint32_t compression;
        uint32_t imagesize;
        uint32_t horizontal_resolution;
        uint32_t vertical_resolution;
        uint32_t colors_used;
        uint32_t colors_important;
    } __attribute__((packed));

    explicit BMPWrapper(uint32_t width = 0, uint32_t height = 0);

    BMPHeader bmp_header_;
    DIBHeader dib_header_;
};

class Image {
public:
    bool ReadFromBMPFile(const std::string& file_name);
    bool ReadFromBMPStream(std::istream& istr);
    bool SaveToBMPFile(const std::string& file_name);
    bool SaveToBMPStream(std::ostream& ostr);

    Matrix<Pixel>* GetData() {
        return &img_;
    }
    Pixel* GetPixel(size_t x, size_t y) {
        return &img_[x][y];
    }
    Pixel* At(int row, int col);
    size_t GetWidth() const {
        return width_;
    }
    size_t GetHeight() const {
        return height_;
    }
    void SetWidth(const size_t width) {
        width_ = width;
    }
    void SetHeight(const size_t height) {
        height_ = height;
    }
    void SetData(Matrix<Pixel>& pixels) {
        img_.Swap(img_, pixels);
    }
    void SetPixel(const size_t x, const size_t y, const Pixel& pixel) {
        img_[y][x] = pixel;
    }

protected:
    Matrix<Pixel> img_;
    size_t width_ = 0;
    size_t height_ = 0;
};

#endif
