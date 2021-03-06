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
		for (it = out_text.begin(); it != out_text.end(); ++it) {
			std::cout << *it;
			sleep(time);
		}
        std::cout << std::endl << "\r";
	}

    SceneFlow play_scene(Scene& scene) {
        debug_println(BIT0,"Playing scene");
        SceneFlow flow = SCENE_FLOW_NORMAL;
        if(scene.is_set_text()) show_text(scene.get_text());
        if(scene.is_set_menu()) present_menu(scene.get_menu());
        if(scene.is_set_world()) {
            bool cont = play_world(scene.get_world());
            if(!cont) flow = SCENE_FLOW_STOP;
        }
        return flow;
    }

    void show_text(const Text& text) {
        flush_and_clear();
        char choice;
        while (true) {
            cvs.apply_text(text);
            print_canvas();
            choice = get_char();
            switch(choice){
            case COMMAND_ENTER:
            case COMMAND_SPACE:
                goto EndWhile;
            default:
                ;
            }
        }
        EndWhile:
        ;
    }

    void entity_status(const Entity& ent) {
        flush_and_clear();
        char choice;
        while (true) {
            cvs.apply_entity_status(ent);
            print_canvas();
            choice = get_char();
            switch(choice){
            case COMMAND_ENTER:
            case COMMAND_SPACE:
                goto EndWhile;
            default:
                ;
            }
        }
        EndWhile:
        ;
    }

    MenuFlow setup_game_menu() {
        MenuFlow fl = FLOW_BACK;
        while (true) {
            Menu item_menu("Items");
            debug_println(BIT5,"Player inventory size: " << PLAYER.get_inventory_size());
            for (std::size_t i = 0; i < PLAYER.get_inventory_size(); ++i) {
                Item& item = PLAYER.get_item_from_inventory(i);
                item_menu.add_item(item.get_name(),item.get_description(),item);
            }
            item_menu.add_back();
            Menu game_menu ("Game Menu");
            game_menu.add_item("Resume game","Resume the game",FLOW_BACK);
            game_menu.add_item("Status","Status",FLOW_FORWARD);
            game_menu.add_item("Inventory","Show the items you have in your inventory",FLOW_BACK,FUNCTION_NONE,nullptr,0,&item_menu);
            game_menu.add_item("End game", "End game and go back to main menu", FLOW_END);
            present_menu(game_menu);
            fl = game_menu.get_flow_of_selected();
            if (fl == FLOW_FORWARD)
                entity_status(PLAYER);
            else
                break;
        }
        return fl;
    }

    void present_menu(const Menu& menu, bool sub) {
        char choice;
        while (true) {
            flush_and_clear();
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
                        if (next_menu.get_flow_of_selected() == FLOW_END)
                            goto EndWhile;
                        break;
                    }
                    goto EndWhile;
                }
            default:
                ;
            }
        }

        EndWhile:
        if (sub) {
            flush_screen();
            cvs.clear_canvas();
        }
        ;
    }

    bool play_world(World& world) {
        if (world.start_is_set()) {
            while (true) {
                Area& area = world.current_area();
                if(!play_area(area))
                    return false;
                if (world.move_current_area(area.selected_direction)) {
                    world.current_area().selected_direction = area.selected_direction;
                }
            }
        }
        return true;
    }

    bool play_area(Area& area) {

        char choice;
        while (true) {
            flush_and_clear();
            if(area.is_end()) {
                Text text("txt-won");
                show_text(text);
                return false;
            }
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
                if (area.is_path_blocked(area.selected_direction))
                    break;
                goto EndWhileArea;
                break; //optional
            case COMMAND_FIGHT: {
                Menu fightmenu("Who do you want to fight?");
                for (std::size_t i = 0; i < area.get_entity_size(); ++i) {
                    MenuFlow flow = FLOW_FORWARD;
                    Entity& entity(area.get_entity(i));
                    if (!entity.is_alive())
                        flow = FLOW_STAY;
                    fightmenu.add_item(entity.get_name(), entity.get_description(),flow);
                }
                fightmenu.add_back();
                present_menu(fightmenu, true);
                debug_println(BIT1,"Selected :" << fightmenu.get_selected() << " flow of selected: " << fightmenu.get_flow_of_selected()
                              << " flow_back: " << FLOW_BACK);
                if (fightmenu.get_flow_of_selected() == FLOW_BACK) continue;
                Entity& chosen_entity(area.get_entity(fightmenu.get_selected()));
                Battle battle(chosen_entity);
                battle_intro(battle);
                BattleOutcome outcome = play_battle(battle);
                if (outcome == BATTLE_OUTCOME_ENEMY_WIN) return false;
                break;
            }
            case COMMAND_TALK: {
                const Menu& talk_menu = area.get_talk_menu();
                present_menu(talk_menu, true);
                if (talk_menu.get_flow_of_selected() == FLOW_BACK) continue;
                Entity& chosen_entity(area.get_entity(talk_menu.get_selected()));
                show_text(Text(chosen_entity.get_what_to_say(),""));
                break;
            }
            case COMMAND_PAUSE: {
                //const Menu& game_menu = area.get_game_menu();
                if (setup_game_menu() == FLOW_END) return false;
                break;
            }
            default : //Optional
                ;
            }
        }
    EndWhileArea:
    return true;
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

    BattleOutcome play_battle(Battle& battle) {
        flush_and_clear();
        char choice;
        Menu& current_menu = battle.get_current_menu();
        BattleOutcome outcome = BATTLE_OUTCOME_UNDECIDED;

        while (true) {
            cvs.apply_battle_fight(battle);
            print_canvas();

            choice = get_char();
            if (battle.turn == ENEMY_TURN) {
                switch(choice){
                case COMMAND_ENTER:
                case COMMAND_SPACE:
                    outcome = battle.enemy_action();
                    break;
                }
            } else if (battle.turn == PARTY_TURN) {
                switch(choice){
                case COMMAND_ENTER:
                case COMMAND_SPACE:
                    current_menu.run_function();
                    battle.back_to_main_menu();
                    outcome = battle.party_action();
                    break;
                default : //Optional
                    ;
                }
            }
            cvs.apply_battle_action(battle);
            if (outcome != BATTLE_OUTCOME_UNDECIDED) {
                std::string outcome_str;
                cvs.apply_battle_fight(battle);
                print_canvas();
                get_char();
                switch (outcome) {
                case BATTLE_OUTCOME_ENEMY_WIN:
                    outcome_str = UI::TEXT_PARTY_DEFEAT;
                    break;
                case BATTLE_OUTCOME_PARTY_WIN:
                    outcome_str = UI::TEXT_ENEMY_DEFEAT + " " + battle.get_enemy_entity(0).get_name();
                    break;
                default:
                    outcome_str = UI::TEXT_NONE_DEFEAT;
                    break;
                }
                Text outcome_text(outcome_str, "");
                show_text(outcome_text);
                goto EndWhile;
            }
        }
        EndWhile:
        return outcome;
    }

    void print_canvas() {
        reset_output_marker();
        for (unsigned int i = 0; i < cvs.get_rows(); ++i) {
            std::cout << cvs[i];
            if(i < cvs.get_rows()-1) std::cout << std::endl << "\r";
        }
    }

    void flush_screen(){
        reset_output_marker();
        for (unsigned int i = 0; i < TERMINAL_ROWS; ++i) {
            std::string empty(TERMINAL_COLS, ' ');
            std::cout << empty.c_str();
            if(i < TERMINAL_ROWS-1) std::cout << std::endl << "\r";
        }
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
            debug_print(BIT0,"Setting buffer mode to raw...");
            system ("/bin/stty raw -echo");
            MODE = UNBUFFERED;
            debug_println(BIT0," buffer mode set to raw");
        }

        else if (i == 1) {
            debug_print(BIT0,"Setting buffer mode to buffered...");
            system ("/bin/stty cooked echo");
            MODE = BUFFERED;
            debug_println(BIT0," buffer mode set to buffered");
        }
    }


}
