#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>
#include <vector>
#include "../items/item.hpp"

class Entity {
private:
    int hp = 20; //Health Points
    int ap = 5; //Attack Points
    int dp = 10; //Defense Points
    int mp = 10; //Magic Points
    std::string name = "Riksluffare";
    std::string description = "Whack";
    std::string trash_talk = "????";
    bool alive = true;

    std::vector<Item*> inventory;

public:
    Entity();
    Entity(const std::string& nm);
    Entity(const std::string& nm, const std::string& desc, const std::string& trash);
    ~Entity();

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
