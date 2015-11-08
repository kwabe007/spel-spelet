#ifndef UI_HPP
#define UI_HPP

#include <string>
#include "menu.hpp"
#include "canvas.hpp"

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
    static const unsigned char COMMAND_ENTER = 13;

    static const std::string ANSI_MOVE_UP("\e[A");


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

    void present_menu(const Menu& menu);

    void print_canvas();

    void reset_output_marker();

    /* Changes the buffer mode, NOTE: only works on terminal using stty
     * 0 for unbuffered, 1 for buffered
     */
    void set_buffer_mode(int i);


	//show_menu();
};

#endif // !UI_HPP
