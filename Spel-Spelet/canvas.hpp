#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <string>
#include <iostream>
#include "matrix.hpp"
#include "menu.hpp"


class Canvas {
private:
    std::size_t rows;
    std::size_t cols;
    int cursor_col = 0;
    int cursor_row = 0;
    int selector_offset = 2;
    std::string selector = ">";
    int option_pad = 1;
    std::size_t option_x_offset = 3;
    std::size_t option_y_offset = 3;
    std::size_t menu_title_x_offset = 3;
    std::size_t menu_title_y_offset = 2;
    
    Matrix matrix;

public:
    Canvas();
    Canvas(std::size_t n, std::size_t m);
    Canvas(const Canvas& ref);
    Canvas& operator =(Canvas& ref);
    ~Canvas();

    void apply_menu(const Menu& ref);
    void clear_canvas();

    //void fill_row(std::size_t rw, char* ref);
    std::size_t get_rows()const;
    std::size_t get_cols()const;

    char* operator[](std::size_t pos)const;

};

#endif
