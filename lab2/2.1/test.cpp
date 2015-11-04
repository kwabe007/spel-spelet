#include <iostream>
#include <typeinfo>
#include <vector>
#include "julian.hpp"
#include "gregorian.hpp"
#include <cassert>
#include "kattistime.h"
#include<stdexcept>

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

    cout << "*******************TEST STARTED*******************\n";



    Gregorian greg_today;
    Julian juli_today;

    cout << "Good evening ladies and gentlemen, today's date is as following\n"
            << greg_today << " Using the undisputable Gregorian calendar.\n"
            << juli_today << " Using the slightly outdated Julian calendar.\n";

    int t_y = 2144;
    assert(t_y>=1582); //MAKE SURE YEAR IS AT LEAST 1582
    int t_m = 7;
    int t_d = 7;

    Gregorian greg(t_y,t_m,t_d);
    Julian cyka(t_y,t_m,t_d);
    Gregorian year_test(2004,2,29);

    int dpm = cyka.days_this_month();
    int mpy = cyka.months_per_year();
    int dpw = cyka.days_per_week();

    cout << "Printing cyka: "<< year_test << endl;

    try{
        Gregorian good_date(-333332);
    } catch (const std::out_of_range& oor) {
        std::cerr << "error was caught but shouldn't have: " << oor.what() << '\n';
    }

    /*try{
        Julian dumb_date2(2005,33,1);;
    } catch (const std::out_of_range& oor) {
        std::cerr << "error caught successfully: " << oor.what() << '\n';
    }*/
    try{
        Julian good_date(2100,2,29);
    } catch (const std::out_of_range& oor) {
        std::cerr << "error was caught but shouldn't have: " << oor.what() << '\n';
    }
    try{
        Gregorian dumb_date3(2100,2,29);
    } catch (const std::out_of_range& oor) {
        std::cerr << "error caught successfully: " << oor.what() << '\n';
    }

    cout << "divider "<< 15/-2 << endl;
    cout << "modulo: "<< 15%2 << endl;

    year_test.add_year(4);
    cout << "Printing test: "<< year_test << endl;
    assert(year_test.day() == 29);

    Gregorian year_test_copy = year_test++;
    year_test--;
    year_test_copy++;
    year_test_copy--;

    cout << "Printing test: "<< year_test << endl;
    cout << "Printing test_copy: "<< year_test_copy << endl;

    assert(year_test == year_test_copy);

    cout << "Printing test: "<< year_test << endl;
    assert(year_test.day() == 29);
    year_test.add_year(-2);
    cout << "Printing test: "<< year_test << endl;
    year_test.add_year(-2);
    cout << "Printing test: "<< year_test << endl;
    assert(year_test.day() == 28);

    Gregorian test_month(2000,9,1);
    Gregorian test_month2(2000,7,17);
    Gregorian test_month3(2005,1,31);

    assert(test_month.week_day() == 5);
    cout << "Printing test_month week_day_name " << test_month.week_day_name() << std::endl;
    assert(test_month.week_day_name() == "friday");

    assert(test_month2.week_day() == 1);
    assert(test_month2.week_day_name() == "monday");

    assert(test_month3.week_day() == 1);
    assert(test_month3.week_day_name() == "monday");

    test_month.add_month(1);
    test_month2.add_month(-1);
    test_month3.add_month(3);

    assert(test_month.month() == 10);
    assert(test_month.month_name() == "october");
    assert(test_month.day() == 1);

    assert(test_month2.month() == 6);
    assert(test_month2.month_name() == "june");
    assert(test_month2.day() == 17);

    assert(test_month3.month() == 5);
    assert(test_month3.month_name() == "may");
    assert(test_month3.day() == 2);


    cout << "Printing dpm: "<< dpm << endl;
    cout << "Printing mpy: "<< mpy << endl;
    cout << "Printing dpw: "<< dpw << endl;

    assert(dpm == 31);
    assert(mpy == 12);
    assert(dpw == 7);

    Julian testjul(53948);
    cout << testjul << " TEST JUL\n";

    int mjd_greg = 104327;
    int mjd_cyka = 104341;

    cout << "Printing greg: "<< greg << endl;
    cout << "Printing mjd: "<< mjd_greg << endl;

    assert(mjd_greg == 104327);
    assert(mjd_cyka == 104341);

    Gregorian greg_copy(mjd_greg);
    Gregorian greg_copy2(greg_copy);
    Julian cyka_copy(mjd_cyka);
    cout << "cyka_copy created!" << endl;
    Julian cyka_copy2(cyka_copy);

    cout << "Printing greg_copy: "<< greg_copy << endl;
    cout << "Printing cyka_copy: "<< cyka_copy << endl;
    cout << "Printing greg_copy2: "<< greg_copy2 << endl;
    cout << "Printing cyka_copy2: "<< cyka_copy2 << endl;

    Gregorian greg_copy3(greg_copy2);
    Julian cyka_copy3(greg_copy3);

    cout << "Printing greg_copy3: "<< greg_copy3 << endl;
    cout << "Printing cyka_copy3: "<< cyka_copy3 << endl;

    assert (greg_copy3 == cyka_copy3);

    assert(greg_copy==greg);
    assert(cyka_copy==cyka);
    assert(greg_copy2==greg);
    assert(cyka_copy2==cyka_copy);

    ++greg_copy;
    ++cyka_copy2;

    assert(greg_copy!=greg);
    assert(cyka_copy==cyka);
    assert(greg_copy2==greg);
    assert(cyka_copy2!=cyka_copy);

    int dif = cyka-greg;
    int sum = cyka+greg;
    cout << "dif: "<< dif << endl;
    assert(dif == 14);
    assert(sum == 208668);

    assert(greg != cyka);

    greg_copy3 = cyka_copy2;
    Gregorian RonnieColeman = greg_copy3;
    greg_copy2 = greg_copy3;

    cout << "RonnieColeman "<< RonnieColeman << endl;
    cout << "Printing greg_copy3: "<< greg_copy3 << endl;
    cout << "Printing cyka_copy2: "<< cyka_copy2 << endl;
    cout << "Printing greg_copy2: "<< greg_copy2 << endl;

    assert(greg_copy3 == RonnieColeman);
    assert(greg_copy3 == cyka_copy2);
    assert(greg_copy2 == cyka_copy2);

    greg_copy3.add_month(4);
    greg_copy2.add_month(-1);

    cout << "RonnieColeman "<< RonnieColeman << endl;
    cout << "Printing greg_copy3: "<< greg_copy3 << endl;
    cout << "Printing cyka_copy2: "<< cyka_copy2 << endl;
    cout << "Printing greg_copy2: "<< greg_copy2 << endl;

    assert(greg_copy3 != RonnieColeman);
    assert(greg_copy3 != cyka_copy2);
    assert(greg_copy2 != cyka_copy2);


    cout << "*******************TEST FINISHED*******************\n";
}
