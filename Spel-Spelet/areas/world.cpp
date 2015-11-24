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
        if (index_map.size() > 0) {
            coord = transform_coordinates(last_coord_mapped, link_direction);
        }
        map_area(coord, index);
    }
}

void World::map_area(std::pair<int,int> coord, std::size_t index) {
    index_map[coord] = index;
}

void World::set_start_area(int x, int y) {
    starting_area_coord = std::pair<int,int>(x,y);
    start_area_is_set = true;
}

Area& World::current_area() {
    std::size_t index = index_map[current_area_coord];
    return *areas[index];
}

const Area& World::current_area() const{
    std::size_t index = (*(index_map.find(current_area_coord))).second;
    return *areas[index];
}

Area& World::get_area(std::size_t index) {
    return *areas[index];
}

const Area& World::get_area(std::size_t index) const{
    return *areas[index];
}

void World::set_current_area(int x,int y) {
    std::pair<int,int> new_val(x,y);
    if(index_map.find(new_val) == index_map.end()) {
        std::string cs;
        for (std::pair< const std::pair<int,int>, std::size_t> i :index_map) {
            cs = cs + std::to_string(i.second) + ":";
            cs = cs + std::to_string(i.first.first) + ",";
            cs = cs + std::to_string(i.first.second) + " ";
        }
        std::string str("Cannot set current area of world '"+name+"' to coordinate ("+std::to_string(new_val.first)+","+std::to_string(new_val.second)+"), area does not exist: " +cs);
        throw std::out_of_range(str);
    }
    current_area_coord = new_val;
}

bool World::move_current_area(Direction dir) {
    std::pair<int,int> new_val = transform_coordinates(current_area_coord,dir);
    if(index_map.find(new_val) == index_map.end()) {
        return false;
    }
    current_area_coord = new_val;
    return true;
}

bool World::start_is_set() const{
    return start_area_is_set;
}

std::pair<int,int> World::transform_coordinates(std::pair<int,int> coord, Direction dir) {
    std::pair<int,int> new_val(coord);
    switch(dir) {
    case DIRECTION_NORTH:
        new_val.first = coord.first;
        new_val.second = coord.second + 1;
        break;
    case DIRECTION_EAST:
        break;
    case DIRECTION_SOUTH:
        new_val.first = coord.first;
        new_val.second = coord.second - 1;
        break;
    case DIRECTION_WEST:
        break;
    default:
        break;
    }
    return new_val;
}

