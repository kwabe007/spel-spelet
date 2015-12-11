#include "building.hpp"

Building::Building(const std::string& filename) : Indoor::Indoor(filename) {
    fs.close();
}
