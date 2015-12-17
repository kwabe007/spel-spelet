#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include "organic.hpp"

class Animal : public Organic {
protected:
    using Organic::Organic;
    Weapon get_unarmed_weapon() const;
public:
    Animal();
    Animal(std::stringstream& ss);
    Animal(const std::string& resource);
    ~Animal();
};

#endif
