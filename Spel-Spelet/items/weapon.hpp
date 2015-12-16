#ifndef WEAPON_HPP
#define WEAPON_HPP

#include "item.hpp"

class Weapon : public Item {
private:
    using Item::Item;
    unsigned int ap = 0;
public:
    Weapon(std::string filename);
    Weapon(std::stringstream& ss);
    int get_ap() const;
    std::string get_description() const;
    int action();
};

#endif
