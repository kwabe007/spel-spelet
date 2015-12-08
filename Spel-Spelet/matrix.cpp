#include <algorithm>
#include <stddef.h>
#include "matrix.hpp"

Matrix::Matrix() {
}

Matrix::Matrix(size_t n, size_t m) {
    cols = n;
    rows = m;
    allocate();
}

Matrix::Matrix(const Matrix& ref){

}

char* Matrix::operator[](size_t pos) const{
    if (pos > rows) throw std::out_of_range ("unable to access row, out of range");
    return *(out_ptr + pos);
}

Matrix::~Matrix() {
    for (unsigned int i = 0; i < rows; ++i) {
        delete[] *(out_ptr + i);
    }
    delete[] out_ptr;
}

void Matrix::fill_row(std::size_t rw, const char* ref){
    if (rw > rows) {

        throw std::out_of_range ("row index out of range: " + std::to_string(rw) + " outside " + std::to_string(rows));
    }
    char* in_ptr = *(out_ptr + rw);
    for (unsigned int i = 0; i < cols; ++i) {
        *(in_ptr + i) = *(ref + i);
    }
}

void Matrix::fill_row(std::size_t rw, const char* ref, std::size_t length){
    if (rw > rows) {

        throw std::out_of_range ("row index out of range: " + std::to_string(rw) + " outside " + std::to_string(rows));
    }
    char* in_ptr = *(out_ptr + rw);
    for (unsigned int i = 0; i < length; ++i) {
        *(in_ptr + i) = *(ref + i);
    }
}

void Matrix::fill_row(std::size_t rw, const char* ref, std::size_t length, std::size_t offset, bool prefill){
    if (rw > rows) {

        throw std::out_of_range ("row index out of range: " + std::to_string(rw) + " outside " + std::to_string(rows));
    }
    char* in_ptr = *(out_ptr + rw);
    if (prefill) {
        for (unsigned int i = 0; i < offset; ++i) {
            *(in_ptr + i) = ' ';
        }
    }
    for (unsigned int j = 0; j < length; ++j) {
        *(in_ptr + j + offset) = *(ref + j);
    }
}

void Matrix::fill_row(std::size_t rw, char ch){
    if (rw > rows) {

        throw std::out_of_range ("row index out of range: " + std::to_string(rw) + " outside " + std::to_string(rows));
    }
    char* in_ptr = *(out_ptr + rw);
    for (unsigned int i = 0; i < cols; ++i) {

        *(in_ptr + i) = ch;
    }
}

void Matrix::fill_row(std::size_t rw, char ch, std::size_t length){
    if (rw > rows) {

        throw std::out_of_range ("row index out of range: " + std::to_string(rw) + " outside " + std::to_string(rows));
    }
    char* in_ptr = *(out_ptr + rw);
    for (unsigned int i = 0; i < length; ++i) {
        *(in_ptr + i) = ch;
    }
}

void Matrix::fill_row(std::size_t rw, char ch, std::size_t length, std::size_t offset, bool prefill){
    if (rw > rows) {

        throw std::out_of_range ("row index out of range: " + std::to_string(rw) + " outside " + std::to_string(rows));
    }
    char* in_ptr = *(out_ptr + rw);
    if (prefill) {
        for (unsigned int i = 0; i < offset; ++i) {
            *(in_ptr + i) = ' ';
        }
    }
    for (unsigned int j = 0; j < length; ++j) {
        *(in_ptr + j + offset) = ch;
    }
}

size_t Matrix::get_rows()const {
    return rows;
}

size_t Matrix::get_cols()const {
    return cols;
}

void Matrix::allocate() {
    out_ptr = new char*[rows];
    for (unsigned int i = 0; i < rows; ++i) {
        *(out_ptr + i) = new char[cols+1]();
        //std::fill(*(out_ptr+i),*(out_ptr + i)+cols,48); For setting default characters on matrix
    }
}

std::ostream& operator<<(std::ostream& os, const Matrix& mx) {
    char** out_ptr = mx.out_ptr;
    char* in_ptr;
    for (unsigned int i = 0; i < mx.rows; ++i) {
        in_ptr = *(out_ptr + i);
        for (unsigned int j = 0; j < mx.cols; ++j) {
            os << *(in_ptr + j);
            //if (j < mx.cols-1) os << " "; //This is for printing matrix with spaces between columns
        }
        if (i < mx.rows-1) os << "\n";
    }
    return os;
}



