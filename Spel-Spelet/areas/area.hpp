#ifndef AREA_HPP
#define AREA_HPP
#include <string>
#include <vector>
#include "../entities/entity.hpp"

enum Direction {
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
    std::string name;
    std::string description;

    std::vector<Entity> entity_vec;
    //std::vector<Objects*> stuff;

public:
    Area();
    Area(const std::string nm, const std::string desc);
    Area(const Area& ref) = delete;
    //Area& operator=(const Area& ref);

    int selected_direction = DIRECTION_NORTH;
    std::string get_name() const;
    std::string get_description() const;
    std::size_t get_entity_size() const;
    Entity& get_entity(std::size_t index);
    const Entity& get_entity(std::size_t index) const;

    void set_name(const std::string& str);
    void set_description(const std::string& str);
    void add_entity(const Entity& ent);

    ~Area();
    //void initiate_fight();

};


#endif
