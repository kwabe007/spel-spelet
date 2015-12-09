#ifndef WEAPON_HPP
#define WEAPON_HPP

#include "item.hpp"

class Weapon : public Item {
private:
    using Item::Item;
    unsigned int ap = 0;
public:
};

#endif
