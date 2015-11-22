#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <unistd.h>
#include "ui.hpp"
#include "parse.hpp"
//#include "debugmacro.hpp"
#include "canvas.hpp"
#include "scene.hpp"
#include "debug_test_macros/debugmacro.h"
#include "debug_bits.h"
#include "entities/human.hpp"
#include "battle.hpp"


namespace UI {
    void sleep(const std::size_t milliseconds) {
        usleep(milliseconds * 1000); // takes microseconds
    }

    Canvas cvs(TERMINAL_COLS, TERMINAL_ROWS);
    modes MODE = UNKNOWN;

    void setup() {
        for (unsigned int i = 0; i < cvs.get_rows()-1; ++i) {
           std::cout << i << std::endl << "\r";
        }
        //std::cout << ANSI_MOVE_UP;
        reset_output_marker();
    }

    void finished(unsigned int x) {
        for (unsigned int i = 0; i < x; ++i)
        std::cout << ANSI_MOVE_UP;
    }

    void print(const std::string& text) {
        std::cout << text;
    }

    void println(const std::string& text) {
        std::cout << text << std::endl << "\r";
	}

    char get_char() {
        char input;
        input = std::cin.get();
        debug_print(BIT0,("Pressed key: %d\n",input));
        if (input == COMMAND_TERMINATE) {
            if (is_unbuffered())
                set_buffer_mode(1);
            std::exit(EXIT_SUCCESS);
        }
        return input;
    }

    std::string** create_str_matrix(int n, int m) {
        std::string** out_ptr = new std::string*[n];
        for (int i = 0; i < n; ++i) {
            *(out_ptr + i) = new std::string[m];
        }
        return out_ptr;
    }

    void deallocate_str_matrix(std::string** out_ptr, int n) {
        for (int i = 0; i < n; ++i) {
            delete[] *(out_ptr + i);
        }
        delete[] out_ptr;
    }

	void time_print(const std::string& text, const size_t time) {
		/*std::chrono::milliseconds timespan(10); //No support for thread operations in MinGW :( 
		std::this_thread::sleep_for(timespan);*/
		std::string out_text = tools::replace_coding(text);
		std::string::const_iterator it;
        //debug(2, "String to time_print is %s", out_text.c_str());
		for (it = out_text.begin(); it != out_text.end(); ++it) {
			std::cout << *it;
			sleep(time);
		}
        std::cout << std::endl << "\r";
	}
    Scene* play_scene(Scene& scene) {
        if(scene.is_set_text()) present_prologue(scene.get_text());
        if(scene.is_set_menu()) present_menu(scene.get_menu_ptr());
        if(scene.is_set_area()) {std::cerr << "area" << std::endl; play_area(scene.get_area());}

        else std::cerr << "no menu" << std::endl;
        return &scene;
    }

    void present_prologue(const std::string& text) {
    }

    void present_menu(const Menu* menu_ptr, bool sub) {
        std::cerr << "presenting menu " << menu_ptr->get_name() << std::endl << "\r";
        std::cerr << menu_ptr->get_size() << " " << menu_ptr->get_capacity() << std::endl << "\r";
        flush_screen();
        cvs.clear_canvas();
        char choice;
        const Menu* next_menu_ptr;
        while (true) {
            cvs.apply_menu(*menu_ptr);
            print_canvas();
            choice = get_char();
            switch(choice){
            case COMMAND_UP:
                menu_ptr->move_up();
                break; //optional
            case COMMAND_DOWN:
                menu_ptr->move_down();
                break; //optional
            case COMMAND_ENTER:
            case COMMAND_SPACE:
                next_menu_ptr = menu_ptr->run_function(menu_ptr->get_selected());
                if (!next_menu_ptr) goto EndWhile;
                else if (next_menu_ptr == menu_ptr) continue;
                else present_menu(next_menu_ptr, true);
                break; //optional
            default : //Optional
                ;
            }
        }

        EndWhile:
        //std::cout << "choice " << menu.get_selected();
        if (sub) {
            flush_screen();
            cvs.clear_canvas();
        }
        ;
    }

    void play_area(Area& area) {
        flush_screen();
        cvs.clear_canvas();

        char choice;
        while (true) {
            cvs.apply_area(area);
            print_canvas();
            choice = get_char();
            switch(choice){
            case COMMAND_UP:
                area.selected_direction = DIRECTION_NORTH;
                break; //optional
            case COMMAND_DOWN:
                area.selected_direction = DIRECTION_SOUTH;
                break; //optional
            case COMMAND_LEFT:
                area.selected_direction = DIRECTION_WEST;
                break; //optional
            case COMMAND_RIGHT:
                area.selected_direction = DIRECTION_EAST;
                break; //optional
            case COMMAND_ENTER:
            case COMMAND_SPACE:
                 goto EndWhileArea;
                break; //optional
            case COMMAND_FIGHT:
            {
                Menu fightmenu("Who do you want to fight?",area.get_entity_size());

                for (std::size_t i = 0; i < area.get_entity_size(); ++i) {
                    Entity& entity(area.get_entity(i));
                    fightmenu.add_item(entity.get_name(), entity.get_description());
                }
                Menu* m_ptr = &fightmenu;
                present_menu(m_ptr, true);
                //extern Entity PLAYER;
                Entity& chosen_entity(area.get_entity(m_ptr->get_selected()));
                std::cerr << chosen_entity.get_name() << std::endl;
                Battle battle(chosen_entity);
                battle_intro(battle);
                int outcome = play_battle(battle);
                if (outcome == -1) {
                    std::cerr << "you got rekt, gg no re" << std::endl;
                }
                if (outcome == 1) {
                    std::cerr << "great victory" << std::endl;
                }
                goto EndWhileArea;
            }

            default : //Optional
                ;
            }
        }
    EndWhileArea:
    ;
    }
    void battle_intro(const Battle& battle) {
        flush_screen();
        cvs.clear_canvas();

        char choice;
        while (true) {
            cvs.apply_battle_intro(battle);
            print_canvas();
            choice = get_char();
            switch(choice){
            case COMMAND_ENTER:
            case COMMAND_SPACE:
                 goto EndWhile;
                break; //optional
            default : //Optional
                ;
            }
        }
        EndWhile:
        ;
    }

    int play_battle(Battle& battle) {
        flush_screen();
        cvs.clear_canvas();
        char choice;
        Menu* next_menu_ptr;
        Menu current_menu = battle.get_current_menu();
        int battlestate = 0;

        while (true) {
            std::cerr << "battlestate*** " << battlestate << std::endl;
            cvs.apply_battle_fight(battle);
            print_canvas();
            sleep(1000);
            if (battle.turn == ENEMY_TURN) {
                battlestate = battle.action();
                cvs.apply_battle_fight(battle);
                print_canvas();
            } else if (battle.turn == PARTY_TURN) {
                choice = get_char();
                switch(choice){
                case COMMAND_ENTER:
                case COMMAND_SPACE:
                    next_menu_ptr = current_menu.run_function();
                    if (!next_menu_ptr) {
                    battle.back_to_main_menu();
                    battlestate = battle.action();
                    }
                    else if (next_menu_ptr == &current_menu) continue;
                    else
                    goto EndWhile;
                    break; //optional
                default : //Optional
                    ;
                }
            }
            if (battlestate != 0) {
                goto EndWhile;
            }
        }
        EndWhile:
        return battlestate;
    }

    void print_canvas() {
        reset_output_marker();
        for (unsigned int i = 0; i < cvs.get_rows(); ++i) {
            std::cout << cvs[i];
            if(i < cvs.get_rows()-1) std::cout << std::endl << "\r";
        }
        //std::cout << ANSI_MOVE_UP;
    }

    void flush_screen(){
        reset_output_marker();
        for (unsigned int i = 0; i < TERMINAL_ROWS; ++i) {
            std::string empty(TERMINAL_COLS, ' ');
            std::cout << empty.c_str();
            if(i < TERMINAL_ROWS-1) std::cout << std::endl << "\r";
        }
        //std::cout << ANSI_MOVE_UP;
    }

    void reset_output_marker() {
        for (unsigned int i = 0; i < cvs.get_rows()-1; ++i) {
            std::cout << ANSI_MOVE_UP;
        }
        std::cout << "\r";
    }

    bool is_unbuffered() {
        if (MODE == UNBUFFERED) return true;
        return false;
    }

    void set_buffer_mode(int i) {
        if (i == 0) {
            system ("/bin/stty raw -echo");
            MODE = UNBUFFERED;
        }

        else if (i == 1) {
            system ("/bin/stty cooked echo");
            MODE = BUFFERED;
        }
    }

}
