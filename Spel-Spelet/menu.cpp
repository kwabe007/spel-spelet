#include "menu.hpp"
#include <string>
#include <iostream>

Menu::Menu() {
    capacity = 5;
    items = new MenuItem[capacity];
    size = 0;
}

Menu::Menu(size_t n) {
    capacity = n;
    items = new MenuItem[capacity];
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

Func_Ptr Menu::get_fp(int index) const {
    return items[index].fp_choice;
}

void Menu::fill_matrix(std::string** outer_array) const {
    std::string* inner_array;
    std::string* current_pair;
    std::cout << "size: " << size << std::endl;
    for (unsigned int i = 0; i < size; ++i) {
        inner_array = *(outer_array + i);
        for (unsigned int j = 0; j < ITEM_REPR_STR_COUNT; ++j) {
            std::cout << "Accessing [" << i << "][" << j << "]" << std::endl;
            current_pair = &(*(items + i)->repr_strings);
            *(inner_array  + j) = *(current_pair + j);
        }
    }
}
