#ifndef MENU_HPP
#define MENU_HPP

#include <string>
#include <array>
#include <vector>
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

/* Contains choices for the user connected
 * to functions.
 * */

enum MenuFlow {
    FLOW_FORWARD,
    FLOW_BACK,
    FLOW_STAY
};

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
        MenuFlow flow = FLOW_FORWARD;
        Menu* nextmenu = nullptr;

        friend Menu;

        public:
        MenuItem(){}
        MenuItem(const std::string& name, const std::string& desc, MenuFlow fl = FLOW_FORWARD,
                 FunctionType f_type = FUNCTION_NONE, std::size_t* init_val = nullptr, std::size_t set_val = 0,
                 Menu* submenu = nullptr) {
            switch (f_type) {
            case FUNCTION_INTEGRAL:
                functionobject = FunctionObject(init_val,set_val);
                break;
            default:
                functionobject = FunctionObject(f_type);
            }

            repr_strings[0] = name;
            repr_strings[1] = desc;
            flow = fl;
            nextmenu = submenu;
        }

        std::string get_name() const {
            return repr_strings[0];
        }
        std::string get_desc() const {
        return repr_strings[1];
        }

    };

    private:
    mutable std::size_t selected_item = 0;
    std::vector<MenuItem> items;
    std::string name = "none";
    std::string description = "nondescript";

    public:

    Menu();
    Menu(const std::string nm);
    Menu(const Menu& ref)=delete;

    ~Menu();

    Menu& operator=(const Menu& ref);
    std::string operator[](std::size_t index)const;

    int add_item(const std::string& name, const std::string& desc, Menu& submenu);
    int add_item(const std::string& name, const std::string& desc, MenuFlow flow = FLOW_FORWARD,
                 FunctionType f_type = FUNCTION_NONE, std::size_t* init_val = nullptr, std::size_t set_val = 0,
                 Menu* submenu = nullptr);

    int add_back();

    void clear();
    bool move_up() const;
    bool move_down() const;

    std::string get_name() const;
    std::string get_desc() const;
    void run_function();
    void run_function() const;
    size_t get_size() const;
    bool is_selected(std::size_t index) const;
    std::size_t get_selected() const;
    MenuFlow get_flow_of_selected() const;
    Menu& get_menu_of_selected();
    const Menu& get_menu_of_selected() const;
    std::string get_description_of_selected() const;
    bool selected_has_menu() const;

    void fill_matrix(std::string** matrix) const;

};


#endif
