
#include <csignal>
#include <execinfo.h>
#include <vector>
#include <iostream>
#include <unistd.h>
#include "menu.hpp"
#include "ui.hpp"
#include "parse.hpp"
#include "matrix.hpp"
#include "scene.hpp"
#include "areas/building.hpp"

int GLOBAL_DEBUG_LEVEL = 0; //Will be set from the command-line in main source file


using namespace std;

/* TODO:
 * Check EXIT CODE AFTER SYSTEM CALL TO STTY
 * CREATE VIRTUAL CLASS SCENE
 * ADD AUTOMATIC REALLOCATION TO MENU
 * ADD COPY CTOR AND ASS OPERATOR TO MENU
 * ADD THROW IN MENU CLASS (GET_FP)
 * ADD NAMESPACE
 */

void handler(int sig) {
  void *array[10];
  size_t size;

  // get void*'s for all entries on the stack
  size = backtrace(array, 10);

  // print out all the frames to stderr
  fprintf(stderr, "Error: signal %d:\n", sig);
  backtrace_symbols_fd(array, size, STDERR_FILENO);
  exit(1);
}

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
signal(SIGSEGV, handler);

    UI::setup();
    UI::reset_output_marker();


    /*MenuAction action_nothing;

    Menu helpmenu("Sub-menu", 2);
    helpmenu.add_item("This does nothing", "this is option 1");
    helpmenu.add_item("Back", "this is option 2", action_nothing);

    MenuAction action(&secondmenu);
    MenuAction action_sub_menu(&helpmenu);
    action.add_function(&exit);*/

    Scene scene;
    Menu mainmenu("Main Menu", 4);
    mainmenu.add_item("New Game", "this is option 1");
    mainmenu.add_item("Load", "this is option 2");
    mainmenu.add_item("Help", "this is option 3");
    mainmenu.add_item("Exit", "this is option 4");
    scene.set_menu(mainmenu);

    Scene scene2;
    Building room("Your Room", "Wake up, WAKE THE FUCK UP!");
    scene2.set_area(room);

    Scene scene3;
    Menu secondmenu("Second Menu", 2);
    secondmenu.add_item("Samla kamrater", "this is option 1");
    secondmenu.add_item("Jaga kulturberikare", "this is option 2");
    scene3.set_menu(secondmenu);


    vector<Scene*> vec;
    std::cerr << "pushing menu" << std::endl;
    vec.push_back(&scene);
    vec.push_back(&scene2);
    vec.push_back(&scene3);

    UI::set_buffer_mode(0);
    vector<Scene*>::iterator it;
    std::cerr << "going through scenes" << std::endl;
    for(it = vec.begin();it < vec.end();++it) {
        std::cerr << "playing scene" << std::endl;
        UI::play_scene(**it);
    }

    //UI::present_menu(mainmenu);
    UI::set_buffer_mode(1);


    return 0;
}
