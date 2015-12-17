#ifndef ARMOR_HPP
#define ARMOR_HPP

#include "item.hpp"

class Armor : public Item {
private:
    using Item::Item;
    unsigned int dp = 0;
public:
    Armor(std::string filename);
    Armor(std::stringstream& ss);
    int get_dp() const;
    std::string get_description() const;
    int action();
};

#endif
