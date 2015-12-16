#include "menu.hpp"
#include <string>
#include <stdexcept>
#include <iostream>

Menu::Menu() {
}

Menu::Menu(const std::string nm) : name{nm} {
}

Menu::~Menu() {
    /*for(Menu* submenu : submenus) {
        delete submenu;
    }*/
}


std::string Menu::operator[](std::size_t index)const {
    return items[index].repr_strings[0];
}

int Menu::add_back() {
    add_item("Back","Return",FLOW_BACK);
    return 0;
}

int Menu::add_item(const std::string& name, const std::string& desc, Item& item) {
    add_item(name,desc,FLOW_STAY,FUNCTION_NONE,nullptr,0,nullptr,&item);
    return 0;
}

int Menu::add_item(const std::string& name, const std::string& desc, Menu& submenu) {
    add_item(name,desc,FLOW_FORWARD,FUNCTION_NONE,nullptr,0,&submenu);
    return 0;
}

int Menu::add_item(const std::string& name, const std::string& desc, MenuFlow flow,
                   FunctionType f_type, std::size_t* init_val, std::size_t set_val,
                   Menu* submenu, Item* item_ptr) {
    items.push_back(MenuItem(name,desc,flow,f_type,init_val,set_val,submenu,item_ptr));
    return 0;
}

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

void Menu::run_function() {
    items[selected_item].functionobject();
}

void Menu::run_function() const {
    items[selected_item].functionobject();
}

std::size_t Menu::get_size() const {
    return items.size();
}

bool Menu::is_selected(std::size_t index)const{
    return index == selected_item;
}

std::size_t Menu::get_selected()const{
    return selected_item;
}

MenuFlow Menu::get_flow_of_selected() const {
    return items[selected_item].flow;
}

Menu& Menu::get_menu_of_selected() {
    MenuItem& item = items[selected_item];
    if(item.nextmenu == nullptr) {
        throw std::out_of_range("Can not get menu of item " + item.get_name() + " : it is undefined");
    }
    return *item.nextmenu;
}

const Menu& Menu::get_menu_of_selected() const {
    const MenuItem& item = items[selected_item];
    if(item.nextmenu == nullptr) {
        throw std::out_of_range("Can not get menu of item " + item.get_name() + " : it is undefined");
    }
    return *item.nextmenu;
}

std::string Menu::get_description_of_selected() const {
    return items[selected_item].repr_strings[1];
}


bool Menu::selected_has_menu() const {
    if(items[selected_item].nextmenu == nullptr) return false;
    return true;
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
