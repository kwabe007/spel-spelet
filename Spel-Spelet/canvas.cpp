#include "canvas.hpp"
#include "ui.hpp"
#include "debug/debugmacro.h"

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
    if (len == cols) return 0;
    size_t middle = (cols/2)-(len/2)-1;
    return middle;
}

std::size_t Canvas::calculate_y_middle(std::size_t len) {
    size_t middle = (rows/2)-(len/2)-1;
    return middle;
}

/*void Canvas::apply_text(const Text& text) {
    std::stringstream ss_text(text.get_text(), ios_base::in);
    std::string row_str;
    for (std::size_t i = 0; i<rows; ++i) {
        ss_text.get(row_str,cols);
        if (ss_text.eof())
            break;
        row_str
        std::size_t row = i/rows;
        std::size_t col = i%cols;
        matrix.fill_row(i,row_str.c_str());
    }
}*/

bool Canvas::add_if_fit (const std::string& word, std::string& line, std::size_t line_max_size, const std::string& delim) {
    if(word.size() + delim.size() + line.size() <= line_max_size) {
        line.append(word+delim);
        return true;
    }
    return false;
}

void Canvas::fill_row(std::size_t rw, const std::string& str, std::size_t offset, bool prefill,
                      char prefill_char, bool postfill, char postfill_char, bool centered, std::size_t rw_span) {
    std::size_t pos = 0;
    std::string line;
    for (std::size_t i = 0 ; i < rw_span && pos < str.size(); ++i, pos += line.size()) {
        line = str.substr(pos,cols-offset);
        if (centered){
            offset = calculate_x_middle(line.size()) + offset;
            debug_println(BIT0,"Size of line: " << line.size() << " Calculated middle: " << offset);
        }
        matrix.fill_row(rw+i,line,offset,prefill,prefill_char,postfill,postfill_char);
    }

}

void Canvas::fill_row_word_wrapping(std::size_t rw, const std::string& str, std::size_t offset, bool prefill,
                      char prefill_char, bool postfill, char postfill_char, bool centered, std::size_t rw_span) {
    std::stringstream ss_str(str);
    std::string word;
    std::string delim(" ");
    std::size_t line_max_size = cols-offset;

    if (ss_str.good()) {
        ss_str >> word;
        debug_println(BIT0,"First word from stringstream: '" << word << "'");
        for (std::size_t i = 0 ; i < rw_span; ++i) {
            std::string line;
            while(true) {
                if (ss_str.eof()) {
                    delim.clear(); //If we're at the last word add no delimiter
                    debug_println(BIT0,"End of stringstream reached, delimiter set to blank");
                }
                if (!add_if_fit(word,line,line_max_size,delim)) {
                    if (centered) offset = calculate_x_middle(line.size()) + offset; //Adjust offset for line centration
                    debug_println(BIT0,"Writing line '" << line << "' to canvas matrix");
                    matrix.fill_row(rw+i,line,offset,prefill,prefill_char,postfill,postfill_char);
                    break;
                }
                if (ss_str.good()) {
                    ss_str >> word;
                } else {
                    if (centered) offset = calculate_x_middle(line.size()) + offset; //Adjust offset for line centration
                    matrix.fill_row(rw+i,line,offset,prefill,prefill_char,postfill,postfill_char);
                    debug_println(BIT0,"Writing line '" << line << "' to canvas matrix");
                    goto endwhile;
                }
            }
        }
    } else {
        debug_println(BIT0,"Stringstream being read with word wrapping is not good");
    }
    endwhile:;
}

void Canvas::apply_menu(const Menu& ref) {
    int size = (int)ref.get_size();
    std::string m_item_name_str;
    std::size_t row;
    for (int i = size - 1; i >= 0; --i) {
        m_item_name_str = ref[i];
        row = matrix.get_rows() - 1 - option_y_offset - (option_pad + 1)*(size-1-i);
        matrix.fill_row(row,m_item_name_str,option_x_offset);
        if (ref.is_selected(i)) matrix.fill_row(row,selector,option_x_offset-selector_offset);
    }
    matrix.fill_row(menu_title_y_offset,ref.get_name(),menu_title_x_offset);
    matrix.fill_row(menu_title_y_offset+1,UI::MENU_DELIMITER);
}

void Canvas::apply_partial_menu(const Menu& menu, std::size_t x_pos, std::size_t y_pos, std::size_t x_span, std::size_t y_span) {
    std::string item_name;
    std::size_t top_row = y_pos;
    std::size_t row;
    for (std::size_t i = 0; i < menu.get_size(); ++i) {
        item_name = menu[i];
        row = top_row+partial_option_y_offset+(option_pad+1)*i;
        matrix.fill_row(row,item_name,partial_option_x_offset+x_pos);
        if (menu.is_selected(i)) matrix.fill_row(row,selector,partial_option_x_offset+x_pos-selector_offset);
    }
    matrix.fill_row(top_row+battle_menu_title_y_offset,menu.get_name(),battle_menu_title_x_offset+x_pos);
}

void Canvas::apply_area(const Area& ref) {
    matrix.fill_row(area_name_y_offset,ref.get_name(),calculate_x_middle(ref.get_name().size()));
    matrix.fill_row(area_description_y_offset,ref.get_description(),area_description_x_offset);
    matrix.fill_row(rows-1-area_controls_delimiter_offset,UI::CONTROL_DELIMITER);

    //Getting area controls positions
    std::size_t north_y = rows-1-area_controls_y_offset-4;
    std::size_t north_x = area_controls_x_offset+UI::CONTROL_WEST.size();
    std::size_t east_y = rows-1-area_controls_y_offset-2;
    std::size_t east_x = area_controls_x_offset+UI::CONTROL_WEST.size()*2;
    std::size_t south_y = rows-1-area_controls_y_offset;
    std::size_t south_x = area_controls_x_offset+UI::CONTROL_WEST.size();
    std::size_t west_y = rows-1-area_controls_y_offset-2;
    std::size_t west_x = area_controls_x_offset;

    //Fill in fight hint
    matrix.fill_row(rows-1-fight_hint_y_offset,UI::FIGHT_HINT,cols-1-fight_hint_x_offset-UI::FIGHT_HINT.size());

    //Filling in area controls with given positions
    matrix.fill_row(north_y, UI::CONTROL_NORTH, north_x);
    matrix.fill_row(east_y, UI::CONTROL_EAST, east_x);
    matrix.fill_row(south_y, UI::CONTROL_SOUTH, south_x);
    matrix.fill_row(west_y, UI::CONTROL_WEST, west_x);

    //Fill in selector depending on which direction is selected
    switch (ref.selected_direction) {
        case DIRECTION_NORTH:
        matrix.fill_row(north_y,selector,north_x-2,false);
        break;
        case DIRECTION_EAST:
        matrix.fill_row(east_y,selector,east_x-2,false);
        break;
        case DIRECTION_SOUTH:
        matrix.fill_row(south_y,selector,south_x-2,false);
        break;
        case DIRECTION_WEST:
        matrix.fill_row(west_y,selector,west_x-2,false);
        break;
    default:
        break;
    }
}

void Canvas::apply_battle_intro(const Battle& battle) {
    const Entity& ally = battle.get_party_entity(0);
    const Entity& enemy = battle.get_enemy_entity(0);
    matrix.fill_row(player_trash_talk_y_offset,ally.get_name(),player_trash_talk_x_offset);
    matrix.fill_row(player_trash_talk_y_offset+1,("\""+ally.get_trash_talk()+"\""),player_trash_talk_x_offset);
    matrix.fill_row(calculate_y_middle(),"VS",2,calculate_x_middle(2));
    matrix.fill_row(rows-2,"Press ENTER to continue",23,calculate_x_middle(23));
    matrix.fill_row(rows-2-enemy_trash_talk_y_offset,enemy.get_name(),cols-1-enemy_trash_talk_x_offset-enemy.get_name().size());
    matrix.fill_row(rows-1-enemy_trash_talk_y_offset,("\""+enemy.get_trash_talk()+"\""),cols-1-enemy_trash_talk_x_offset-enemy.get_trash_talk().size()-2);
}

void Canvas::apply_battle_fight(const Battle& battle) {
    std::size_t delim_row = calculate_y_middle()+battle_delimiter_y_offset;
    matrix.fill_row(delim_row,UI::BATTLE_DELIMITER,cols);
    const Entity& enemy = battle.get_enemy_entity(0);
    const Entity& player = battle.get_party_entity(0);

    std::string enemy_str = (enemy.get_name() + "HP["+std::to_string(enemy.get_hp())+"]");
    matrix.fill_row(party_name_y_offset,' ');
    matrix.fill_row(party_name_y_offset,enemy_str,cols-enemy.get_name().size()-party_name_x_offset-7); // Minus 7 for hp bracket
    std::string player_str = (player.get_name() + "HP["+std::to_string(player.get_hp())+"]");
    matrix.fill_row(party_name_y_offset,player_str,party_name_x_offset);

    apply_partial_menu(battle.get_current_menu(),battle_menu_x_offset,battle_menu_y_offset+delim_row);
}

void Canvas::apply_battle_action(const Battle& battle) {
    std::size_t action_row = calculate_y_middle()+battle_delimiter_y_offset-battle_action_row_span;
    std::string action = battle.get_last_action();
    debug_println(BIT0, "Action size: " << action.size());
    //std::size_t x_col = calculate_x_middle(action.size());
    fill_row_word_wrapping(action_row,action,0,true,' ',true,' ',false,battle_action_row_span);
}

void Canvas::clear_row(std::size_t row) {
    matrix.fill_row(row,'\0');
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
