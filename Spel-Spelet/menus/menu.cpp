#include "menu.hpp"
#include <string>
#include <stdexcept>
#include <iostream>

Menu::Menu() {
}

Menu::Menu(const std::string nm) : name{nm} {
}

Menu::~Menu() {
}

std::string Menu::operator[](std::size_t index)const {
    return items[index].repr_strings[0];
}

int Menu::add_item(const std::string name, const std::string desc){
    items.push_back(MenuItem(name,desc));
    return 0;
}

int Menu::add_item(const std::string name, const std::string desc, Menu& submenu){
    items.push_back(MenuItem(name,desc,submenu));
    return 0;
}

int Menu::add_item(const std::string name, const std::string desc, std::size_t* target_val, std::size_t set_to){
    items.push_back(MenuItem(name,desc,target_val,set_to));
    return 0;
}

int Menu::add_item(const std::string name, const std::string desc, FunctionType type) {
    items.push_back(MenuItem(name,desc,type));
    return 0;
}

/*int Menu::add_back() {
    MenuItem new_item("Back","Return",&selected_item,-1);
    if (size < capacity )items[size]= new_item;
    else return -1;
    items[size] = new_item;
    ++size;
    return 0;
}*/


void Menu::clear(){
    items.clear();
}

bool Menu::move_up() const {
    if (selected_item <= 0){
        selected_item = items.size()-1;
        return true;
    }
    else --selected_item;
    return false;
}

bool Menu::move_down() const {
    if (selected_item >= items.size()-1){
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

Menu* Menu::run_function() {
    items[selected_item].functionobject();
    return items[selected_item].nextmenu;
}

const Menu* Menu::run_function() const {
    items[selected_item].functionobject();
    return items[selected_item].nextmenu;
}

/*Menu* Menu::run_function(std::size_t index){
    items[index].functionobject();
    return items[index].nextmenu;
}*/

std::size_t Menu::get_size() const {
    return items.size();
}

bool Menu::is_selected(std::size_t index)const{
    return index == selected_item;
}

std::size_t Menu::get_selected()const{
    return selected_item;
}

void Menu::fill_matrix(std::string** outer_array) const {
    std::string* inner_array;

    for (unsigned int i = 0; i < items.size(); ++i) {
        inner_array = *(outer_array + i);
        for (unsigned int j = 0; j < ITEM_REPR_STR_COUNT; ++j) {

            const std::string* current_pair = (items[i].repr_strings);
            *(inner_array  + j) = *(current_pair + j);
        }
    }
}
