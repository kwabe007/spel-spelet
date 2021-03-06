#ifndef BUILDING_HPP
#define BUILDING_HPP
#include "indoor.hpp"

class Building : public Indoor  {
public:
    using Indoor::Indoor;
    std::string get_type() const;
    ~Building();
};

#endif
