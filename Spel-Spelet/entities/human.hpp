#ifndef HUMAN_HPP
#define HUMAN_HPP

#include "organic.hpp"

class Human : public Organic {
protected:
    using Organic::Organic;
    Weapon get_unarmed_weapon() const;
public:
    Human();
    Human(std::stringstream& ss);
    Human(const std::string& resource);
    Human& operator=(const Human& ref);
    ~Human();
};

extern Human PLAYER;

#endif
