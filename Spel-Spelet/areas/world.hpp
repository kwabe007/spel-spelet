#ifndef WORLD_HPP
#define WORLD_HPP

#include <unordered_map>
#include "area.hpp"

class World {
private:
    std::string name;
    std::unordered_map<std::size_t, std::pair<int,int>> index_map;
    std::vector<Area*> areas;

    bool auto_setup = true;
    Direction link_direction = DIRECTION_NORTH;
    std::size_t last_index_mapped;

public:
    World();
    World(const std::string name);
    World(const World& ref) = delete;
    ~World();

    World& operator=(const World& ref) = delete;

    void add_area(Area& ar);
    map_area(std::size_t i, std::pair<int,int> coordinates) {

    }



};

#endif
