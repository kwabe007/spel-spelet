#include <iostream>
#include <sstream>
#include "area.hpp"
#include "../conf.hpp"
#include "../entities/human.hpp"
#include "../exceptions/fileexcept.hpp"
#include "../parse.hpp"
#include "../debug/debugmacro.h"

Area::Area() :name {"none"}, description{"none"}{

}

Area::Area(const std::string& resource) {
    debug_println(BIT5, "Constructing area from resource '" << resource << "'...");
    std::string contents = tools::read_resource(resource);
    std::stringstream ss_contents(contents);
    std::getline(ss_contents, name);
    std::getline(ss_contents, description);

    std::string entities_str;
    std::getline(ss_contents, entities_str);
    std::stringstream ss_enti(entities_str);
    while (ss_enti.good()) {
        char c1 = ss_enti.peek();
        if (c1 == CONF.FLAG_RES_ATTR_EMPTY)
            break;
        std::string entity_str;
        ss_enti >> entity_str;
        Entity* ent_ptr = static_cast<Entity*> (tools::parse_entity_from_file(entity_str));
        add_entity(*ent_ptr);
    }
    std::string block_str;
    std::getline(ss_contents, block_str);
    std::stringstream ss_block(block_str);
    debug_println(BIT5, "Read ss_block for area " << name << ": '" << block_str << "'");
    while (ss_block.good()) {
        char c1 = ss_block.peek();
        if (c1 == CONF.FLAG_RES_ATTR_EMPTY)
            break;
        try {
            std::size_t index = -1;
            ss_block >> index;
            std::string direction_str = "BAD";
            ss_block >> direction_str;
            Direction dir = str_to_dir(direction_str);
            set_block(index,dir);
        } catch (const std::exception& e) {
            throw FileException("invalid line for blocking characters in file");
        }
    }
    std::getline(ss_contents, who_block);

    debug_println(BIT5, "Area construction complete");
}

Area::Area(const std::string& nm, const std::string& desc) : name{nm}, description{desc} {

}

Area::~Area(){
    if (talk_menu_ptr) {
        delete talk_menu_ptr;
    }
    if (game_menu_ptr) {
        delete game_menu_ptr;
    }
    for (Entity* ent_ptr : entity_vec) {
        delete ent_ptr;
    }
}

std::string Area::get_name() const {
    return name;
}
std::string Area::get_description() const {
    std::string total_description = description;
    for (auto pair : blocking_map) {
        if (pair.second->is_alive()) {
            total_description += (" " + who_block + " " + dir_to_str(pair.first));
        }
    }
    return total_description;
}

std::size_t Area::get_entity_size() const {
    return entity_vec.size();
}

Entity& Area::get_entity(std::size_t index) {
    return *entity_vec[index];
}

const Entity& Area::get_entity(std::size_t index) const {
    return *entity_vec[index];
}

const Menu& Area::get_talk_menu() {
    if (talk_menu_ptr) {
        delete talk_menu_ptr;
    }
    talk_menu_ptr = new Menu("Who do you want to talk to?");
    for (std::size_t i = 0; i < entity_vec.size();++i) {
        const Entity& entity = *entity_vec[i];
        talk_menu_ptr->add_item(entity.get_name(),entity.get_description());
    }
    talk_menu_ptr->add_back();
    return *talk_menu_ptr;
}

const Menu& Area::get_game_menu() {
    if (game_menu_ptr) {
        return *game_menu_ptr;
    }
    game_menu_ptr = new Menu("Game Menu");
    game_menu_ptr->add_item("Resume game","Resume the game");
    game_menu_ptr->add_item("End game", "End game and go back to main menu", FLOW_BACK);
    return *game_menu_ptr;
}

void Area::set_name(const std::string& str) {
    name = str;
}

void Area::set_description(const std::string& str) {
    description = str;
}

void Area::add_entity(Entity& ent) {
    entity_vec.push_back(&ent);
}

bool Area::is_path_blocked(Direction dir) const {
    if (blocking_map.empty())
        return false;
    auto search = blocking_map.find(dir);
        if(search == blocking_map.end())
            return false;
    if (search->second->is_alive())
        return true;
    return false;
}

void Area::set_block(std::size_t index, Direction dir) {
    if(index >= entity_vec.size())
            throw std::out_of_range("Can not set entity at index " + std::to_string(index) + " to block path, in area " + name + ": index out of range");
    Entity* ent = entity_vec[index];
    blocking_map[dir] = ent;
    debug_println(BIT5, "Entity " << ent->get_name() << " is now blocking a path in dir " << dir << " in area " << name);
}

void Area::reset_direction() {
    selected_direction = default_direction;
}

Direction Area::str_to_dir(const std::string& str) {
    std::unordered_map<std::string, Direction> str_to_direction = {
        { "north", DIRECTION_NORTH },
        { "east", DIRECTION_EAST },
        { "south", DIRECTION_SOUTH },
        { "west", DIRECTION_WEST },
    };

    return str_to_direction.at(str);
}

std::string Area::dir_to_str(Direction dir) {
    std::unordered_map<Direction, std::string,EnumClassHash> direction_to_str = {
        { DIRECTION_NORTH, "north" },
        { DIRECTION_EAST, "east" },
        { DIRECTION_SOUTH, "south" },
        { DIRECTION_WEST, "west" },
    };
    return direction_to_str.at(dir);
}
