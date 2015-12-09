#include "human.hpp"
#include "../conf.hpp"
#include "../debug/debugmacro.h"
Human PLAYER(RES_PATH+"units/player");

Human::Human() {
}

Human::Human(const std::string& filename) : Organic(filename) {
    debug_println(BIT1,"Human created from file '" << filename << "' name: " << name << " description: " << description << " trash_talk: " << trash_talk << "' ap: " << ap << " dp: " << dp << " hp: " << hp << " mp: " << mp);
    fs.close();
}

Weapon Human::get_unarmored_weapon() const {
        Weapon unarmored_weapon = Weapon(RES_PATH + "weapons/fists");
        return unarmored_weapon;
}

Human::~Human() {
     delete unarmored_weapon_ptr;
}
