
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
 * 3 - ENTITIES
 * 4 - PARSE
 * 5 - AREAS
 * 6 - ITEMS
 */

/* TODO:
 * DESTRUCTORS FOR SCENE(WORLD,MAP,TEXT), WORLD(AREA), AREA (ENTITIES,OBJECTS)
 * ADD NAMESPACE
 * Check EXIT CODE AFTER SYSTEM CALL TO STTY
 */

using namespace std;
int GLOBAL_DEBUG_LEVEL = 0; //Will be set from the command-line in main source file
unsigned int GLOBAL_DEBUG_BITS = 1<<3;
ofstream ERR_FS("errlog");
Human PLAYER(CONF.get_path_resource()+"units/player");


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
    UI::set_buffer_mode(0);
    debug_println(BIT0,"testing1,2");
    while (true) {

        //PLAYER = Human(CONF.get_path_resource()+"units/player");
        Menu mainmenu("Main Menu");
        mainmenu.add_item("New Game","this is option 1");
        mainmenu.add_item("Load","this is option 2");
        mainmenu.add_item("Help","this is option 3");
        mainmenu.add_item("Exit","this is option 4",FLOW_BACK);
        /*Scene scene1;
        World firstworld("Kvarnamala");
        Building room1("map-forest1");
        Building room1("map-forest2");*/


        Scene scene2;
            Text intro("txt-intro");
        scene2.set_text(intro);
            World firstworld("Kvarnamala");
                //Building firstroom("map-spybar");
                //Building secondroom("map-soapbar");
                Building firstroom("map-forest1");
                Building secondroom("map-forest2");
                Building thirdroom("map-cscmainhall");
                Building fourthroom("map-csccomprooms");
                Building fifthroom("map-cscthrone");
            firstworld.add_area(firstroom);
            firstworld.add_area(secondroom);
            firstworld.add_area(thirdroom);
            firstworld.add_area(fourthroom);
            firstworld.add_area(fifthroom);
            firstworld.set_start_area(0,0);

        scene2.set_world(firstworld);
        vector<Scene*> vec;

        vec.push_back(&scene2);
        debug_println(BIT0,"Pushed back the scenes");

        UI::present_menu(mainmenu);
        if (mainmenu.get_flow_of_selected() == FLOW_BACK) break;
        auto it = vec.begin();
        while(it < vec.end()) {
            SceneFlow flow = UI::play_scene(**it);
            if (flow == SCENE_FLOW_STOP) {
                break;
            } else {
                ++it;
            }
        }
    }

    UI::set_buffer_mode(1);


    return 0;
}
