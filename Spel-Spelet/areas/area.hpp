#ifndef AREA_HPP
#define AREA_HPP
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include "../entities/entity.hpp"
#include "../menus/menu.hpp"

class EnumClassHash
{
public:
    template <typename T>
    std::size_t operator()(T t) const
    {
        return static_cast<std::size_t>(t);
    }
};

enum Direction {
    DIRECTION_NONE = -1,
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
protected:
    std::string name;
    std::string description;
    std::string who_block;
    Menu* talk_menu_ptr = nullptr;
    Menu* game_menu_ptr = nullptr;
    Menu* item_menu_ptr = nullptr;
    bool end = false;
    std::fstream fs;
    std::unordered_map<Direction,Entity*, EnumClassHash> blocking_map;
    std::vector<Entity*> entity_vec;
    //std::vector<Objects*> stuff;

public:
    Area();
    Area(const std::string& filename);
    Area(const std::string& nm, const std::string& desc);
    Area(const Area& ref) = delete;
    //Area& operator=(const Area& ref);
    const Direction default_direction = DIRECTION_NORTH;
    Direction selected_direction = default_direction;
    std::string get_name() const;
    std::string get_description() const;
    std::size_t get_entity_size() const;
    Entity& get_entity(std::size_t index);
    const Entity& get_entity(std::size_t index) const;
    const Menu& get_talk_menu();
    const Menu& get_game_menu();

    void set_name(const std::string& str);
    void set_description(const std::string& str);
    void add_entity(Entity& ent);
    bool is_path_blocked(Direction dir) const;
    void set_block(std::size_t index, Direction dir);
    void set_end(bool b);
    bool is_end();

    void reset_direction();

    static Direction str_to_dir(const std::string& str);

    static std::string dir_to_str(Direction dir);
    virtual ~Area();
    virtual std::string get_type() const=0;

};


#endif
