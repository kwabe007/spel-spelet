#include <string>
#include "scene.hpp"
#include "menu.hpp"

Menu* Scene::set_menu(Menu& mn) {
    menu = &mn;
    return menu;
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
    if (menu) return true;
    return false;
}

Menu& Scene::get_menu() const {
    return *menu;
}

Scene* Scene::get_next_ptr() const {
    return next_ptr;
}

std::string& Scene::get_text() const {
    return *text;
}
