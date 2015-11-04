#include <string>
#include<vector>
#include<iostream>
#include "julian.hpp"
#include<stdexcept>

namespace lab2 {

lab2::Julian::Julian() : WesternDate() {
    from_julian_day(mjd_create, date);
    yr = date[0];
    mth = date[1]-1;
    dy = date[2]-1;
    setup_ly_cond();
}
lab2::Julian::Julian(const int mjd){
    if (mjd < -101127 || mjd >416755) {
        throw std::out_of_range("Out of range!");
    }
    from_julian_day(mjd, date);
    yr = date[0];
    mth = date[1]-1;
    dy = date[2]-1;
    setup_ly_cond();
}
lab2::Julian::Julian(const int yr_in, const int mth_in, const int dy_in) : WesternDate(yr_in,mth_in,dy_in) {
    setup_ly_cond();
    if (0 >= mth_in || mth_in > mpy || 0 >= dy_in || dy_in > current_dpm) {
        throw std::out_of_range ("Out of range");
    }
}
lab2::Julian::Julian(const Date& ref) : WesternDate(ref) {
    from_julian_day(mjd_create, date);
    yr = date[0];
    mth = date[1]-1;
    dy = date[2]-1;
    setup_ly_cond();
}
lab2::Julian::Julian(const Date* ref_ptr) : WesternDate(ref_ptr) {
    from_julian_day(mjd_create, date);
    yr = date[0];
    mth = date[1]-1;
    dy = date[2]-1;
    setup_ly_cond();
}
lab2::Julian::Julian(const WesternDate& ref) : WesternDate(ref) {
    //std::cerr << "mod " << mjd_create << " ";
    from_julian_day(mjd_create, date);
    yr = date[0];
    mth = date[1]-1;
    dy = date[2]-1;
    //std::cerr << yr << " " << mth << " " << dy << std::endl;
    setup_ly_cond();
}
lab2::Julian::Julian(const Julian& ref) : WesternDate(ref) {
    from_julian_day(mjd_create, date);
    yr = date[0];
    mth = date[1]-1;
    dy = date[2]-1;
    setup_ly_cond();
}
lab2::Julian::~Julian(){
    delete[] months;
}
void lab2::Julian::setup_ly_cond() {
    leap_year = is_leap_year(yr);
    months[ly_month] = ly_default+leap_year;
    current_dpm = *(months + mth);
    //std::cerr << yr << " " << mth << " " << dy << std::endl;
}
Julian& lab2::Julian::operator ++ () {
    add_d();
    return *this;
}
Julian lab2::Julian::operator ++ (int) {
    Julian temp(*this);
    add_d();
    return temp;
}
Julian& lab2::Julian::operator -- () {
    rem_d();
    return *this;
}
Julian lab2::Julian::operator -- (int) {
    Julian temp(*this);
    rem_d();
    return temp;
}
int lab2::Julian::mod_julian_day() const {
    // http://quasar.as.utexas.edu/BillInfo/JulianDatesG.html
    int year = yr;
    int month = mth + 1;
    int day = dy + 1;
    if (mth <= 2) {
        month = mth + 12;
        --year;
    }
    int d = 365.25*(year+4716);
    int e = 30.6001*(month+1);
    int mjd = day + d + e - 1524.5 - 2400000.5;
    return mjd;
}

void lab2::Julian::from_julian_day(const int mjd, int* date)const {
    int Q = mjd + 2400000.5 + 0.5;
    int Z = (int)Q;
    int A = Z;
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
bool lab2::Julian::is_leap_year(const int year) const {
    if (year % 4 == 0) {
        return true;
    } else {
        return false;
    }
}

}
