#include "battle.hpp"

Battle::Battle(Entity& enemy) : main_party{1,&PLAYER}, enemy_party{1,&enemy},select_enemy_menu{"Who do you want attack?",1} {
    select_enemy_menu.add_item(enemy.get_name(),"Keff",&selected_enemy_index,0);
    current_enemy = enemy_party[0];
    enemies_alive = enemy_party.size();
    party_members_alive = main_party.size();
}

bool Battle::attack(Entity& target) {
    return current_entity->attack(target);
}

bool Battle::attack(Entity& attacker, Entity& target) {
    return attacker.attack(target);
}

int Battle::action() {
    int vic_flag = 0;
    switch (turn) {
    case PARTY_TURN:
        if(party_action()) vic_flag = 1;
        turn = ENEMY_TURN;
        break;
    case ENEMY_TURN:
        if(enemy_action()) vic_flag = -1;
        turn = PARTY_TURN;
        break;
    }
    return vic_flag;
}

bool Battle::party_action() {
    if (attack(get_enemy_entity(selected_enemy_index)))
        --enemies_alive;
    if (enemies_alive == 0) return true;
    return false;
}

bool Battle::enemy_action() {
    if (attack(get_party_entity(selected_party_index)))
        --party_members_alive;
    if (party_members_alive == 0) return true;
    return false;
}

void Battle::back_to_main_menu() {
    current_menu = &select_enemy_menu;
}

Entity& Battle::get_party_entity(std::size_t index) {
    return *main_party[index];
}

const Entity& Battle::get_party_entity(std::size_t index) const {
    return *main_party[index];
}

Entity& Battle::get_enemy_entity(std::size_t index) {
    return *enemy_party[index];
}

const Entity& Battle::get_enemy_entity(std::size_t index) const {
    return *enemy_party[index];
}

Menu& Battle::get_current_menu() {
    return *current_menu;
}

const Menu& Battle::get_current_menu() const {
    return *current_menu;
}
