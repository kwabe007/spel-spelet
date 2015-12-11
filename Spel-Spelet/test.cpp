
#include <csignal>
#include <execinfo.h>
#include <vector>
#include <iostream>
#include <unistd.h>
#include "menus/menu.hpp"
#include "ui.hpp"
#include "parse.hpp"
#include "matrix.hpp"
#include "scene.hpp"
#include "areas/building.hpp"
#include "entities/human.hpp"
#include "areas/world.hpp"
#include "debug/debugmacro.h"
#include "texts/text.hpp"
#include "conf.hpp"


/* BITS
 * 0 - GENERAL
 * 1 - UI
 * 2 - CANVAS
 *
 */

/* TODO:
 * Check EXIT CODE AFTER SYSTEM CALL TO STTY
 * DESTRUCTORS FOR SCENE(WORLD,MAP,TEXT), WORLD(AREA), AREA (ENTITIES,OBJECTS)
 * ADD THROW IN MENU CLASS (GET_FP)
 * ADD NAMESPACE
 */

using namespace std;
int GLOBAL_DEBUG_LEVEL = 0; //Will be set from the command-line in main source file
unsigned int GLOBAL_DEBUG_BITS = 3;
ofstream ERR_FS("errlog");


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


int main(int argc, char** argv) {
signal(SIGSEGV, handler);
    UI::setup();
    debug_println(BIT0,"testing1,2");


    Scene scene;
    Menu mainmenu("Main Menu");
    mainmenu.add_item("New Game","this is option 1");
    mainmenu.add_item("Load","this is option 2");
    mainmenu.add_item("Help","this is option 3");
    mainmenu.add_item("Exit","this is option 4",FLOW_BACK,FUNCTION_EXIT);
    scene.set_menu(mainmenu);

    Scene scene2;
        World firstworld("Kvarnamala");
            Building room("Plattan", "Smells like shit here");
                Human luffare;
            room.add_entity(luffare);
            Building secondroom("Hötorget", "You're at the marketplace but watch out for junkies");
                Human pundare(CONF.get_path_resource("junkie"));
            secondroom.add_entity(pundare);
        firstworld.add_area(room);
        firstworld.add_area(secondroom);
        firstworld.set_start_area(0,0);
    scene2.set_world(firstworld);

    Text text("texts/japan");
    debug_println(BIT0,text.get_text());

    Scene scene3;
    Menu secondmenu("Second Menu");
    secondmenu.add_item("Samla kamrater", "this is option 1");
    secondmenu.add_item("Jaga kulturberikare", "this is option 2");
    scene3.set_menu(secondmenu);

    vector<Scene*> vec;

    vec.push_back(&scene);
    vec.push_back(&scene2);
    vec.push_back(&scene3);
    debug_println(BIT0,"Pushed back the scenes");

    UI::set_buffer_mode(0);
    vector<Scene*>::iterator it = vec.begin();
    while(it < vec.end()) {
        SceneFlow flow = UI::play_scene(**it);
        if (flow == SCENE_FLOW_STOP) {
            it = vec.begin();
        } else {
            ++it;
        }
    }

    //UI::present_menu(mainmenu);
    UI::set_buffer_mode(1);


    return 0;
}
