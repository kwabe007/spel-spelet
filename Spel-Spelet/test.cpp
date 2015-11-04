
#include <iostream>
#include "menu.hpp"
#include "ui.hpp"
#include "parse.hpp"

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
    Menu mainmenu("Main Menu", 3);
    int c;
    /* use system call to make terminal send all keystrokes directly to stdin */
    system ("/bin/stty raw");

    mainmenu.add_item("option 1", "this is option 1", &runnable1);
    mainmenu.add_item("option 2", "this is option 2", &runnable2);
    mainmenu.add_item("option 3", "this is option 3", &runnable3);
    string test = tools::read_file("test/hh");
    UI::present_menu(mainmenu);
    //cout << "\033[F";

    /* use system call to set terminal behaviour to more normal behaviour */
    system ("/bin/stty cooked");
    cout << "\r";
    return 0;
}
