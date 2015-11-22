#ifndef FUNCOBJ_HPP
#define FUNCOBJ_HPP

#include <cstdlib>

enum FunctionType {
    FUNCTION_INTEGRAL,
    FUNCTION_EXIT,
    FUNCTION_NONE,
};

class FunctionObject {
private:
    FunctionType type = FUNCTION_INTEGRAL;
    std::size_t* init_value_ptr = nullptr;
    std::size_t value_to_set = 0;

public:
    FunctionObject();
    FunctionObject(FunctionType t);
    FunctionObject(std::size_t* to_change, std::size_t val_set);

    void set_integral();
    static void exit();
    void operator()();


};

#endif
