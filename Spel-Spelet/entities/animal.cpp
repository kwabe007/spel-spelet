#include "animal.hpp"
#include "../conf.hpp"
#include "../debug/debugmacro.h"


Animal::Animal() {
}

Animal::Animal(std::stringstream& ss) : Organic::Organic(ss) {
    debug_println(BIT3,"Animal created from file, name: " << name << " description: " << description << " trash_talk: " << trash_talk << "' ap: " << ap << " dp: " << dp << " hp: " << hp << " mp: " << mp);
}

Animal::Animal(const std::string& resource) : Organic(resource) {
    debug_println(BIT3,"Animal created from resource '" << resource << "' name: " << name << " description: " << description << " trash_talk: " << trash_talk << "' ap: " << ap << " dp: " << dp << " hp: " << hp << " mp: " << mp);
}

Weapon Animal::get_unarmed_weapon() const {
        Weapon unarmed_weapon = Weapon(CONF.get_path_resource("itm-claws"));
        return unarmed_weapon;
}

Animal::~Animal() {
}
