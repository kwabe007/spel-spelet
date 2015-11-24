#include "world.hpp"
World::World() {

}

World::World(const std::string name) : name{name} {

}

World::~World() {

}

void World::add_area(Area& ar) {
    std::size_t index = areas.size();
    areas.push_back(&ar);
    if (auto_setup) {
        std::pair<int,int> coord(0,0);
        if (unordered_map.size > 0) {
            std::pair<int,int> coord_of_last;
            switch(link_direction) {
            case DIRECTION_NORTH:
                coord_of_last = index_map[last_index_mapped];
                coord.first = coord_of_last.first;
                coord.second = coord_of_last.second + 1;
                break;
            case DIRECTION_EAST:
                break;
            case DIRECTION_SOUTH:
                break;
            case DIRECTION_WEST:
                break;
            }
        }
        map_area(index, coord);
    }
}

void World::map_area(std::size_t index, std::pair<int,int> coord) {
    index_map[index] = coord;
}


