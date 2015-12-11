#ifndef BUILDING_HPP
#define BUILDING_HPP
#include "indoor.hpp"

class Building : public Indoor  {
public:
    using Indoor::Indoor;
    Building(const std::string& filename);


};

#endif
