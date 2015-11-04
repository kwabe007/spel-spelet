#include <iostream>
#include "menu.hpp"

using namespace std;

/* TODO:
 * GET STARTED WITH TEXT UI USING CARRIAGE RETURN
 * ADD AUTOMATIC REALLOCATION TO MENU
 * ADD COPY CTOR AND ASS OPERATOR TO MENU
 * ADD THROW IN MENU CLASS (GET_FP)
 * ADD NAMESPACE
 * CREATE A MATRIX CLASS
 */

void runnable1(Menu* menu) {
    cout << "BLEEARGH" << endl;
}
void runnable2(Menu* menu) {
    cout << "22222" << endl;
}
void runnable3(Menu* menu) {
    cout << "3333333" << endl;
}

string** create_str_matrix(int n, int m) {
    string** out_ptr = new string*[n];
    for (int i = 0; i < n; ++i) {
        *(out_ptr + i) = new string[m];
    }
    return out_ptr;
}

void deallocate_str_matrix(string** out_ptr, int n) {
    for (int i = 0; i < n; ++i) {
        delete[] *(out_ptr + i);
    }
    delete[] out_ptr;
}

int main(int argc, char** argv) {
    Menu mainmenu(3);

    mainmenu.add_item("option 1", "this is option 1", &runnable1);
    mainmenu.add_item("option 2", "this is option 2", &runnable2);
    mainmenu.add_item("option 3", "this is option 3", &runnable3);



    int choice;
    string** arr = create_str_matrix(3,2);
    mainmenu.fill_matrix(arr);

    cout << **arr << "  " << *((*arr) + 1)  << endl;
    cout << **(arr + 1) << "  " << *(*(arr + 1) +1)  << endl;
    cout << **(arr + 2) << "  " << *(*(arr + 2) +1)  << endl;
    cout << "choose" << endl;
    cin >> choice;
    Func_Ptr fp2 = mainmenu.get_fp(choice-1);
    (*fp2)(&mainmenu);

    deallocate_str_matrix(arr,3);




    return 0;
}
