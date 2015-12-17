#include "armor.hpp"
#include "../debug/debugmacro.h"
#include "../exceptions/fileexcept.hpp"
#include "../entities/entity.hpp"

Armor::Armor(std::string filename) {
    std::ifstream fs_item (filename);
    if (!fs_item.good()) {
        throw FileException("File '" + filename + "' not found or is empty");
    }
    fs_item >> name;
    fs_item >> description;
    fs_item >> dp;
    debug_println(BIT6,"Armor created from file '" << filename << "' name: " << name << " description: " << description << " dp: " << dp);
}

Armor::Armor(std::stringstream& ss) : Item::Item(ss){
    if (!ss.good()) {
        throw FileException("String stream is empty");
    }
    std::string temp;
    std::getline(ss, temp);
    dp = std::stoi(temp);
    debug_println(BIT6,"Armor created from string stream name: " << name << " description: " << description << " dp: " << dp);
}

int Armor::get_dp() const {
    return dp;
}

std::string Armor::get_description() const {
    return description;
}

int Armor::action() {
    if (!owner)
        throw std::invalid_argument("Armor " + name + "has no owner and can not be equipped");
    owner->equip_armor(*this);
    return 0;
}

