
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
#include "areas/forest.hpp"
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
 * REDO MENU TO VIRTUAL CLASS WITH SUBCLASSES
 * FIX ITEM SYSTEM!
 * ADD NAMESPACE
 * Check EXIT CODE AFTER SYSTEM CALL TO STTY
 */

using namespace std;
int GLOBAL_DEBUG_LEVEL = 0; //Will be set from the command-line in main source file
unsigned int GLOBAL_DEBUG_BITS = 1<<5;
ofstream ERR_FS("errlog");
Human PLAYER;

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

//signal(SIGSEGV, handler);
    UI::setup();
    UI::set_buffer_mode(0);
    Text intro("txt-disc");
    UI::show_text(intro);
    debug_println(BIT0,"testing1,2");
    //Human* human_ptr = dynamic_cast<Human*> (tools::parse_entity_from_file("unt-pjotr"))
    while (true) {
        PLAYER.reset("unt-pjotr");
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
                Forest forest1("map-forest1");
                Forest forest2("map-forest2");
                Forest forest3("map-forest3");
                Building csc_main_hall("map-cscmainhall");
                Building csc_comp_rooms("map-csccomprooms");
                Building csc_throne("map-cscthrone");
                Building csc_end("map-cscexit");
                    csc_end.set_end(true);
            firstworld.add_and_map_area(forest1,0,0);
            firstworld.add_and_map_area(forest2,0,1);
            firstworld.add_and_map_area(forest3,1,1);
            firstworld.add_and_map_area(csc_main_hall,0,2);
            firstworld.add_and_map_area(csc_comp_rooms,0,3);
            firstworld.add_and_map_area(csc_throne,0,4);

            firstworld.add_and_map_area(csc_end,0,5);
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
