#include <random>
#include "entity.hpp"
#include "../conf.hpp"


Entity::Entity() {

}

Entity::Entity(const std::string& nm, const std::string& desc, const std::string& trash) : name{nm}, description{desc}, trash_talk{trash} {
}

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

bool Entity::take_damage(int damage) {
    if (hp > damage) {
        hp -= damage;
        return false;
    }
    else {
        hp = 0;
        return true;
    }
}

bool Entity::attack (Entity& other) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(DAMAGE_VAR_LOW,DAMAGE_VAR_HIGH);
    int var = dis(gen);
    int damage_deal = 0;
    if (ap + var >= 0)
        damage_deal = ap + var;
    bool dead = other.take_damage(damage_deal);
    return dead;
}


