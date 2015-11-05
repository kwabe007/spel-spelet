#include "matrix.hpp"
#include<stddef.h>

Matrix::Matrix() {
}

Matrix::Matrix(size_t n, size_t m) {
    cols = n;
    rows = m;
    out_ptr = new std::string*[cols];
    in_ptr = new std::string[rows];
}

Matrix::Matrix(const Matrix& ref){

}

std::string* Matrix::operator[](size_t i) const{
    return *(out_ptr + i);

}

Matrix::~Matrix() {
    for (unsigned int i = 0; i < cols; ++i) {
        delete[] *(out_ptr + i);
    }
    delete[] out_ptr;
}

void Matrix::fill_col(std::size_t col, std::string* ref){
    std::string* col_ptr = *(out_ptr + col);
    for (unsigned int i = 0; i < rows; ++i) {
        *(col_ptr + i) = *(ref + i);
    }
}

void Matrix::fill_row(std::size_t rw, std::string* ref){
    std::string** rw_ptr = out_ptr;
    for (unsigned int i = 0; i < cols; ++i, ++rw_ptr) {
        std::cerr << "accessing [" << i << "][" << rw_ptr-out_ptr << "]" << std::endl;
        out_ptr[0][0] = "hh";
        std::cerr << "aaaaa" << std::endl;
        std::cerr << out_ptr[0][0] << std::endl;
        *(*(rw_ptr) + rw) = *(ref + i);
    }
}

size_t Matrix::get_rows()const {
    return rows;
}

size_t Matrix::get_cols()const {
    return cols;
}

std::ostream& operator<<(std::ostream& os, const Matrix& mx) {
    std::string** out_ptr = mx.out_ptr;
    for (unsigned int i = 0; i < mx.cols; ++i) {
        os << *(*(out_ptr + i));
    }
    return os;
}

