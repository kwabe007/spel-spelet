#include <string>
#include <iostream>
#include "scene.hpp"
#include "menu.hpp"

void Scene::set_menu(Menu& mn) {
    menu_ptr = &mn;
    menu = *menu_ptr;
}

void Scene::set_area(Area& ar) {
    area = &ar;
}

std::string* Scene::set_text(std::string& txt) {
    text = &txt;
    return text;
}

bool Scene::has_prologue() const {
    if (text) return true;
    return false;
}

bool Scene::has_menu() const {
    if (menu_ptr) return true;
    return false;
}

Menu& Scene::get_menu() const {
    return *menu_ptr;
}

Scene* Scene::get_next_ptr() const {
    return next_ptr;
}

std::string& Scene::get_text() const {
    return *text;
}
