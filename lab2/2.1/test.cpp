#include <iostream>
#include <typeinfo>
#include <vector>
#include "julian.hpp"
#include "gregorian.hpp"
#include <cassert>
#include "kattistime.h"
#include <stdexcept>

using namespace std;
using namespace lab2;

void print500dates (Date& date) {
    for (int i = 0; i < 900; ++i) {
        cout << --date << endl;
    }
}

int main() {
// NOTE: DUE TO THE ALGORITM LACKING SICK GAINZ, IT IS NOT ACCURATE FOR YEARS EARLIER THAN 1582

    /* TODO:

    */
    //set_k_time(mytime);
    //cout << "The current date is: " << mytime << endl;

    time_t tp;
    time(&tp);
    set_k_time(tp);
    cout << "*******************TEST STARTED*******************\n";

    Gregorian greg_today;
    Julian juli_today;

    cout << "Good evening ladies and gentlemen, today's date is as following\n"
            << greg_today << " Using the undisputable Gregorian calendar.\n"
            << juli_today << " Using the slightly outdated Julian calendar.\n";

    int t_y = 2144;
    assert(t_y>=1582); //MAKE SURE YEAR IS AT LEAST 1582
    Gregorian new_date(2134,2,22);
    cout << "Standard: " << new_date << endl;
    new_date.add_month(-15);
    cout << "+(-15)m: " << new_date << endl;
    cout << new_date << " " << new_date.mod_julian_day() << endl;
    assert(new_date.mod_julian_day() == 102914);




    cout << "*******************TEST FINISHED*******************\n";
}
