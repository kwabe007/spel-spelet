#include "menu.hpp"
#include <string>
#include <iostream>

Menu::Menu() {
    capacity = 5;
    items = new MenuItem[capacity];
    size = 0;
}

Menu::Menu(const std::string nm, size_t n) {
    capacity = n;
    items = new MenuItem[capacity];
    name = nm;
    size = 0;
}

Menu::~Menu() {
    delete[] items;
}

int Menu::add_item(const std::string name, const std::string desc, const Func_Ptr fp){
    MenuItem new_item(name,desc,fp);
    if (size < capacity )items[size]= new_item;
    else return -1;
    items[size] = new_item;
    ++size;
    return 0;
}

int Menu::clear(){
    size = 0;
    return 0;
}

std::string Menu::get_name() const{
    return name;
}
std::string Menu::get_desc() const{
    return description;
}

Func_Ptr Menu::get_fp(int index) const {
    return items[index].fp_choice;
}
size_t Menu::get_size() const {
    return size;
}

void Menu::fill_matrix(std::string** outer_array) const {
    std::string* inner_array;
    std::string* current_pair;

    for (unsigned int i = 0; i < size; ++i) {
        inner_array = *(outer_array + i);
        for (unsigned int j = 0; j < ITEM_REPR_STR_COUNT; ++j) {

            current_pair = &(*(items + i)->repr_strings);
            *(inner_array  + j) = *(current_pair + j);
        }
    }
}
