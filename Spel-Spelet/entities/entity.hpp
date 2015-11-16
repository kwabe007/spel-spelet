#ifndef ENTITY_HPP
#define ENTITY_HPP

class Entity {
private:
    int hp = 10; //Health Points
    int ap = 10; //Attack Points
    int dp = 10; //Defense Points
    int mp = 10; //Magic Points
    //std::vector<Objects> inventory;
public:
    int get_hp()const;
    int get_mp()const;
    int get_ap()const;
    int get_dp()const;
    void set_hp(int val);
    void set_mp(int val);
    void set_ap(int val);
    void set_dp(int val);
    bool take_damage(int damage);
    int attack(Entity& other);

};

#endif
