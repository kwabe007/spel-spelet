#include "forest.hpp"

Forest::Forest(const std::string& str) : Outdoor(str) {

}

std::string Forest::get_type() const {
    return "Forest";
}
