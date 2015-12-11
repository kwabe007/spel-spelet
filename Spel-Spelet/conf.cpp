#include "conf.hpp"
#include "exceptions/fileexcept.hpp"

std::string Conf::get_path_resource(const std::string& res) {
    if (res.size() == 0)
    return RES_PATH;
    auto search = RES_FILE_TYPE_LOOKUP.find(res);
    ResourceType type = TYPE_NONE;
    if(search != RES_FILE_TYPE_LOOKUP.end()) {
        type = RES_FILE_TYPE_LOOKUP[res];
    }
    else {
        throw FileException("Failed to find resource " + res + " among valid resources");
    }
    std::string trail_path(RES_TYPE_PATH_LOOKUP[type]);
    return RES_PATH + trail_path + res;
}

int Conf::get_damage_var_low() {
    return DAMAGE_VAR_LOW;
}

int Conf::get_damage_var_high() {
    return DAMAGE_VAR_HIGH;
}
