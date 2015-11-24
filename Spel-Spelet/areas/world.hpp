#ifndef WORLD_HPP
#define WORLD_HPP

#include <unordered_map>
#include "area.hpp"

class World {
private:
    std::string name;
    std::unordered_map<std::pair<int,int>, std::size_t> index_map;
    std::vector<Area*> areas;
    bool start_area_is_set = false;
    std::pair<int,int> starting_area_coord;
    std::pair<int,int> current_area_coord;
    std::pair<int,int> last_coord_mapped;

    bool auto_setup = true;
    Direction link_direction = DIRECTION_NORTH;


public:
    World();
    World(const std::string name);
    World(const World& ref) = delete;
    ~World();

    World& operator=(const World& ref) = delete;

    void add_area(Area& ar);
    void map_area(std::pair<int,int> coordinates, std::size_t index);
    void set_start_area(std::size_t index);

    Area& current_area();
    const Area& current_area() const;
    Area& get_area(std::size_t index);
    const Area& get_area(std::size_t index) const;

    void set_current_area(int x,int y);
    bool move_current_area(Direction dir);

    bool start_is_set() const;

    static std::pair<int,int> transform_coordinates(std::pair<int,int> coord, Direction dir);


};

#endif
