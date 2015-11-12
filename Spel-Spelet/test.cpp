
#include <vector>
#include <iostream>
#include "menu.hpp"
#include "ui.hpp"
#include "parse.hpp"
#include "matrix.hpp"
#include "scene.hpp"

int GLOBAL_DEBUG_LEVEL = 0; //Will be set from the command-line in main source file


using namespace std;

/* TODO:
 * CREATE VIRTUAL CLASS SCENE
 * ADD AUTOMATIC REALLOCATION TO MENU
 * ADD COPY CTOR AND ASS OPERATOR TO MENU
 * ADD THROW IN MENU CLASS (GET_FP)
 * ADD NAMESPACE
 */

int exit() {
    if (UI::is_unbuffered())
        UI::set_buffer_mode(1);
    std::exit(EXIT_SUCCESS);
}
const Menu* runnable2(const Menu* menu) {
    cerr << "22222" << endl;
    return menu;
}
const Menu* runnable3(const Menu* menu) {
    cout << "3333333" << endl;
    return nullptr;
}

int main(int argc, char** argv) {
    Menu mainmenu("Main Menu", 4);
    UI::setup();
    UI::reset_output_marker();

    MenuAction action_nothing;
    Menu secondmenu("Second Menu", 2);
    secondmenu.add_item("Hulu and Hang", "this is option 1");
    secondmenu.add_item("Netflix and Chill", "this is option 2", action_nothing);

    Menu helpmenu("Second Menu", 2);
    secondmenu.add_item("This does nothing", "this is option 1");
    secondmenu.add_item("Back", "this is option 2", action_nothing);

    MenuAction action(&secondmenu);
    MenuAction action_sub_menu(&helpmenu);
    action.add_function(&exit);
    mainmenu.add_item("New Game", "this is option 1", action_nothing);
    mainmenu.add_item("Load", "this is option 2", action_nothing);
    mainmenu.add_item("Help", "this is option 3", action_sub_menu);
    mainmenu.add_item("Exit", "this is option 3", action);

    Scene scene;
    scene.set_menu(mainmenu);
    Scene scene2;
    scene2.set_menu(secondmenu);

    vector<Scene*> vec;
    vec.push_back(&scene);
    vec.push_back(&scene2);

    UI::set_buffer_mode(0);
    vector<Scene*>::iterator it;
    for(it = vec.begin();it < vec.end();++it) {
        UI::play_scene(**it);
    }

    //UI::present_menu(mainmenu);
    UI::set_buffer_mode(1);


    return 0;
}
