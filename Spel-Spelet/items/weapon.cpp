#include "weapon.hpp"
#include "../debug/debugmacro.h"
#include "../exceptions/fileexcept.hpp"

Weapon::Weapon(std::string filename) {
    std::ifstream fs_item (filename);
    if (!fs_item.good()) {
        throw FileException("File '" + filename + "' not found or is empty");
    }
    fs_item >> name;
    fs_item >> description;
    fs_item >> ap;
    debug_println(BIT6,"Weapon created from file '" << filename << "' name: " << name << " description: " << description << " ap: " << ap);
}

Weapon::Weapon(std::stringstream& ss) : Item::Item(ss){
    if (!ss.good()) {
        throw FileException("String stream is empty");
    }
    std::string temp;
    std::getline(ss, temp);
    ap = std::stoi(temp);
    debug_println(BIT6,"Weapon created from string stream name: " << name << " description: " << description << " ap: " << ap);
}

int Weapon::get_ap() const {
    return ap;
}

std::string Weapon::get_description() const {
    return description;
}

int Weapon::action() {
    return 0;
}

