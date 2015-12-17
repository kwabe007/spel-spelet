#include "human.hpp"
#include "../conf.hpp"
#include "../debug/debugmacro.h"


Human::Human() {
}

Human::Human(std::stringstream& ss) : Organic::Organic(ss) {
    debug_println(BIT3,"Human created from file, name: " << name << " description: " << description << " trash_talk: " << trash_talk << "' ap: " << ap << " dp: " << dp << " hp: " << hp << " mp: " << mp);
}

Human::Human(const std::string& resource) : Organic(resource) {
    debug_println(BIT3,"Human created from resource '" << resource << "' name: " << name << " description: " << description << " trash_talk: " << trash_talk << "' ap: " << ap << " dp: " << dp << " hp: " << hp << " mp: " << mp);
}

Human& Human::operator=(Human& ref) {
    hp = ref.hp;
    ap = ref.ap;
    dp = ref.dp;
    mp = ref.mp;
    name = ref.name;
    inventory = ref.inventory;
    description = ref.description;
    trash_talk = ref.trash_talk;
    what_to_say = ref.what_to_say;
    weapon_ptr = ref.weapon_ptr;
    unarmed_weapon_ptr = ref.unarmed_weapon_ptr;
    alive = ref.alive;
    return *this;
}

Weapon Human::get_unarmed_weapon() const {
        Weapon unarmed_weapon = Weapon(CONF.get_path_resource("itm-fists"));
        return unarmed_weapon;
}

Human::~Human() {
}
