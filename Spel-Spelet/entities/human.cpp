#include "human.hpp"
#include "../conf.hpp"
#include "../debug/debugmacro.h"
Human PLAYER(CONF.get_path_resource()+"units/player");

Human::Human() {
}

Human::Human(const std::string& filename) : Organic(filename) {
    debug_println(BIT1,"Human created from file '" << filename << "' name: " << name << " description: " << description << " trash_talk: " << trash_talk << "' ap: " << ap << " dp: " << dp << " hp: " << hp << " mp: " << mp);
    fs.close();
}

Weapon Human::get_unarmored_weapon() const {
        Weapon unarmored_weapon = Weapon(CONF.get_path_resource("fists"));
        return unarmored_weapon;
}

Human::~Human() {
     delete unarmored_weapon_ptr;
}
