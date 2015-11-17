#ifndef HUMAN_HPP
#define HUMAN_HPP

#include "organic.hpp"

class Human : public Organic {
    using Organic::Organic;
};

extern Human PLAYER;

#endif
