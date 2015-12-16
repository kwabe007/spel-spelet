#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>
#include <vector>
#include <fstream>
#include <utility>
#include <sstream>
#include "../items/item.hpp"
#include "../items/weapon.hpp"


class Entity {
protected:

    int hp = 20; //Health Points
    int hp_max = hp; //Max Health Points
    int ap = 5; //Attack Points
    int dp = 10; //Defense Points
    int mp = 10; //Magic Points
    std::string name = "Riksluffare";
    std::string description = "Whack";
    std::string trash_talk = "????";
    std::string what_to_say = "I have nothing to say";
    Weapon* weapon_ptr = nullptr;
    Weapon* unarmored_weapon_ptr = nullptr;

    bool alive = true;
    std::vector<Item*> inventory;
    virtual Weapon get_unarmored_weapon() const=0;
    std::fstream fs;
    void read_from_string_stream(std::stringstream& ss);

public:
    Entity();
    Entity(const std::string& resource);
    Entity(std::stringstream& ss);
    Entity(const std::string& nm, const std::string& desc, const std::string& trash);
    virtual ~Entity();



    int get_hp() const;
    int get_mp() const;
    int get_ap() const;
    int get_dp() const;

    std::string get_name() const;
    std::string get_description() const;
    std::string get_trash_talk() const;
    std::string get_what_to_say() const;
    Item& get_item_from_inventory(std::size_t index);
    const Item& get_item_from_inventory(std::size_t index)const;
    std::size_t get_inventory_size() const;
    Weapon get_weapon() const;

    bool is_alive()const;
    void set_hp(int val);
    void set_mp(int val);
    void set_ap(int val);
    void set_dp(int val);
    void add_item_to_inventory(Item& item);
    std::pair<bool, int> take_damage(int damage);
    std::pair<bool, int> take_health(int health);
    std::pair<bool, int> attack(Entity& other);

};

#endif
