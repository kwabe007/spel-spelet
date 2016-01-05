#ifndef OUTDOOR_HPP
#define OUTDOOR_HPP

#include "area.hpp"

class Outdoor : public Area {
public:
    using Area::Area;
    virtual std::string get_type() const=0;
    virtual ~Outdoor(){}
};

#endif
