#include "scene.hpp"

void Scene::set_text(Text& txt) {
    text_ptr = &txt;
}

void Scene::set_menu(Menu& mn) {
    menu_ptr = &mn;
}

void Scene::set_world(World& wd) {
    world_ptr = &wd;
}

bool Scene::is_set_text() const {
    if (text_ptr) return true;
    return false;
}

bool Scene::is_set_menu() const {
    if (menu_ptr) return true;
    return false;
}

bool Scene::is_set_world() const {
    if (world_ptr) return true;
    return false;
}

Menu& Scene::get_menu() {
    return *menu_ptr;
}

const Menu& Scene::get_menu() const {
    return *menu_ptr;
}

Text& Scene::get_text() {
    return *text_ptr;
}

World& Scene::get_world(){
    return *world_ptr;
}

const World& Scene::get_world() const {
    return *world_ptr;
}
