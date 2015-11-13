#ifndef BUILDING_HPP
#define BUILDING_HPP
#include "indoor.hpp"

class Building : public Indoor  {
public:

    //Building(const std::string name, const std::string desc){}
    using Indoor::Indoor;

};

#endif
