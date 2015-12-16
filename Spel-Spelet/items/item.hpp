#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include <sstream>

class Entity;

class Item {
protected:
    std::string name;
    std::string description;
    Entity* owner = nullptr;

public:
    Item();
    Item(std::string filename);
    Item(std::stringstream& ss, Entity* owner = nullptr);
    virtual ~Item();
    std::string get_name() const;
    virtual std::string get_description() const=0;

    void set_owner(Entity* ent_ptr);
    virtual int action()=0;
};


#endif
