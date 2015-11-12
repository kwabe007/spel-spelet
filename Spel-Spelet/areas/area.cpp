#include "area.hpp"

Area::Area() : next_area_vec{DIRECTION_COUNT,nullptr},
extra_area_vec{0}, description{"none"}{
}

Area::Area(const Area& ref) : next_area_vec{ref.next_area_vec},
extra_area_vec{ref.extra_area_vec}, description{ref.description} {
}

Area& Area::operator=(const Area& ref) {
    next_area_vec = ref.next_area_vec;
    extra_area_vec = ref.extra_area_vec;
    description = ref.description;
    return *this;
}

std::string Area::get_description() const {
    return description;
}

void Area::set_description(const std::string& str) {
    description = str;
}
