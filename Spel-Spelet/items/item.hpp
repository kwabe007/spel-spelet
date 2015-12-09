#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

class Item {
private:
    std::string name;
    std::string description;

public:
    Item();
    Item(std::string filename);
    std::string get_name() const;
};


#endif
