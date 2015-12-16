#ifndef OUTDOOR_HPP
#define OUTDOOR_HPP

#include "area.hpp"

class Outdoor : public Area {
    using Area::Area;
public:
    virtual std::string get_type()=0;
};

#endif
