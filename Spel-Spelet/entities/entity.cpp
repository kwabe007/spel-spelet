#include "entity.hpp"

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

int Entity::attack (Entity& other) {
    other.get_hp();
    return 0;
}


