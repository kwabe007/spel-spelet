#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>
#include <vector>
#include <fstream>
#include "../items/item.hpp"
#include "../items/weapon.hpp"

class Entity {
protected:
    int hp = 20; //Health Points
    int ap = 5; //Attack Points
    int dp = 10; //Defense Points
    int mp = 10; //Magic Points
    std::string name = "Riksluffare";
    std::string description = "Whack";
    std::string trash_talk = "????";
    Weapon* weapon_ptr = nullptr;
    Weapon* unarmored_weapon_ptr = nullptr;

    bool alive = true;
    std::vector<Item*> inventory;
    virtual Weapon* get_unarmored_weapon()=0;
    std::fstream fs;

public:
    Entity();
    Entity(const std::string& nm);
    Entity(const std::string& nm, const std::string& desc, const std::string& trash);
    virtual ~Entity()=0;

    int get_hp() const;
    int get_mp() const;
    int get_ap() const;
    int get_dp() const;
    std::string get_name() const;
    std::string get_description() const;
    std::string get_trash_talk() const;

    bool is_alive()const;
    void set_hp(int val);
    void set_mp(int val);
    void set_ap(int val);
    void set_dp(int val);
    bool take_damage(int damage);
    bool attack(Entity& other);

};

#endif
