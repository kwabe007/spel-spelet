#ifndef HUMAN_HPP
#define HUMAN_HPP

#include "organic.hpp"

class Human : public Organic {
protected:
    Weapon* get_unarmored_weapon();
public:
    Human();
    Human(const std::string& filename);
    ~Human();


};

extern Human PLAYER;

#endif
