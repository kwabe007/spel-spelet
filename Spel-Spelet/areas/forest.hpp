#ifndef FOREST_HPP
#define FOREST_HPP

#include "outdoor.hpp"

class Forest : public Outdoor {

public:
    using Outdoor::Outdoor;
    Forest(const std::string& str);
    std::string get_type() const;
    ~Forest(){}
};

#endif
