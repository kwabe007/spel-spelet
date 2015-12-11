#include <iostream>
#include <sstream>
#include "area.hpp"
#include "../conf.hpp"
#include "../entities/human.hpp"
#include "../exceptions/fileexcept.hpp"

Area::Area() :name {"none"}, description{"none"}{

}

Area::Area(const std::string& filename) : fs(filename) {
    if (!fs.good()) {
        throw FileException("File '" + filename + "' not found or is empty");
    }
    std::getline(fs, name);
    std::getline(fs, description);
    std::string entities_str;
    std::getline(fs, entities_str);
    std::stringstream ss(entities_str);
    while (ss.good()) {
        std::string entity_str;
        ss >> entity_str;
        Entity* ent_ptr = new Human(CONF.get_path_resource(entity_str));
        add_entity(*ent_ptr);
    }
}

Area::Area(const std::string& nm, const std::string& desc) : name{nm}, description{desc} {

}

Area::~Area(){
    if (talk_menu_ptr) {
        delete talk_menu_ptr;
    }
}

std::string Area::get_name() const {
    return name;
}
std::string Area::get_description() const {
    return description;
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

void Area::set_name(const std::string& str) {
    name = str;
}

void Area::set_description(const std::string& str) {
    description = str;
}

void Area::add_entity(Entity& ent) {
    entity_vec.push_back(&ent);
}

void Area::reset_direction() {
    selected_direction = default_direction;
}
