#include <random>
#include "entity.hpp"
#include "../conf.hpp"
#include <iostream>
#include "../exceptions/fileexcept.hpp"
#include "../debug/debugmacro.h"


Entity::Entity() {
}

Entity::Entity(const std::string& filename) : fs{filename} {
    if (!fs.good()) {
        throw FileException("File '" + filename + "' not found or is empty");
    }
    std::string temp;
    std::getline(fs, name);
    std::getline(fs, description);
    std::getline(fs, trash_talk);
    std::getline(fs, what_to_say);

    std::getline(fs, temp);
    hp = std::stoi(temp);
    std::getline(fs, temp);
    ap = std::stoi(temp);
    std::getline(fs, temp);
    dp = std::stoi(temp);
    std::getline(fs, temp);
    mp = std::stoi(temp);

}

Entity::Entity(const std::string& nm, const std::string& desc, const std::string& trash) : name{nm}, description{desc}, trash_talk{trash} {
}

Entity::~Entity() { };

int Entity::get_hp() const {
    return hp;
}

int Entity::get_mp() const {
    return mp;
}

int Entity::get_ap() const {
    return ap;
}

int Entity::get_dp() const {
    return dp;
}

std::string Entity::get_name() const {
    return name;
}

std::string Entity::get_description() const {
    return description;
}

std::string Entity::get_trash_talk() const {
    return trash_talk;
}

std::string Entity::get_what_to_say() const {
    return what_to_say;
}

Weapon Entity::get_weapon() const {
    if (weapon_ptr) return *weapon_ptr;
    return get_unarmored_weapon();
}

bool Entity::is_alive() const {
    return alive;
}

void Entity::set_hp(int val){
    hp = val;
}

void Entity::set_mp(int val){
    mp = val;
}

void Entity::set_ap(int val){
    ap = val;
}

void Entity::set_dp(int val){
    dp = val;
}

std::pair<bool, int> Entity::take_damage(int damage) {
    if (hp > damage) {
        hp -= damage;
        return std::pair<bool, int>(false, damage);
    }
    hp = 0;
    alive = false;
    return std::pair<bool, int>(true, damage);
}

std::pair<bool, int> Entity::attack (Entity& other) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(DAMAGE_VAR_LOW,DAMAGE_VAR_HIGH);
    int var = dis(gen);
    int damage = 0;
    if (ap + var >= 0)
        damage = ap + var;

    std::pair<bool, int> stats = other.take_damage(damage);
    debug_println(BIT0,"Stats entity attack: " << stats.first << " " << stats.second);
    return stats;
}


