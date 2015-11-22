#ifndef BATTLE_HPP
#define BATTLE_HPP
#include <vector>
#include "entities/human.hpp"
#include "menus/menu.hpp"


enum BattleState {
    ENEMY_TURN,
    PARTY_TURN,
};

class Battle {
private:

    std::vector<Entity*> main_party;
    std::vector<Entity*> enemy_party;
    Entity* current_entity = &PLAYER;
    Entity* current_enemy;
    Menu select_enemy_menu;
    Menu* current_menu=&select_enemy_menu;
    std::size_t selected_enemy_index = 0;
    std::size_t enemies_alive;
    std::size_t selected_party_index = 0;
    std::size_t party_members_alive;
    bool victory = false;

public:
    BattleState turn = PARTY_TURN;
    Battle(Entity& enemy);

    bool attack(Entity& target);
    bool attack(Entity& attacker, Entity& target);
    int action();
    bool party_action();
    bool enemy_action();

    void back_to_main_menu();

    Entity& get_party_entity(std::size_t index);
    const Entity& get_party_entity(std::size_t index) const;
    Entity& get_enemy_entity(std::size_t index);
    const Entity& get_enemy_entity(std::size_t index) const;
    Menu& get_current_menu();
    const Menu& get_current_menu() const;


};

#endif
