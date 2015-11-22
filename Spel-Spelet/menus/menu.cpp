#include "menu.hpp"
#include <string>
#include <stdexcept>
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

Menu::Menu(const Menu& ref) : name(ref.name), description(ref.description) {
    size = ref.size;
    capacity = ref.capacity;
    selected_item = ref.selected_item;
    items = new MenuItem[capacity];
    for (std::size_t i = 0; i < size ; ++i) {
        items[i] = ref.items[i];
    }
}

Menu::~Menu() {
    delete[] items;
}

/*Menu& Menu::operator=(const Menu& ref) {
    size = ref.size;
    capacity = ref.capacity;
    selected_item = ref.selected_item;
    std::cerr << "1" << std::endl;
    delete[] items;
    std::cerr << "2" << std::endl;
    items = new MenuItem[capacity];
    std::cerr << "3" << std::endl;
    for (std::size_t i = 0; i < size ; ++i) {
        std::cerr << "7" << std::endl;
        items[i] = ref.items[i];
        if (ma.menu_to == &ref) {
            items[i].action.menu_to = this;
        }
    }
    std::cerr << "4" << std::endl;
    name = ref.name;
    description = ref.description;
    return *this;
}*/

std::string& Menu::operator[](std::size_t index)const {
    if (index > size) throw std::out_of_range ("unable to access menu item string, out of range");
    return (*(items + index)).repr_strings[0];
}

int Menu::add_item(const std::string name, const std::string desc){
    MenuItem new_item(name,desc);
    if (size < capacity )items[size]= new_item;
    else return -1;
    items[size] = new_item;
    ++size;
    return 0;
}

int Menu::add_item(const std::string name, const std::string desc, Menu& submenu){
    MenuItem new_item(name,desc,submenu);
    if (size < capacity )items[size]= new_item;
    else return -1;
    items[size] = new_item;
    ++size;
    return 0;
}

int Menu::add_item(const std::string name, const std::string desc, std::size_t* target_val, std::size_t set_to){
    MenuItem new_item(name,desc,target_val,set_to);
    if (size < capacity )items[size]= new_item;
    else return -1;
    items[size] = new_item;
    ++size;
    return 0;
}

int Menu::add_item(const std::string name, const std::string desc, FunctionType type) {
    MenuItem new_item(name,desc,type);
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

Menu* Menu::run_function() const {
    items[selected_item].functionobject();
    return items->nextmenu;
}

Menu* Menu::run_function(std::size_t index) const {
    items[index].functionobject();
    return items->nextmenu;
}

std::size_t Menu::get_size() const {
    return size;
}

std::size_t Menu::get_capacity() const {
    return capacity;
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
