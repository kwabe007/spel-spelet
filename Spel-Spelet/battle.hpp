#ifndef BATTLE_HPP
#define BATTLE_HPP
#include <vector>
#include "entities/entity.hpp"
#include "menus/menu.hpp"

class Battle {
private:
    std::vector<Entity*> main_party;
    std::vector<Entity*> enemy_party;
    Entity current_entity;
    //Menu party_menu;
    Menu enemy_menu;
    Menu* current_menu_ptr;

public:
    Battle(Entity& enemy);

    bool attack(Entity& target);
    bool attack(Entity& attacker, Entity& target);

    Entity& get_party_entity(std::size_t index);
    const Entity& get_party_entity(std::size_t index) const;
    Entity& get_enemy_entity(std::size_t index);
    const Entity& get_enemy_entity(std::size_t index) const;

    const Menu& current_menu()const;

};

#endif
