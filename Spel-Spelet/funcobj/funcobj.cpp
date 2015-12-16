#include "funcobj.hpp"
#include "../ui.hpp"
#include "../debug/debugmacro.h"

FunctionObject::FunctionObject() {

}

FunctionObject::FunctionObject(Item* it_ptr) {
    item_ptr = it_ptr;
    debug_println(BIT0, "item ptr set to funcobj");
}

FunctionObject::FunctionObject(FunctionType t) {
    type = t;
}

FunctionObject::FunctionObject(std::size_t* to_change, std::size_t val_set) : init_value_ptr{to_change}, value_to_set{val_set} {

}

void FunctionObject::set_integral() const {

    *init_value_ptr = value_to_set;
}

void FunctionObject::exit() {
    if (UI::is_unbuffered()) {
        UI::set_buffer_mode(1);
    }
    std::exit(EXIT_SUCCESS);
}

void FunctionObject::operator()() const {
    if (item_ptr) {
        debug_println(BIT0, "doing item action");
        item_ptr->action();
    }
    if (type == FUNCTION_NONE) return;
    if (type == FUNCTION_EXIT) exit();
    if (type == FUNCTION_INTEGRAL) set_integral();
}


