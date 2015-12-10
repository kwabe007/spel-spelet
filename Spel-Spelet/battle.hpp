#ifndef BATTLE_HPP
#define BATTLE_HPP
#include <vector>
#include <utility>
#include <string>
#include "entities/human.hpp"
#include "menus/menu.hpp"


enum BattleOutcome {
    BATTLE_OUTCOME_UNDECIDED,
    BATTLE_OUTCOME_PARTY_WIN,
    BATTLE_OUTCOME_ENEMY_WIN
};

enum BattleState {
    ENEMY_TURN,
    PARTY_TURN,
};

class Battle {
private:

    std::vector<Entity*> main_party;
    std::vector<Entity*> enemy_party;
    std::size_t party_turn_index = 0;
    std::size_t enemy_turn_index = 0;
    Menu select_enemy_menu;
    Menu* current_menu=&select_enemy_menu;
    std::size_t target_enemy_index = 0;
    std::size_t target_party_index = 0;
    bool victory = false;
    std::string latest_action;
    Entity& get_current_party();
    const Entity& get_current_party() const;
    Entity& get_current_enemy();
    const Entity& get_current_enemy() const;
    Entity& get_target_party();
    const Entity& get_target_party() const;
    Entity& get_target_enemy();
    const Entity& get_target_enemy() const;
    void switch_turn();
    enum ActionType {
        ACTION_TYPE_ATTACK
    };
    void set_latest_action(const Entity& subject,ActionType type, const Entity& object, std::pair<bool, int> stats);

public:
    BattleState turn = PARTY_TURN;
    Battle(Entity& enemy);

    std::pair<bool, int> attack(Entity& attacker, Entity& target);
    BattleOutcome party_action();
    BattleOutcome enemy_action();
    std::size_t partymems_alive() const;
    std::size_t enemies_alive() const;

    void back_to_main_menu();

    Entity& get_party_entity(std::size_t index);
    const Entity& get_party_entity(std::size_t index) const;
    Entity& get_enemy_entity(std::size_t index);
    const Entity& get_enemy_entity(std::size_t index) const;
    Menu& get_current_menu();
    const Menu& get_current_menu() const;
    std::string get_last_action() const;
    Entity& get_current_entity();
    const Entity& get_current_entity() const;


};

#endif
