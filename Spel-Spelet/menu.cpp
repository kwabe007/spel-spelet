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

std::string& Menu::operator[](int index)const {
    return (*(items + index)).repr_strings[0];
}

int Menu::add_item(const std::string name, const std::string desc){
    MenuAction action (this);
    MenuItem new_item(name,desc,action);
    if (size < capacity )items[size]= new_item;
    else return -1;
    items[size] = new_item;
    ++size;
    return 0;
}

int Menu::add_item(const std::string name, const std::string desc, MenuAction action){
    MenuItem new_item(name,desc,action);
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

bool Menu::move_up() const {
    if (selected_item <= 0){
        selected_item = size-1;
        return true;
    }
    else --selected_item;
    return false;
}

bool Menu::move_down() const {
    if (selected_item >= size-1){
        selected_item = 0;
        return true;
    }
    else ++selected_item;
    return false;
}

std::string Menu::get_name() const{
    return name;
}

std::string Menu::get_desc() const{
    return description;
}

MenuAction& Menu::get_action(int index) const {
    return items[index].action;
}

size_t Menu::get_size() const {
    return size;
}

bool Menu::is_selected(std::size_t index)const{
    return index == selected_item;
}

std::size_t Menu::get_selected()const{
    return selected_item;
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
