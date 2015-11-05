#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <string>
#include<iostream>


class Matrix {
private:
    std::size_t rows;
    std::size_t cols;
    std::string* in_ptr;
    std::string** out_ptr;
public:
    Matrix();
    Matrix(std::size_t n, std::size_t m);
    Matrix(const Matrix& ref);
    Matrix& operator =(Matrix& ref);
    ~Matrix();

    std::string* operator[](size_t i) const;

    void fill_col(std::size_t col, std::string* ref);
    void fill_row(std::size_t rw, std::string* ref);
    std::size_t get_rows()const;
    std::size_t get_cols()const;

    friend std::ostream& operator<<(std::ostream& os, const Matrix& dt);

};



#endif
