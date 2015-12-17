#ifndef ORGANIC_HPP
#define ORGANIC_HPP

#include "entity.hpp"

class Organic : public Entity {
protected:
    using Entity::Entity;
    virtual Weapon get_unarmed_weapon() const=0;
public:
    virtual ~Organic();

};

#endif
