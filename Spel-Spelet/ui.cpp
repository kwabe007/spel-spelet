#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <unistd.h>
#include "ui.hpp"
#include "parse.hpp"
#include "canvas.hpp"
#include "scene.hpp"
#include "debug/debugmacro.h"
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
        debug_print(BIT0,"Pressed key: " << (int)input << std::endl);
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
        if(scene.is_set_menu()) present_menu(scene.get_menu());
        if(scene.is_set_world()) {play_world(scene.get_world());}

        return &scene;
    }

    void present_prologue(const std::string& text) {
    }

    void present_menu(const Menu& menu, bool sub) {
        flush_screen();
        cvs.clear_canvas();
        char choice;
        while (true) {
            cvs.apply_menu(menu);
            print_canvas();
            choice = get_char();
            switch(choice){
            case COMMAND_UP:
                menu.move_up();
                break; //optional
            case COMMAND_DOWN:
                menu.move_down();
                break; //optional
            case COMMAND_ENTER:
            case COMMAND_SPACE:
                menu.run_function();
                switch (menu.get_flow_of_selected()) {
                case FLOW_STAY:
                    continue;
                    break;
                default:
                    if (menu.selected_has_menu()) {
                        const Menu& next_menu = menu.get_menu_of_selected();
                        present_menu(next_menu);
                    }
                    goto EndWhile;
                }
            default:
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

    void play_world(World& world) {

        if (world.start_is_set()) {
            while (true) {
                Area& area = world.current_area();
                play_area(area);
                if (world.move_current_area(area.selected_direction)) {
                    world.current_area().selected_direction = area.selected_direction;
                }
            }
        }
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
                Menu fightmenu("Who do you want to fight?");
                for (std::size_t i = 0; i < area.get_entity_size(); ++i) {
                    Entity& entity(area.get_entity(i));
                    fightmenu.add_item(entity.get_name(), entity.get_description());
                }
                fightmenu.add_item("Go Back", "Return", FLOW_BACK);
                //fightmenu.add_back();
                present_menu(fightmenu, true);
                if (fightmenu.get_flow_of_selected() == FLOW_BACK){
                    flush_and_clear();
                    continue;
                }
                //extern Entity PLAYER;
                Entity& chosen_entity(area.get_entity(fightmenu.get_selected()));
                Battle battle(chosen_entity);
                battle_intro(battle);
                int outcome = play_battle(battle);
                if (outcome == -1) {
                }
                if (outcome == 1) {
                }
                flush_screen();
                cvs.clear_canvas();
                break;
            }
                break;

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
        Menu& current_menu = battle.get_current_menu();
        int battlestate = 0;

        while (true) {
            cvs.apply_battle_fight(battle);
            print_canvas();
            sleep(1000);
            if (battle.turn == ENEMY_TURN) {
                battlestate = battle.enemy_action();
                cvs.apply_battle_fight(battle);
                print_canvas();
            } else if (battle.turn == PARTY_TURN) {
                choice = get_char();
                switch(choice){
                case COMMAND_ENTER:
                case COMMAND_SPACE:
                    current_menu.run_function();
                    battle.back_to_main_menu();
                    battlestate = battle.party_action();
                    break;
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

    void flush_and_clear() {
        flush_screen();
        cvs.clear_canvas();
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
