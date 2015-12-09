#include "battle.hpp"
#include "parse.hpp"
#include "debug/debugmacro.h"
#include "items/weapon.hpp"

Battle::Battle(Entity& enemy) : main_party{1,&PLAYER}, enemy_party{1,&enemy},select_enemy_menu{"Who do you want attack?"} {
    select_enemy_menu.add_item(enemy.get_name(),"Keff",&target_enemy_index,0);
}

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

void Battle::set_latest_action(const Entity& subject,ActionType type, const Entity& object, std::pair<bool, int> stats) {
    std::string subjectname(subject.get_name());
    std::string objectname(object.get_name());
    std::string damage_dealt = std::to_string(stats.second);
    switch (type) {
    case ACTION_TYPE_ATTACK:
        latest_action = subjectname + " " + tools::read_line("general_interface/attack_action1") + " " + objectname + " " +
                tools::read_line("general_interface/attack_action2") + " " + subject.get_weapon().get_name() + " " + tools::read_line("general_interface/dealing_damage") +
                damage_dealt;
    }
}

std::pair<bool, int> Battle::attack(Entity& attacker, Entity& target) {
    return attacker.attack(target);
}

int Battle::party_action() {
    std::pair<bool, int> stats = attack(get_current_party(),get_target_enemy());
    set_latest_action(get_current_party(),ACTION_TYPE_ATTACK,get_target_enemy(),stats);
    switch_turn();
    if (enemies_alive() == 0) return true;
    return false;
}

int Battle::enemy_action() {
    set_latest_action(get_current_enemy(),ACTION_TYPE_ATTACK,get_target_party(),
                      attack(get_current_enemy(),get_target_party()));
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

std::string Battle::get_last_action() const {
    return latest_action;
}
