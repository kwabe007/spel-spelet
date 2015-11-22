#ifndef MENU_HPP
#define MENU_HPP

#include <string>
#include <array>
#include "../funcobj/funcobj.hpp"

//Forward declaration of Menu for use in typedef.
class Menu;

//typedef for the function pointers.
typedef const Menu* (*Func_Ptr)(const Menu*);

//typedef for function in Menufunction
typedef int (*action_function)();

//Define number of string member variables in class MenuItem that have
//a representative purpose.
static const int ITEM_REPR_STR_COUNT = 2;

/*class MenuAction {
private:
    const Menu* menu_to = nullptr;
    static const std::size_t CAPACITY = 3;
    std::size_t size = 0;
    action_function func_arr[CAPACITY];
    friend Menu;

public:
    MenuAction() {
    }

    MenuAction(const Menu* to) {
        menu_to = to;
    }

    bool add_function(action_function func) {
        if (size < CAPACITY) {
            func_arr[size] = func;
            ++size;
            return true;
        }
        return false;
    }

    MenuAction& operator=(const MenuAction& ref) {
        menu_to = nullptr;
        size = ref.size;
        for (std::size_t i = 0; i < size; ++i) {
            func_arr[i] = ref.func_arr[i];
        }

        return *this;
    }

    const Menu* operator()() const {
        for (std::size_t i = 0; i < size; ++i) {
            func_arr[i]();
        }
        return menu_to;
    }

    const Menu* operator()(const Menu* from) const {
        for (std::size_t i = 0; i < size; ++i) {
            func_arr[i]();
        }
        return from;
    }

    std::size_t get_size() const {
        return size;
    }

};*/


/* Contains choices for the user connected
 * to functions.
 * */



class Menu {

    /* Used in the Menu class as a representation of the
     * different choices available in said Menu.
     * name: The name of the choice.
     * description: choice description.
     * fp_choice: pointer to the function of the choice.
     * */
    class MenuItem {
        private:
        std::string repr_strings[ITEM_REPR_STR_COUNT];
        FunctionObject functionobject;
        Menu* nextmenu = nullptr;

        friend Menu;

        public:
        MenuItem(){}
        MenuItem(const std::string name, const std::string desc) : functionobject{FUNCTION_NONE} {
            repr_strings[0] = name;
            repr_strings[1] = desc;
        }
        MenuItem(const std::string name, const std::string desc, std::size_t* init_val, std::size_t set_val) : functionobject{init_val,set_val} {
            repr_strings[0] = name;
            repr_strings[1] = desc;
        }
        MenuItem(const std::string name, const std::string desc, FunctionType type) : functionobject{type} {
            repr_strings[0] = name;
            repr_strings[1] = desc;
        }
        MenuItem(const std::string name, const std::string desc, Menu& submenu) : functionobject{}{
            repr_strings[0] = name;
            repr_strings[1] = desc;
            nextmenu = &submenu;
        }
        /*MenuItem& operator=(const MenuItem& ref) {
            for (std::size_t i = 0; i < ITEM_REPR_STR_COUNT; ++i) {
                repr_strings[i] = ref.repr_strings[i];
            }
            action = ref.action;
            return *this;
        }*/
        std::string get_name() const {
            return repr_strings[0];
        }
        std::string get_desc() const {
        return repr_strings[1];
        }

    };

    private:
    std::size_t size = 0;
    std::size_t capacity = 0;
    mutable std::size_t selected_item = 0;
    MenuItem * items;
    std::string name;
    std::string description;
    //MenuAction noaction(this);
    //MenuItem none("Back","",noaction);

    public:

    Menu();
    Menu(const std::string nm, size_t n);
    Menu(const Menu& ref);

    ~Menu();

    Menu& operator=(const Menu& ref);
    std::string& operator[](std::size_t index)const;

    int add_item(const std::string name, const std::string desc);
    int add_item(const std::string name, const std::string desc, Menu& submenu);
    int add_item(const std::string name, const std::string desc, std::size_t* target_val, std::size_t set_to);
    int add_item(const std::string name, const std::string desc, FunctionType type);

    int clear();
    bool move_up() const;
    bool move_down() const;

    std::string get_name() const;
    std::string get_desc() const;
    Menu* run_function(int index) const;
    size_t get_size() const;
    size_t get_capacity() const;
    bool is_selected(std::size_t index)const;
    std::size_t get_selected()const;

    void fill_matrix(std::string** matrix) const;

};


#endif
