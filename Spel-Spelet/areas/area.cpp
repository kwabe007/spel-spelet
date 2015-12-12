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
    debug_println(BIT5, "Constructing area from file '" << resource << "'...");
    std::string contents = tools::read_resource(resource);
    std::stringstream ss_cont(contents);
    std::getline(ss_cont, name);
    std::getline(ss_cont, description);
    std::string entities_str;
    std::getline(ss_cont, entities_str);
    std::stringstream ss_enti(entities_str);
    while (ss_enti.good()) {
        std::string entity_str;
        ss_enti >> entity_str;
        Entity* ent_ptr = static_cast<Entity*> (tools::parse_entity_from_file(CONF.get_path_resource(entity_str)));
        add_entity(*ent_ptr);
    }
    debug_println(BIT5, "Area construction complete");
}

Area::Area(const std::string& nm, const std::string& desc) : name{nm}, description{desc} {

}

Area::~Area(){
    if (talk_menu_ptr) {
        delete talk_menu_ptr;
    }
    for (Entity* ent_ptr : entity_vec) {
        delete ent_ptr;
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
