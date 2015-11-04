
#include <iostream>
#include <initializer_list>
#include "kth_cprog_simple_container.hpp"
#include <cstdio>


void printVect(UIntVector vect) {
    for(int i; i<vect.size();++i)
        std::cout << "Elem " << i << ": " << vect[i] << std::endl;
}
/*void changeInt(int const myInt) {
    ++myInt;
}*/

int main() {
    unsigned int x = 44;
    unsigned int y = 45;

    std::initializer_list<unsigned int> il = {1,2,4};
    UIntVector a(il);
    printVect(a);
    UIntVector f(a);
    f = a;
    UIntVector b(10);
    a.size();
    printVect(a);
    printVect(f);
    UIntVector c;
    //a = b;

    std::cout << f.size() << std::endl;
    //vect[2] = 222;
    //cyka[2] = 22;
    //std::cout << theInt << std::endl;
    /*for (int q;q<suppa.size();++q) {
        std::cout << "elem nr"  << q << suppa[q];
    }*/
    //changeInt(4);
    /*std::cout << theInt << std::endl;
    std::cout << "SUPPA SIZE BIATCH: " << std::endl;*/
    return 0;
}
