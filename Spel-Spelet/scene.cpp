#include "scene.hpp"

void Scene::set_text(std::string& txt) {
    text = txt;
    text_set = true;
}

void Scene::set_menu(Menu& mn) {
    menu_ptr = &mn;
}

void Scene::set_area(Area& ar) {
    area = ar;
    area_set = true;
}

bool Scene::is_set_text() const {
    return text_set;
}

bool Scene::is_set_menu() const {
    if (menu_ptr) return true;
    return false;
}

bool Scene::is_set_area() const {
    return area_set;
}

std::string& Scene::get_text(){
    return text;
}

Menu* Scene::get_menu_ptr() {
    return menu_ptr;
}

World& Scene::get_world(){
    return area;
}

const std::string& Scene::get_text() const {
    return text;
}

const Menu* Scene::get_menu_ptr() const {
    return menu_ptr;
}

const World& Scene::get_world() const {
    return area;
}
