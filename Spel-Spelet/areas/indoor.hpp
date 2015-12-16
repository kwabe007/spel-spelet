#ifndef INDOOR_HPP
#define INDOOR_HPP
#include "area.hpp"

class Indoor : public Area  {
    using Area::Area;
public:
    virtual std::string get_type()=0;
};

#endif
