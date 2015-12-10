#include <iostream>
#include "area.hpp"

Area::Area() :name {"none"}, description{"none"}{

}

Area::Area(const std::string nm, const std::string desc) : name{nm}, description{desc} {

}

Area::~Area(){
    /*for (Object* o : stuff){
        delete o;
    }*/
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
