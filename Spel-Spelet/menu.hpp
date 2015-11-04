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
        public:
        MenuItem(){}
        MenuItem(const std::string name, const std::string desc,  void (*const fp )(Menu*)){
            repr_strings[0] = name;
            repr_strings[1] = desc;
            fp_choice = fp;
        }


        private:
        std::string repr_strings[ITEM_REPR_STR_COUNT];

        void (*fp_choice)(Menu*);
        friend Menu;

    };

    public:
    Menu();
    Menu(const std::string nm, size_t n);
    ~Menu();

    int add_item(const std::string name, const std::string desc, void (*const fp)(Menu*));
    int clear();

    std::string get_name() const;
    std::string get_desc() const;
    Func_Ptr get_fp(int index) const;
    size_t get_size() const;

    void fill_matrix(std::string** matrix) const;




    private:
    size_t size;
    size_t capacity;
    MenuItem * items;
    std::string name;
    std::string description;



};


#endif
