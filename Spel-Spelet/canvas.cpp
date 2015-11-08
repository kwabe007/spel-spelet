#include <string>
#include <iostream>
#include "canvas.hpp"


Canvas::Canvas(): matrix(0, 0){
    rows = 0;
    cols = 0;
}

Canvas::Canvas(std::size_t n, std::size_t m): matrix(n, m) {
    cols = n;
    rows = m;
}

Canvas::Canvas(const Canvas& ref) {

}

Canvas& Canvas::operator =(Canvas& ref) {
    return *this;
}

Canvas::~Canvas() {

}

void Canvas::apply_menu(const Menu& ref) {
    int size = (int)ref.get_size();
    std::string m_item_name_str;
    std::size_t row;
    for (int i = size - 1; i >= 0; --i) {
        m_item_name_str = ref[i];
        row = matrix.get_rows() - 1 - option_y_offset - (option_pad + 1)*(size-1-i);
        matrix.fill_row(row,m_item_name_str.c_str(),m_item_name_str.size(),option_x_offset);
        if (ref.is_selected(i)) matrix.fill_row(row,selector.c_str(),selector.size(),option_x_offset-selector_offset);
    }
}

std::size_t Canvas::get_rows()const {
    return rows;
}

std::size_t Canvas::get_cols()const {
    return cols;
}

char* Canvas::operator[](std::size_t pos)const {
    return matrix[pos];
}
