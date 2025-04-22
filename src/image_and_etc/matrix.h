#ifndef MATRIX_H
#define MATRIX_H

#include <cstddef>
#include <stdexcept>
#include <utility>

template <typename T>
class Matrix {
public:
    class Row {
        friend class Matrix;

    protected:
        Row(Matrix* owner, size_t num) : owner_(owner), num_(num) {
        }

    public:
        T& operator[](size_t pos) {
            return owner_->GetElement(num_, pos);
        }

        const T& operator[](size_t pos) const {
            return owner_->GetElement(num_, pos);
        }

        size_t GetNum() const {
            return num_;
        }

        size_t GetSize() const {
            return owner_->GetColNum();
        }

    protected:
        Matrix* owner_;
        size_t num_;
    };

    class ConstRow {
        friend class Matrix;

    protected:
        ConstRow(const Matrix* owner, size_t num) : owner_(owner), num_(num) {
        }

    public:
        const T& operator[](size_t pos) const {
            return owner_->GetElement(num_, pos);
        }

        size_t GetNum() const {
            return num_;
        }

        size_t GetSize() const {
            return owner_->GetColNum();
        }

    protected:
        const Matrix* owner_;
        size_t num_;
    };

public:
    Matrix() : ptr_(nullptr), col_num_(0), row_num_(0) {
    }

    Matrix(size_t rows_num, size_t cols_num) : Matrix() {
        if (rows_num == 0 && cols_num == 0) {
            return;
        }
        col_num_ = cols_num;
        row_num_ = rows_num;
        ptr_ = new T[CalcSize()];
    }

    Matrix(size_t rows_num, size_t cols_num, const T& def) : Matrix(rows_num, cols_num) {
        if (!ptr_) {
            return;
        }
        for (size_t i = 0; i < CalcSize(); ++i) {
            ptr_[i] = def;
        }
    }

    Matrix(const Matrix& other)
        : ptr_(other.ptr_ ? new T[other.row_num_ * other.col_num_] : nullptr),
          col_num_(other.col_num_),
          row_num_(other.row_num_) {
        CopyElementsFromMatrix(other);
    }

    ~Matrix() {
        delete[] ptr_;
    }

    Row operator[](size_t row_index) {
        return Row{this, row_index};
    }

    ConstRow operator[](size_t row_index) const {
        return ConstRow{this, row_index};
    }

    bool operator==(const Matrix& other) const {
        if (row_num_ != other.row_num_ || col_num_ != other.col_num_) {
            return false;
        }
        for (size_t i = 0; i < CalcSize(); ++i) {
            if (ptr_[i] != other.ptr_[i]) {
                return false;
            }
        }
        return true;
    }

    Matrix& operator=(const Matrix& rhs) {
        if (this == &rhs) {
            return *this;
        }
        Matrix temp(rhs);
        Swap(temp, *this);
        return *this;
    }

    size_t CalcOffset(size_t i, size_t j) const {
        return col_num_ * i + j;
    }

    size_t CalcSize() const {
        return col_num_ * row_num_;
    }

    T& GetElement(size_t i, size_t j) {
        return ptr_[CalcOffset(i, j)];
    }

    const T& GetElement(size_t i, size_t j) const {
        return ptr_[CalcOffset(i, j)];
    }

    void CopyElementsFromMatrix(const Matrix& other) {
        for (size_t i = 0; i < CalcSize(); ++i) {
            ptr_[i] = other.ptr_[i];
        }
    }

    T& At(size_t i, size_t j) {
        if (i >= row_num_ || j >= col_num_) {
            throw std::out_of_range("Given index out of bounds.");
        }
        return ptr_[CalcOffset(i, j)];
    }

    size_t GetRowNum() const {
        return row_num_;
    }

    size_t GetColNum() const {
        return col_num_;
    }

    static void Swap(Matrix& m1, Matrix& m2) noexcept {
        std::swap(m1.ptr_, m2.ptr_);
        std::swap(m1.row_num_, m2.row_num_);
        std::swap(m1.col_num_, m2.col_num_);
    }

protected:
    T* ptr_;
    size_t col_num_;
    size_t row_num_;
};

#endif  // MATRIX_H