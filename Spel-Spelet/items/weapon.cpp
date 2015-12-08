#include "weapon.hpp"
#include "../debug/debugmacro.h"

Weapon::Weapon(std::string filename) : {
    std::ifstream fs_item (filename);

    if (!fs_item.good()) {

        throw FileException("File '" + filename + "' not found or is empty");
    }

    fs_item >> name;
    fs_item >> description;
    fs_item >> ap;
    debug_println(BIT1,"Weapon created from file '" << filename << "' name: " << name << " description: " << description << " ap: " << ap);

}
