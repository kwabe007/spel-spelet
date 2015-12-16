#ifndef FOREST_HPP
#define FOREST_HPP

#include "outdoor.hpp"

class Forest : public Outdoor {
private:
    using Outdoor::Outdoor;
public:
    std::sting get_type();
};

#endif
