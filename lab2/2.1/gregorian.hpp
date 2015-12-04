#ifndef GREGORIAN_HPP
#define GREGORIAN_HPP

#include <string>
#include<vector>
#include<iostream>
#include "westerndate.hpp"

namespace lab2 {

class Gregorian: public WesternDate{
    protected:
    void setup_ly_cond();
    bool leap_year()const;
    bool calculate_if_leap_year(const int year)const;

    void from_julian_day(const int mjd, int* date)const;

    public:
    Gregorian();
    Gregorian(const Date& ref);
    Gregorian(const Gregorian& ref);
    explicit Gregorian(const int mjd);
    explicit Gregorian(const int yr_in, const int mth_in, const int dy_in);

    int mod_julian_day()const;
    Gregorian& operator ++ ();
    Gregorian& operator -- ();
    Gregorian operator ++ (int);
    Gregorian operator -- (int);

    std::string ical_type()const;
};

}


#endif
