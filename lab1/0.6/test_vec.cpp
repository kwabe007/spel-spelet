#include <iostream>
#include <stdexcept>
#include "kth_cprog_simple_container.hpp"     // inkludera din headerfil h�r


int main()
{
    // N�gra saker som ska fungera:
    UIntVector a(7);           // initiering med 7 element
    UIntVector b(a);           // kopieringskonstruktor
    UIntVector c = a;          // kopieringskonstruktor
    UIntVector d(6);


    a = b;                 // tilldelning genom kopiering
    a[5] = 7;              // tilldelning till element

    const UIntVector e(10);    // konstant objekt med 10 element
    int i = e[5];          // const int oper[](int) const k�rs
    i = a[0];              // vektorn �r nollindexerad
    i = a[5];              // int oper[](int) k�rs
    
    a[5]++;                // �ka v�rdet till 8

    try {
        i = e[10];             // f�rs�ker h�mta element som ligger utanf�r e
    } catch (std::out_of_range e) {
        std::cout << e.what() << std::endl;
    }
    
    // Diverse saker att testa
    e[5] = 3;              // fel: (kompilerar ej) tilldelning till const
    b = b;                 // hmm: se till att inte minnet som skall beh�llas frig�rs

    return 0;
}
