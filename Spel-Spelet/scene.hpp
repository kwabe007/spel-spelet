#ifndef SCENE_HPP
#define SCENE_HPP

#include <string>
#include "menus/menu.hpp"
#include "areas/world.hpp"
#include "texts/text.hpp"

enum SceneFlow {
    SCENE_FLOW_NORMAL,
    SCENE_FLOW_STOP,
};

class Scene {

private:
    std::string text;
    Menu* menu_ptr = nullptr;
    World* world_ptr = nullptr;
    Text* text_ptr = nullptr;
    bool world_set = false;

public:
    void set_text(Text& txt);
    void set_menu(Menu& mn);
    void set_world(World& wd);

    bool is_set_text()const;
    bool is_set_menu()const;
    bool is_set_world()const;

    Text& get_text();
    Menu& get_menu();
    const Menu& get_menu()const;
    World& get_world();
    const World& get_world()const;


};

#endif
