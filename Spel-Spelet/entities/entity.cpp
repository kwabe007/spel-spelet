#include <random>
#include "entity.hpp"
#include "../conf.hpp"
#include <iostream>
#include "../exceptions/fileexcept.hpp"
#include "../debug/debugmacro.h"
#include "../parse.hpp"


Entity::Entity() {
}

Entity::Entity(const std::string& resource) {
    std::string contents = tools::read_resource(resource);
    std::stringstream ss(contents);
    std::string discard;
    std::getline(ss,discard);
    read_from_string_stream(ss);
}

Entity::Entity(std::stringstream& ss) {
    read_from_string_stream(ss);
}

void Entity::read_from_string_stream(std::stringstream& ss) {
    debug_println(BIT3, "Constructing entity from string stream... ");
    if (!ss.good()) {
        throw FileException("String stream is empty");
    }
    debug_println(BIT3, "string stream good");

    std::getline(ss, name);
    debug_print(BIT3, " got name: " << name);
    std::getline(ss, description);
    debug_print(BIT3, " got description: " << name);
    std::getline(ss, trash_talk);
    debug_print(BIT3, " got trash talk: " << trash_talk);
    std::getline(ss, what_to_say);
    debug_print(BIT3, " got what_to_say: " << what_to_say);


    std::string temp;
    std::getline(ss, temp);
    hp = std::stoi(temp);
    debug_print(BIT3, " got hp: " << hp);
    hp_max = hp;
    std::getline(ss, temp);
    ap = std::stoi(temp);
    debug_print(BIT3, " got ap: " << ap);
    std::getline(ss, temp);
    dp = std::stoi(temp);
    debug_print(BIT3, " got dp: " << dp);
    std::getline(ss, temp);
    mp = std::stoi(temp);
    debug_print(BIT3, " got mp: " << mp);

    char c1 = ss.peek();
    debug_println(BIT3, "char is " << c1);
    debug_println(BIT3, "conf char is " << CONF.FLAG_RES_ATTR_EMPTY);
    if (c1 != CONF.FLAG_RES_ATTR_EMPTY) {
        std::getline(ss, temp);
        Item* itm_ptr = static_cast<Item*> (tools::parse_item_from_file(temp));
        weapon_ptr = dynamic_cast<Weapon*> (itm_ptr);
    } else {
        std::getline(ss, temp);
    }
    std::string items_str;
    std::getline(ss, items_str);
    std::stringstream ss_items(items_str);
    debug_println(BIT3, "Read stringstream(item) for entity " << name << ": '" << items_str << "'");

    debug_print(BIT3, "Items added to inventory of " << name << ":");
    while (ss_items.good()) {
        char c1 = ss_items.peek();
        if (c1 == CONF.FLAG_RES_ATTR_EMPTY)
            break;
        std::string item_str;
        ss_items >> item_str;
        Item* item_ptr =  static_cast<Item*> (tools::parse_item_from_file(item_str));
        item_ptr->set_owner(this);
        add_item_to_inventory(*item_ptr);
        debug_print(BIT3, " " << item_ptr->get_name());
    }
    debug_println(BIT3, "");
    debug_println(BIT3, "Entity construction complete" << ss);
}

Entity::~Entity() {
    if (weapon_ptr) delete weapon_ptr;
    for (Item* item_ptr : inventory) {
        delete item_ptr;
    }
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

std::string Entity::get_what_to_say() const {
    return what_to_say;
}

Item& Entity::get_item_from_inventory(std::size_t index) {
    return *(inventory[index]);
}

const Item& Entity::get_item_from_inventory(std::size_t index) const {
    return *(inventory[index]);
}

std::size_t Entity::get_inventory_size() const {
    return inventory.size();
}

Weapon Entity::get_weapon() const {
    if (weapon_ptr) return *weapon_ptr;
    return get_unarmored_weapon();
}

bool Entity::is_alive() const {
    if (hp > 0)
        return true;
    return false;
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

void Entity::add_item_to_inventory(Item& item) {
    inventory.push_back(&item);
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

std::pair<bool, int> Entity::take_health(int healing) {
    if (hp == hp_max)
        return std::pair<bool, int>(false, healing);
    if (hp_max - hp > healing) {
        hp += healing;
        return std::pair<bool, int>(true, healing);
    }
    healing = hp_max - hp;
    hp = hp_max;
    return std::pair<bool, int>(true, healing);
}

std::pair<bool, int> Entity::attack (Entity& other) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(CONF.get_damage_var_low(),CONF.get_damage_var_high());
    int var = dis(gen);
    int damage = 0;
    int weapon_damage = 0;
    if (weapon_ptr)
        weapon_damage = weapon_ptr->get_ap();
    if (ap + weapon_damage + var >= 0)
        damage = ap + weapon_damage + var;

    std::pair<bool, int> stats = other.take_damage(damage);
    debug_println(BIT0,"Stats entity attack: " << stats.first << " " << stats.second);
    return stats;
}


