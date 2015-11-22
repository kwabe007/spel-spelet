#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>

class Entity {
private:
    int hp = 20; //Health Points
    int ap = 5; //Attack Points
    int dp = 10; //Defense Points
    int mp = 10; //Magic Points
    std::string name = "Riksluffare";
    std::string description = "Whack";
    std::string trash_talk = "????";

    //std::vector<Objects> inventory;
public:
    Entity();
    Entity(const std::string& nm, const std::string& desc, const std::string& trash);

    int get_hp() const;
    int get_mp() const;
    int get_ap() const;
    int get_dp() const;
    std::string get_name() const;
    std::string get_description() const;
    std::string get_trash_talk() const;
    void set_hp(int val);
    void set_mp(int val);
    void set_ap(int val);
    void set_dp(int val);
    bool take_damage(int damage);
    bool attack(Entity& other);

};

#endif
