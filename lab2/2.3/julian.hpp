#ifndef JULIAN_HPP
#define JULIAN_HPP

#include <string>
#include <vector>
#include <iostream>
#include "westerndate.hpp"

namespace lab2 {

class Julian: public WesternDate{
    private:
        void initialize();
        bool is_leap_year(const int year)const;
        void setup_ly_cond();
        int mod_julian_day()const;
        void from_julian_day(const int mjd, int* date)const;

    public:
        Julian();
        Julian(const Date& ref);
        Julian(const Date* ref_ptr);
        Julian(const Julian& ref);
        Julian(const WesternDate& ref);
        explicit Julian(const int mjd);
        explicit Julian(const int yr_in, const int mth_in, const int dy_in);

        ~Julian();

        Julian& operator ++ ();
        Julian& operator -- ();
        Julian operator ++ (int);
        Julian operator -- (int);

};

}



#endif
