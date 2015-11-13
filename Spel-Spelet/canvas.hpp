#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <string>
#include <iostream>
#include "matrix.hpp"
#include "menu.hpp"
#include "areas/area.hpp"


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
    std::size_t area_description_x_offset = 3;
    std::size_t area_description_y_offset = 5;
    std::size_t area_controls_delimiter_offset = 7;
    std::size_t area_controls_x_offset = 3;
    std::size_t area_controls_y_offset = 1;
    std::size_t area_name_y_offset = 1;
    
    Matrix matrix;

    std::size_t calculate_x_middle(std::size_t len);

public:
    Canvas();
    Canvas(std::size_t n, std::size_t m);
    Canvas(const Canvas& ref);
    Canvas& operator =(Canvas& ref);
    ~Canvas();

    void apply_menu(const Menu& ref);
    void apply_area(const Area& ref);
    void clear_canvas();

    //void fill_row(std::size_t rw, char* ref);
    std::size_t get_rows()const;
    std::size_t get_cols()const;

    char* operator[](std::size_t pos)const;

};

#endif
