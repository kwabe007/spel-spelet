#ifndef SCENE_HPP
#define SCENE_HPP

#include <string>
#include "menu.hpp"
#include "areas/area.hpp"

class Scene {
private:
    std::string text;
    Menu* menu_ptr = nullptr;
    Area area;
    bool text_set = false;
    bool area_set = false;

public:
    void set_text(std::string& txt);
    void set_menu(Menu& mn);
    void set_area(Area& ar);

    bool is_set_text()const;
    bool is_set_menu()const;
    bool is_set_area()const;

    std::string& get_text();
    Menu* get_menu_ptr();
    Area& get_area();
    const std::string& get_text()const;
    const Menu* get_menu_ptr()const;
    const Area& get_area()const;


};

#endif
