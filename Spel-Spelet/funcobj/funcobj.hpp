#ifndef FUNCOBJ_HPP
#define FUNCOBJ_HPP

#include <cstdlib>
#include "../items/item.hpp"

enum FunctionType {
    FUNCTION_INTEGRAL,
    FUNCTION_EXIT,
    FUNCTION_NONE,
};

class FunctionObject {
private:
    FunctionType type = FUNCTION_NONE;
    std::size_t* init_value_ptr = nullptr;
    std::size_t value_to_set = 0;
    Item* item_ptr = nullptr;

public:
    FunctionObject();
    FunctionObject(Item* it_ptr);
    FunctionObject(FunctionType t);
    FunctionObject(std::size_t* to_change, std::size_t val_set);

    void set_integral() const;
    static void exit();
    void operator()() const;


};

#endif
