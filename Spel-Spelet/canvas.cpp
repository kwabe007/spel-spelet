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
    size_t middle = (cols/2)-(len/2)-1;
    return middle;
}

std::size_t Canvas::calculate_y_middle(std::size_t len) {
    size_t middle = (rows/2)-(len/2)-1;
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

void Canvas::apply_partial_menu(const Menu& menu, std::size_t x_pos, std::size_t y_pos, std::size_t x_span, std::size_t y_span) {
    std::string item_name;
    std::size_t top_row = y_pos;
    std::size_t row;
    for (std::size_t i = 0; i < menu.get_size(); ++i) {
        item_name = menu[i];
        row = top_row+partial_option_y_offset+(option_pad+1)*i;
        matrix.fill_row(row,item_name.c_str(),item_name.size(),partial_option_x_offset+x_pos);
        if (menu.is_selected(i)) matrix.fill_row(row,selector.c_str(),selector.size(),partial_option_x_offset+x_pos-selector_offset);
    }
    matrix.fill_row(top_row+battle_menu_title_y_offset,menu.get_name().c_str(),menu.get_name().size(),battle_menu_title_x_offset+x_pos);
}

void Canvas::apply_area(const Area& ref) {
    matrix.fill_row(area_name_y_offset,ref.get_name().c_str(),ref.get_name().size(),calculate_x_middle(ref.get_name().size()));
    matrix.fill_row(area_description_y_offset,ref.get_description().c_str(),ref.get_description().size(),area_description_x_offset);
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
    matrix.fill_row(rows-1-fight_hint_y_offset,UI::FIGHT_HINT.c_str(),UI::FIGHT_HINT.size(),cols-1-fight_hint_x_offset-UI::FIGHT_HINT.size());

    //Filling in area controls with given positions
    matrix.fill_row(north_y, UI::CONTROL_NORTH.c_str(), UI::CONTROL_NORTH.size(),north_x);
    matrix.fill_row(east_y, UI::CONTROL_EAST.c_str(), UI::CONTROL_EAST.size(), east_x);
    matrix.fill_row(south_y, UI::CONTROL_SOUTH.c_str(), UI::CONTROL_SOUTH.size(), south_x);
    matrix.fill_row(west_y, UI::CONTROL_WEST.c_str(), UI::CONTROL_WEST.size(), west_x);

    //Fill in selector depending on which direction is selected
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
    default:
        break;
    }
}

void Canvas::apply_battle_intro(const Battle& battle) {
    const Entity& ally = battle.get_party_entity(0);
    const Entity& enemy = battle.get_enemy_entity(0);
    matrix.fill_row(player_trash_talk_y_offset,ally.get_name().c_str(),ally.get_name().size(),player_trash_talk_x_offset);
    matrix.fill_row(player_trash_talk_y_offset+1,("\""+ally.get_trash_talk()+"\"").c_str(),ally.get_trash_talk().size()+2,player_trash_talk_x_offset);
    matrix.fill_row(calculate_y_middle(),"VS",2,calculate_x_middle(2));
    matrix.fill_row(rows-2,"Press ENTER to continue",23,calculate_x_middle(23));
    matrix.fill_row(rows-2-enemy_trash_talk_y_offset,enemy.get_name().c_str(),enemy.get_name().size(),cols-1-enemy_trash_talk_x_offset-enemy.get_name().size());
    matrix.fill_row(rows-1-enemy_trash_talk_y_offset,("\""+enemy.get_trash_talk()+"\"").c_str(),enemy.get_trash_talk().size()+2,cols-1-enemy_trash_talk_x_offset-enemy.get_trash_talk().size()-2);
}

void Canvas::apply_battle_fight(const Battle& battle) {
    std::size_t delim_row = calculate_y_middle()+battle_delimiter_y_offset;
    matrix.fill_row(delim_row,UI::BATTLE_DELIMITER,cols);
    const Entity& enemy = battle.get_enemy_entity(0);
    const Entity& player = battle.get_party_entity(0);

    std::string enemy_str = (enemy.get_name() + "HP["+std::to_string(enemy.get_hp())+"]");
    matrix.fill_row(party_name_y_offset,' ');
    matrix.fill_row(party_name_y_offset,enemy_str.c_str(),enemy_str.size(),cols-enemy.get_name().size()-party_name_x_offset-7); // Minus 7 for hp bracket
    std::string player_str = (player.get_name() + "HP["+std::to_string(player.get_hp())+"]");
    matrix.fill_row(party_name_y_offset,player_str.c_str(),player_str.size(),party_name_x_offset);

    apply_partial_menu(battle.get_current_menu(),battle_menu_x_offset,battle_menu_y_offset+delim_row);
}

void Canvas::apply_battle_action(const Battle& battle) {
    std::size_t action_row = calculate_y_middle()+battle_delimiter_y_offset-1;
    std::string action = battle.get_last_action();
    debug_println(BIT0, "Action size: " << action.size());

    std::size_t x_col = calculate_x_middle(action.size());

    debug_println(BIT0, "Filling row  with '" << action << "' at row " <<  action_row  << " starting at col " << x_col);
    matrix.fill_row(action_row,action.c_str(),action.size(),x_col);
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
