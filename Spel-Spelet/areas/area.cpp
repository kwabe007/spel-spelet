#include <iostream>
#include "area.hpp"

Area::Area() : next_area_vec{DIRECTION_COUNT,nullptr},
extra_area_vec{0}, name {"none"}, description{"none"}{
        std::cerr << "area default ctor" << std::endl;
}

Area::Area(const std::string nm, const std::string desc) : name{nm}, description{desc} {
    std::cerr << "str ctor" << std::endl;
}

/*Area::Area(const Area& ref) : next_area_vec{ref.next_area_vec},
extra_area_vec{ref.extra_area_vec}, name{ref.name}, description{ref.description} {
}

Area& Area::operator=(const Area& ref) {
    next_area_vec = ref.next_area_vec;
    extra_area_vec = ref.extra_area_vec;
    name = ref.name;
    description = ref.description;
    return *this;
}*/


const std::string Area::get_name() const {
    return name;
}
const std::string Area::get_description() const {
    return description;
}


void Area::set_name(const std::string& str) {
    name = str;
}

void Area::set_description(const std::string& str) {
    description = str;
}

void Area::add_entity(const Entity& ent) {
    entity_vec.push_back(ent);
}
