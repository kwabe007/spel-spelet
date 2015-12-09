#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <string>
#include<iostream>


class Matrix {
private:
    std::size_t rows;
    std::size_t cols;
    char** out_ptr;

    void allocate();
public:
    Matrix();
    Matrix(std::size_t n, std::size_t m);
    Matrix(const Matrix& ref);
    Matrix& operator =(Matrix& ref);
    ~Matrix();

    char* operator[](size_t pos) const;

    void fill_row(std::size_t rw, const std::string& str, std::size_t offset = 0,
                  bool prefill = true, char prefill_char = ' ', bool postfill = false, char postfill_char = ' ');
    /*void fill_row(std::size_t rw, char ch, std::size_t length);*/
    void fill_row(std::size_t rw, char ch);
    void fill_row(std::size_t rw, char ch, std::size_t length, std::size_t offset = 0,
                  bool prefill = true, char prefill_char = ' ', bool postfill = false, char postfill_char = ' ');
    std::size_t get_rows()const;
    std::size_t get_cols()const;

    friend std::ostream& operator<<(std::ostream& os, const Matrix& dt);

};



#endif
