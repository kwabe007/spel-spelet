#include "conf.hpp"
#include <stdexcept>


std::string Conf::get_path_resource(const std::string& res) {
    if (res.size() == 0)
    return RES_PATH;

    std::size_t pos = res.find(RES_TYPE_DELIM);
    if (pos == std::string::npos)
        throw std::invalid_argument("Resource '" + res + "' is missing '" + RES_TYPE_DELIM +  "'-separated prefix");

    std::string prefix = res.substr(0,pos);
    auto search = RES_TYPE_PATH_LOOKUP.find(prefix);
    if(search == RES_TYPE_PATH_LOOKUP.end())
        throw std::invalid_argument("Failed to find resource " + res + " among valid resources");

    std::string type_path = RES_TYPE_PATH_LOOKUP[prefix];
    return RES_PATH + type_path + res;
}

int Conf::get_damage_var_low() {
    return DAMAGE_VAR_LOW;
}

int Conf::get_damage_var_high() {
    return DAMAGE_VAR_HIGH;
}
