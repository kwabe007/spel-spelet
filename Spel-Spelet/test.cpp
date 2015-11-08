
#include <iostream>
#include "menu.hpp"
#include "ui.hpp"
#include "parse.hpp"
#include "matrix.hpp"

int GLOBAL_DEBUG_LEVEL = 0; //Will be set from the command-line in main source file


using namespace std;

/* TODO:
 * GET STARTED WITH TEXT UI USING CARRIAGE RETURN
 * ADD AUTOMATIC REALLOCATION TO MENU
 * ADD COPY CTOR AND ASS OPERATOR TO MENU
 * ADD THROW IN MENU CLASS (GET_FP)
 * ADD NAMESPACE
 * CREATE A MATRIX CLASS
 * CREATE MEMBER VARIABLE IN MENU THAT CONTAINS MATRIX
 * CREATE A PRINT DELIMITER FUNCTION FOR UI
 * ADD A CHECK FOR STTY
 */

void runnable1(Menu* menu) {
    cout << "BLEEARGH" << endl;
}
void runnable2(Menu* menu) {
    cout << "22222" << endl;
}
void runnable3(Menu* menu) {
    cout << "3333333" << endl;
}


int main(int argc, char** argv) {
    Menu mainmenu("Main Menu", 4);
    UI::setup();
    UI::reset_output_marker();
    mainmenu.add_item("New Game", "this is option 1", &runnable1);
    mainmenu.add_item("Load", "this is option 2", &runnable2);
    mainmenu.add_item("Help", "this is option 3", &runnable3);
    mainmenu.add_item("Exit", "this is option 3", &runnable3);
    UI::set_buffer_mode(0);
    UI::present_menu(mainmenu);
    UI::set_buffer_mode(1);
    return 0;
}
