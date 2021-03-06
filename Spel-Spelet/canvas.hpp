#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <string>
#include "matrix.hpp"
#include "menus/menu.hpp"
#include "areas/area.hpp"
#include "battle.hpp"
#include "texts/text.hpp"


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
    std::size_t menu_item_description_y_offset = 0;
    std::size_t menu_item_description_row_span = 2;
    std::size_t area_description_x_offset = 3;
    std::size_t area_description_y_offset = 5;
    std::size_t area_controls_delimiter_offset = 7;
    std::size_t area_controls_x_offset = 3;
    std::size_t area_controls_y_offset = 1;
    std::size_t area_name_y_offset = 1;
    std::size_t area_hints_x_offset = 1;
    std::size_t area_hint_fight_y_offset = 1;
    std::size_t area_hint_talk_y_offset = 3;
    std::size_t area_hint_game_menu_y_offset = 5;
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
    std::size_t battle_action_row_span = 2;
    std::size_t entity_name_turn_y_offset = 0;
    std::size_t text_y_offset = 3;
    std::size_t text_subtitle_y_offset = 3;
    std::size_t text_enter_hint_y_offset = 1;
    std::size_t entity_status_name_y_offset = 1;
    std::size_t entity_status_description_y_offset = 2;
    std::size_t entity_status_description_y_span = 2;
    std::size_t entity_status_weapon_y_offset = 5;
    std::size_t entity_status_armor_y_offset = 9;
    
    Matrix matrix;

    std::size_t calculate_x_middle(std::size_t len);
    std::size_t calculate_y_middle(std::size_t len = 0);
    void fill_row(std::size_t rw, const std::string& str, std::size_t offset = 0, bool centered = false, bool prefill = true,
                  char prefill_char = ' ', bool postfill = true, char postfill_char = ' ', std::size_t rw_span = 1);
    void fill_rowspan_withfill_ww(std::size_t rw, const std::string& str,std::size_t rw_span, std::size_t x_offset = 0,bool centered = false);
    void fill_row_word_wrapping(std::size_t rw, const std::string& str, std::size_t offset = 0, bool centered = false, bool prefill = true,
                                char prefill_char = ' ', bool postfill = true, char postfill_char = ' ', std::size_t rw_span = 1);
    bool add_if_fit(const std::string& word, std::string& line, std::size_t line_max_size, const std::string& delim);

    void set_rows(std::size_t begin,std::size_t end, char ch);
    void clear_row(std::size_t row);
    void set_canvas(std::size_t begin,std::size_t end, char ch, std::size_t col_begin, std::size_t col_end);

public:
    Canvas();
    Canvas(std::size_t n, std::size_t m);
    Canvas(const Canvas& ref);
    Canvas& operator =(Canvas& ref);
    ~Canvas();

    //void apply_text(const Text& text);
    void apply_text (const Text& text);
    void apply_entity_status (const Entity& ent);
    void apply_menu(const Menu& ref);
    void apply_partial_menu(const Menu& ref, std::size_t x_pos, std::size_t y_pos, std::size_t x_span=0, std::size_t y_span=0);
    void apply_area(const Area& ref);
    void apply_battle_intro(const Battle& battle);
    void apply_battle_fight(const Battle& battle);
    void apply_battle_action(const Battle& battle);

    void clear_canvas();


    //void fill_row(std::size_t rw, char* ref);
    std::size_t get_rows()const;
    std::size_t get_cols()const;

    char* operator[](std::size_t pos)const;

};

#endif
