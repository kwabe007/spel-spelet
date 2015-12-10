#ifndef SCENE_HPP
#define SCENE_HPP

#include <string>
#include "menus/menu.hpp"
#include "areas/world.hpp"

enum SceneFlow {
    SCENE_FLOW_NORMAL,
    SCENE_FLOW_STOP,
};

class Scene {

private:
    std::string text;
    Menu* menu_ptr = nullptr;
    World* world_ptr = nullptr;
    bool text_set = false;
    bool world_set = false;

public:
    void set_text(std::string& txt);
    void set_menu(Menu& mn);
    void set_world(World& wd);

    bool is_set_text()const;
    bool is_set_menu()const;
    bool is_set_world()const;

    std::string& get_text();
    const std::string& get_text()const;
    Menu& get_menu();
    const Menu& get_menu()const;
    World& get_world();
    const World& get_world()const;


};

#endif
