#include "consumable.hpp"
#include "../debug/debugmacro.h"
#include "../exceptions/fileexcept.hpp"
#include "../entities/entity.hpp"

Consumable::Consumable(std::stringstream& ss) : Item::Item(ss){
    if (!ss.good()) {
        throw FileException("String stream is empty");
    }

    std::string temp;
    std::getline(ss, temp);
    hp_healed = std::stoi(temp);
    debug_println(BIT6,"Consumable created from string stream name: " << name << " description: " << description << " health healed: " << hp_healed);
}

int Consumable::action() {
    if (amount < 1)
        return 0;
    if (!owner)
        throw std::invalid_argument("Item " + name + " has no owner and can therefor not pursue action");
    std::pair<bool,int> pr = owner->take_health(hp_healed);
    if (pr.first == true)
        amount -= 1;
    return 0;
}

std::string Consumable::get_description() const {
    return "(x" + std::to_string(amount) + ") " + description;
}

