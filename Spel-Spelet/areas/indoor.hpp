#ifndef INDOOR_HPP
#define INDOOR_HPP
#include "area.hpp"

class Indoor : public Area  {
protected:
    using Area::Area;
public:
    virtual std::string get_type()const =0;
    virtual ~Indoor(){}
};

#endif
