#ifndef CONSUMABLE_HPP
#define CONSUMABLE_HPP

#include "item.hpp"


class Consumable : public Item {
private:
    using Item::Item;
    unsigned int hp_healed = 0;
    unsigned int amount = 5;
public:
    Consumable(std::stringstream& ss);
    int action();
    std::string get_description() const;
};

#endif
