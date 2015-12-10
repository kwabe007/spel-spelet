#ifndef UI_HPP
#define UI_HPP

#include <algorithm>
#include <string>
#include "menus/menu.hpp"
#include "canvas.hpp"
#include "scene.hpp"
#include "texts/text.hpp"


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
    static const unsigned char COMMAND_SPACE = ' ';
    static const unsigned char COMMAND_FIGHT = 'f';
    static const unsigned char COMMAND_INVENTORY = 'i';
    static const unsigned char COMMAND_ENTER = 13;
    static const unsigned char COMMAND_TERMINATE = 3;

    static const std::string CONTROL_NORTH ("go N");
    static const std::string CONTROL_EAST ("go E");
    static const std::string CONTROL_SOUTH ("go S");
    static const std::string CONTROL_WEST ("go W");

    static const std::string FIGHT_HINT("F = Fight");
    static const std::string ANSI_MOVE_UP("\e[A");
    static const unsigned char MENU_DELIMITER('_');
    static const unsigned char BATTLE_DELIMITER('_');
    static const unsigned char CONTROL_DELIMITER('-');

    static const std::string TEXT_ENTER_HINT("Press ENTER");
    static const std::string TEXT_PARTY_DEFEAT ("YOU DEAD");
    static const std::string TEXT_ENEMY_DEFEAT("YOU DEFEATED");
    static const std::string TEXT_NONE_DEFEAT("BATTLE ENDED UNDECIDED");
    static const std::string WHOSTURN("'s turn");
    static const std::string ENEMYSTURN("Enemy's turn");

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

    char get_char();

    SceneFlow play_scene(Scene& scene);
    void show_text(const Text& text);
    void present_menu(const Menu& menu, bool sub = false);
    void play_world(World& area);
    void play_area(Area& area);
    void battle_intro(const Battle& battle);
    BattleOutcome play_battle(Battle& battle);

    void print_canvas();
    void flush_screen();

    void flush_and_clear();

    void reset_output_marker();

    /* Changes the buffer mode, NOTE: only works on terminal using stty
     * 0 for unbuffered, 1 for buffered
     */

    bool is_unbuffered();
    void set_buffer_mode(int i);


	//show_menu();
};

#endif // !UI_HPP
