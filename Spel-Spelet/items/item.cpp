#include "item.hpp"
#include "../exceptions/fileexcept.hpp"
#include "../debug/debugmacro.h"
#include <fstream>

Item::Item() {

}
Item::Item(std::string filename) {
    std::ifstream fs_item (filename);
    if (!fs_item.good()) {

        throw FileException("File '" + filename + "' not found or is empty");
    }
    std::getline(fs_item, name);
    std::getline(fs_item, description);
    debug_println(BIT1,"Item created from file '" << filename << "' has name set to " << name << " and description set to " << description);
}

std::string Item::get_name() const{
    return name;
}
