/* Header file containing configurations for the whole game. */

#ifndef CONF_HPP
#define CONF_HPP

#include <string>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <random>
#include <unordered_map>

class Conf {
private:
/*Path to were the resources are*/
const std::string RES_PATH = "res/eng/";

enum ResourceType {
    TYPE_UNIT,
    TYPE_MAP,
    TYPE_WEAPON,
    TYPE_NONE,
};

struct EnumClassHash
{
    template <typename T>
    std::size_t operator()(T t) const
    {
        return static_cast<std::size_t>(t);
    }
};

std::unordered_map<std::string, ResourceType> RES_FILE_TYPE_LOOKUP = {
        {"junkie", TYPE_UNIT},
        {"micke_p", TYPE_UNIT},
        {"soapbar", TYPE_MAP},
        {"spybar", TYPE_MAP},
        {"fists", TYPE_WEAPON},
    };

std::unordered_map<ResourceType, std::string, EnumClassHash> RES_TYPE_PATH_LOOKUP =
    {
        {TYPE_UNIT, "units/"},
        {TYPE_MAP, "maps/"},
        {TYPE_WEAPON, "weapons/"},
    };

/*Splash screen settings*/
const bool SHOW_SPLASH = true;
const int splc = 3; //Amount of splash screens. Note that splash screen files from 0 to (splc-1) must exist if splc is larger than 0;

const int DAMAGE_VAR_LOW = -2; //Lower bound of variation in damage dealt
const int DAMAGE_VAR_HIGH = 2; //Higher bound of variation in damage dealt

public:
std::string get_path_resource(const std::string& res = "");
int get_damage_var_low();
int get_damage_var_high();
};

static Conf CONF;

#endif
