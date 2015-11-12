#ifndef UI_HPP
#define UI_HPP

#include <algorithm>
#include <string>
#include "menu.hpp"
#include "canvas.hpp"
#include "scene.hpp"


/*Functions and stuff for the text-based User Interface.*/
namespace UI  {

    enum modes {
      BUFFERED,
      UNBUFFERED,
      UNKNOWN,
    };

    static const unsigned char COMMAND_UP = 'w';
    static const unsigned char COMMAND_DOWN = 's';
    static const unsigned char COMMAND_LEFT = 'a';
    static const unsigned char COMMAND_RIGHT = 'd';
    static const unsigned char COMMAND_ENTER = ' ';
    //static const unsigned char COMMAND_ENTER = 13;

    static const std::string ANSI_MOVE_UP("\e[A");
    static const unsigned char MENU_DELIMITER('_');
    static const unsigned char CONTROL_DELIMITER('-');


    static const unsigned int TERMINAL_COLS = 80;
    static const unsigned int TERMINAL_ROWS = 24;


    void setup();
    void finished(unsigned int x);

	void sleep(const std::size_t milliseconds);

	/*Prints input string (text)*/
    void print(const std::string& text);
    /*Prints input string (text) with trailing endline*/
    void println(const std::string& text);

    /* Prints input string (text) with delay (time) between the characters; delay is in milliseconds.
     *If time is not specified, it defaults to 10
     */
	void time_print(const std::string& text, const size_t = 10);

    Scene* play_scene(Scene& scene);
    void present_prologue(const std::string& text);
    void present_menu(const Menu* menu, bool sub = false);
    void play_area(Area& area);

    void print_canvas();
    void flush_screen();

    void reset_output_marker();

    /* Changes the buffer mode, NOTE: only works on terminal using stty
     * 0 for unbuffered, 1 for buffered
     */

    bool is_unbuffered();
    void set_buffer_mode(int i);


	//show_menu();
};

#endif // !UI_HPP
