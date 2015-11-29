#include "battle.hpp"

Battle::Battle(Entity& enemy) : main_party{1,&PLAYER}, enemy_party{1,&enemy},select_enemy_menu{"Who do you want attack?",1} {
    select_enemy_menu.add_item(enemy.get_name(),"Keff",&target_enemy_index,0);
}

/*bool Battle::attack(Entity& target) {
    return current_party->attack(target);
}*/

Entity& Battle::get_current_party() {
    return *main_party[party_turn_index];
}

const Entity& Battle::get_current_party() const {
    return *main_party[party_turn_index];
}

Entity& Battle::get_current_enemy() {
    return *enemy_party[enemy_turn_index];
}

const Entity& Battle::get_current_enemy() const {
    return *enemy_party[enemy_turn_index];
}

Entity& Battle::get_target_party() {
    return *main_party[target_party_index];
}

const Entity& Battle::get_target_party() const {
    return *main_party[target_party_index];
}

Entity& Battle::get_target_enemy() {
    return *enemy_party[target_enemy_index];
}

const Entity& Battle::get_target_enemy() const {
    return *enemy_party[target_enemy_index];
}

void Battle::switch_turn() {
    if (turn == PARTY_TURN) turn = ENEMY_TURN;
    else turn = PARTY_TURN;
}

bool Battle::attack(Entity& attacker, Entity& target) {
    return attacker.attack(target);
}

/*int Battle::action() {
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
}*/

int Battle::party_action() {
    attack(get_current_party(),get_target_enemy());
    switch_turn();
    if (enemies_alive() == 0) return true;
    return false;
}

int Battle::enemy_action() {
    attack(get_current_enemy(),get_target_party());
    switch_turn();
    if (partymems_alive() == 0) return true;
    return false;
}

std::size_t Battle::partymems_alive() const {
    std::size_t count(0);
    for (const Entity* party_ptr : main_party) {
        if (party_ptr->is_alive()) {
            ++count;
        }
    }
    return count;
}

std::size_t Battle::enemies_alive() const {
    std::size_t count(0);
    for (const Entity* enemy_ptr : enemy_party) {
        if (enemy_ptr->is_alive()) {
            ++count;
        }
    }
    return count;
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
