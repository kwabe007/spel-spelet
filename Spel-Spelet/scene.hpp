#ifndef SCENE_HPP
#define SCENE_HPP

#include <string>
#include "menu.hpp"

class Scene {
private:
    std::string* text = nullptr;
    Menu* menu = nullptr;
    Scene* next_ptr = this;
    //Area* area;


public:
    std::string* set_text(std::string& txt);
    Menu* set_menu(Menu& mn);

    bool has_prologue()const;
    bool has_menu()const;
    //bool hasArea()const;

    std::string& get_text()const;
    Menu& get_menu()const;
    Scene* get_next_ptr() const;
    //Area* get_area()const;

};

#endif
