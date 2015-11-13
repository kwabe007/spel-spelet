#include <string>
#include <iostream>
#include "canvas.hpp"
#include "ui.hpp"


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

std::size_t Canvas::calculate_x_middle(std::size_t len) {
    size_t middle = (cols/2)-(len/2)-1;
    return middle;
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
    matrix.fill_row(menu_title_y_offset,ref.get_name().c_str(),ref.get_name().size(),menu_title_x_offset);
    matrix.fill_row(menu_title_y_offset+1,UI::MENU_DELIMITER);
}

void Canvas::apply_area(const Area& ref) {
    matrix.fill_row(area_name_y_offset,ref.get_name().c_str(),ref.get_name().size(),calculate_x_middle(ref.get_name().size()));
    matrix.fill_row(area_description_y_offset,ref.get_description().c_str(),ref.get_description().size(),area_description_x_offset);
    matrix.fill_row(rows-1-area_controls_delimiter_offset,UI::CONTROL_DELIMITER);

    std::size_t north_y = rows-1-area_controls_y_offset-4;
    std::size_t north_x = area_controls_x_offset+UI::CONTROL_WEST.size();
    std::size_t east_y = rows-1-area_controls_y_offset-2;
    std::size_t east_x = area_controls_x_offset+UI::CONTROL_WEST.size()*2;
    std::size_t south_y = rows-1-area_controls_y_offset;
    std::size_t south_x = area_controls_x_offset+UI::CONTROL_WEST.size();
    std::size_t west_y = rows-1-area_controls_y_offset-2;
    std::size_t west_x = area_controls_x_offset;

    matrix.fill_row(north_y, UI::CONTROL_NORTH.c_str(), UI::CONTROL_NORTH.size(),north_x);
    matrix.fill_row(east_y, UI::CONTROL_EAST.c_str(), UI::CONTROL_EAST.size(), east_x);
    matrix.fill_row(south_y, UI::CONTROL_SOUTH.c_str(), UI::CONTROL_SOUTH.size(), south_x);
    matrix.fill_row(west_y, UI::CONTROL_WEST.c_str(), UI::CONTROL_WEST.size(), west_x);

    switch (ref.selected_direction) {
        case DIRECTION_NORTH:
        matrix.fill_row(north_y,selector.c_str(),selector.size(),north_x-2,false);
        break;
        case DIRECTION_EAST:
        matrix.fill_row(east_y,selector.c_str(),selector.size(),east_x-2,false);
        break;
        case DIRECTION_SOUTH:
        matrix.fill_row(south_y,selector.c_str(),selector.size(),south_x-2,false);
        break;
        case DIRECTION_WEST:
        matrix.fill_row(west_y,selector.c_str(),selector.size(),west_x-2,false);
        break;
    }

}

void Canvas::clear_canvas() {
    for(unsigned int i = 0; i < matrix.get_rows(); ++i) {
        matrix.fill_row(i,'\0');
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
