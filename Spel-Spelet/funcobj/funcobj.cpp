#include "funcobj.hpp"
#include "../ui.hpp"

FunctionObject::FunctionObject() {

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
    if (type == FUNCTION_NONE) return;
    if (type == FUNCTION_EXIT) exit();
    if (type == FUNCTION_INTEGRAL) set_integral();
}


