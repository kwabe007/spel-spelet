#ifndef AREA_HPP
#define AREA_HPP
#include <string>
#include <vector>

enum {
    DIRECTION_NORTH,
    DIRECTION_NORTHEAST,
    DIRECTION_EAST,
    DIRECTION_SOUTHEAST,
    DIRECTION_SOUTH,
    DIRECTION_SOUTHWEST,
    DIRECTION_WEST,
    DIRECTION_NORTHWEST,
    DIRECTION_COUNT
};

class Area {
private:
    std::vector<Area*> next_area_vec;
    std::vector<Area*> extra_area_vec;
    std::string description;
    //std::vector<Entity> extra_area_vec;

public:
    Area();
    Area(const Area& ref);
    Area& operator=(const Area& ref);
    std::string get_description() const;
    void set_description(const std::string& str);


};


#endif
