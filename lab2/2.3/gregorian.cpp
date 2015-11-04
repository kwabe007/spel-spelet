#include <string>
#include<vector>
#include<iostream>
#include "gregorian.hpp"
#include "kattistime.h"
#include<stdexcept>

namespace lab2 {

lab2::Gregorian::Gregorian() : WesternDate() {
    from_julian_day(mjd_create, date);
    yr = date[0];
    mth = date[1]-1;
    dy = date[2]-1;
    setup_ly_cond();
}

lab2::Gregorian::Gregorian(const int yr_in, const int mth_in, const int dy_in) : WesternDate(yr_in,mth_in,dy_in) {
    setup_ly_cond();
    if (0 >= mth_in || mth_in > mpy || 0 >= dy_in || dy_in > current_dpm) {
        throw std::out_of_range ("Out of range");
    }
}

lab2::Gregorian::Gregorian(const Gregorian& ref) : WesternDate(ref){
    from_julian_day(mjd_create, date);
    yr = date[0];
    mth = date[1] - 1;
    dy = date[2] - 1;
    setup_ly_cond();
}
lab2::Gregorian::Gregorian(const Date& ref) : WesternDate(ref){
    from_julian_day(mjd_create, date);
    yr = date[0];
    mth = date[1] - 1;
    dy = date[2] - 1;
    setup_ly_cond();
}

lab2::Gregorian::Gregorian(int mjd){
    from_julian_day(mjd, date);
    yr = date[0];
    mth = date[1] - 1;
    dy = date[2] - 1;
    setup_ly_cond();
}
lab2::Gregorian::~Gregorian(){
    delete[] months;
}

void lab2::Gregorian::setup_ly_cond() {
    leap_year = is_leap_year(yr);
    months[ly_month] = ly_default+leap_year;
    current_dpm = *(months + mth);
}
Gregorian& lab2::Gregorian::operator ++ () {
    add_d();
    return *this;
}
Gregorian lab2::Gregorian::operator ++ (int) {
    Gregorian temp(*this);
    add_d();
    return temp;
}
Gregorian& lab2::Gregorian::operator -- () {
    rem_d();
    return *this;
}
Gregorian lab2::Gregorian::operator -- (int) {
    Gregorian temp(*this);
    rem_d();
    return temp;
}

int lab2::Gregorian::mod_julian_day() const {
        int year = yr;
        int month = mth+1;
        int day = dy+1;
        year+=8000;
        if(month<3) { year--; month+=12; }
        return (year*365) +(year/4) -(year/100) +(year/400) -1200820
                +(month*153+3)/5-92
                +day-1 - 2400000.5;
}

void lab2::Gregorian::from_julian_day(const int mjd, int* date)const {
    int Q = mjd + 2400000.5 + 0.5;
    int Z = (int)Q;
    int W = (Z - 1867216.25)/36524.25;
    int X = W/4;
    int A = Z+1+W-X;
    int B = A+1524;
    int C = (B-122.1)/365.25;
    int D = 365.25*C;
    int E = (B-D)/30.6001;
    int F = 30.6001*E;
    date[2]= B-D-F+(Q-Z);
    if (E >= 14){
        date[1] = E-13;
    }
    else {
        date[1] = E-1;
    }
    if (date[1] <= 2){
        date[0] = C-4715;
    }
    else {
        date[0] = C-4716;
    }
}
bool lab2::Gregorian::is_leap_year(const int year) const {
    if (year % 400 == 0) {
        return true;
    } else if (year % 100 == 0) {
        return false;
    } else {
        if (year % 4 == 0) {
            return true;
        }
    }
    return false;
}

}
