#include "party.hpp"



void Party::add_member(Entity& new_member) {
     members.add(&new_member);
}

std::size_t Party::size() const {
     return members.size();
}
