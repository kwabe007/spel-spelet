#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include <sstream>

class Item {
protected:
    std::string name;
    std::string description;

public:
    Item();
    Item(std::string filename);
    Item(std::stringstream& ss);
    virtual ~Item();
    std::string get_name() const;
};


#endif
