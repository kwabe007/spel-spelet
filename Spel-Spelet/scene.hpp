#ifndef SCENE_HPP
#define SCENE_HPP

#include <string>
#include "menu.hpp"
#include "areas/area.hpp"

class Scene {
private:
    std::string* text = nullptr;
    Menu menu;
    Menu* menu_ptr = nullptr;
    Scene* next_ptr = this;
    Area* area = nullptr;

public:
    std::string* set_text(std::string& txt);
    void set_menu(Menu& mn);
    void set_area(Area& ar);

    bool has_prologue()const;
    bool has_menu()const;
    //bool hasArea()const;

    std::string& get_text()const;
    Menu& get_menu()const;
    Scene* get_next_ptr() const;
    //Area* get_area()const;

};

#endif
