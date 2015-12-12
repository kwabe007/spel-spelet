#ifndef HUMAN_HPP
#define HUMAN_HPP

#include "organic.hpp"

class Human : public Organic {
protected:
    using Organic::Organic;
    Weapon get_unarmored_weapon() const;
public:
    Human();
    Human(std::stringstream& ss);
    Human(const std::string& filename);
    Human& operator=(const Human& );
    ~Human();
};

extern Human PLAYER;

#endif
