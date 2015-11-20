#include "battle.hpp"
#include "entities/human.hpp"

Battle::Battle(Entity& enemy) : main_party{1,&enemy}, enemy_party{1,&PLAYER} {

}

bool Battle::attack(Entity& target) {
    current_entity.attack(target);
    return true;
}

bool Battle::attack(Entity& attacker, Entity& target) {
    attacker.attack(target);
    return true;
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
