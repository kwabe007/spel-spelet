#ifndef MENU_HPP
#define MENU_HPP

#include <string>

//Forward declaration of Menu for use in typedef.
class Menu;

//typedef for the function pointers.
typedef void (*Func_Ptr)(Menu*);

//Define number of string member variables in class MenuItem that have
//a representative purpose.
static const int ITEM_REPR_STR_COUNT = 2;

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
        void (*fp_choice)(Menu*);

        friend Menu;

        public:
        MenuItem(){}
        MenuItem(const std::string name, const std::string desc,  void (*const fp )(Menu*)){
            repr_strings[0] = name;
            repr_strings[1] = desc;
            fp_choice = fp;
        }
        std::string get_name() const {
            return repr_strings[0];
        }
        std::string get_desc() const {
        return repr_strings[1];
        }

    };

    private:
    std::size_t size;
    std::size_t capacity;
    mutable std::size_t selected_item = 0;
    MenuItem * items;

    std::string name;
    std::string description;

    public:

    Menu();
    Menu(const std::string nm, size_t n);
    ~Menu();

    std::string& operator[](int index)const;

    int add_item(const std::string name, const std::string desc, void (*const fp)(Menu*));
    int clear();
    bool move_up() const;
    bool move_down() const;

    std::string get_name() const;
    std::string get_desc() const;
    Func_Ptr get_fp(int index) const;
    size_t get_size() const;
    bool is_selected(std::size_t index)const;
    std::size_t get_selected()const;

    void fill_matrix(std::string** matrix) const;

};


#endif
