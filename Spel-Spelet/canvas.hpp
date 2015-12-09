#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <string>
#include "matrix.hpp"
#include "menus/menu.hpp"
#include "areas/area.hpp"
#include "battle.hpp"


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
    std::size_t partial_option_x_offset = 3;
    std::size_t partial_option_y_offset = 3;
    std::size_t menu_title_x_offset = 3;
    std::size_t menu_title_y_offset = 2;
    std::size_t area_description_x_offset = 3;
    std::size_t area_description_y_offset = 5;
    std::size_t area_controls_delimiter_offset = 7;
    std::size_t area_controls_x_offset = 3;
    std::size_t area_controls_y_offset = 1;
    std::size_t area_name_y_offset = 1;
    std::size_t fight_hint_x_offset = 1;
    std::size_t fight_hint_y_offset = 1;
    std::size_t player_trash_talk_x_offset = 3;
    std::size_t player_trash_talk_y_offset = 3;
    std::size_t enemy_trash_talk_x_offset = 3;
    std::size_t enemy_trash_talk_y_offset = 3;
    std::size_t battle_delimiter_y_offset = 2;
    std::size_t battle_menu_x_offset = 0;
    std::size_t battle_menu_y_offset = 1;
    std::size_t battle_menu_title_x_offset = 1;
    std::size_t battle_menu_title_y_offset = 0;
    std::size_t party_name_x_offset = 2;
    std::size_t party_name_y_offset = 2;

    
    Matrix matrix;

    std::size_t calculate_x_middle(std::size_t len);
    std::size_t calculate_y_middle(std::size_t len = 0);

public:
    Canvas();
    Canvas(std::size_t n, std::size_t m);
    Canvas(const Canvas& ref);
    Canvas& operator =(Canvas& ref);
    ~Canvas();

    //void apply_text(const Text& text);
    void apply_menu(const Menu& ref);
    void apply_partial_menu(const Menu& ref, std::size_t x_pos, std::size_t y_pos, std::size_t x_span=0, std::size_t y_span=0);
    void apply_area(const Area& ref);
    void apply_battle_intro(const Battle& battle);
    void apply_battle_fight(const Battle& battle);
    void apply_battle_action(const Battle& battle);
    void clear_row(std::size_t row);
    void clear_canvas();

    //void fill_row(std::size_t rw, char* ref);
    std::size_t get_rows()const;
    std::size_t get_cols()const;

    char* operator[](std::size_t pos)const;

};

#endif
