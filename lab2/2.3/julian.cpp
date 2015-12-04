#include <string>
#include<vector>
#include<iostream>
#include "julian.hpp"
#include<stdexcept>

namespace lab2 {

Julian::Julian() : WesternDate() {
    from_julian_day(mjd_create, date);
    yr = date[0];
    mth = date[1]-1;
    dy = date[2]-1;
    setup_ly_cond();
}
Julian::Julian(const int mjd){
    if (mjd < -101127 || mjd >416755) {
        throw std::invalid_argument("Out of range!");
    }
    from_julian_day(mjd, date);
    yr = date[0];
    mth = date[1]-1;
    dy = date[2]-1;
    setup_ly_cond();
}
Julian::Julian(const int yr_in, const int mth_in, const int dy_in) : WesternDate(yr_in,mth_in,dy_in) {
    setup_ly_cond();
    if (0 >= mth_in || mth_in > mpy || 0 >= dy_in || dy_in > current_dpm()) {
        throw std::invalid_argument ("Out of range");
    }
}
Julian::Julian(const Date& ref) : WesternDate(ref) {
    from_julian_day(mjd_create, date);
    yr = date[0];
    mth = date[1]-1;
    dy = date[2]-1;
    setup_ly_cond();
}
Julian::Julian(const Date* ref_ptr) : WesternDate(ref_ptr) {
    from_julian_day(mjd_create, date);
    yr = date[0];
    mth = date[1]-1;
    dy = date[2]-1;
    setup_ly_cond();
}
Julian::Julian(const WesternDate& ref) : WesternDate(ref) {
    from_julian_day(mjd_create, date);
    yr = date[0];
    mth = date[1]-1;
    dy = date[2]-1;
    setup_ly_cond();
}
Julian::Julian(const Julian& ref) : WesternDate(ref) {
    from_julian_day(mjd_create, date);
    yr = date[0];
    mth = date[1]-1;
    dy = date[2]-1;
    setup_ly_cond();
}

void Julian::setup_ly_cond() {
}
Julian& Julian::operator ++ () {
    add_d();
    return *this;
}
Julian Julian::operator ++ (int) {
    Julian temp(*this);
    add_d();
    return temp;
}
Julian& Julian::operator -- () {
    rem_d();
    return *this;
}
Julian Julian::operator -- (int) {
    Julian temp(*this);
    rem_d();
    return temp;
}
int Julian::mod_julian_day() const {
    // http://quasar.as.utexas.edu/BillInfo/JulianDatesG.html
    int year = yr;
    int month = mth + 1;
    int day = dy + 1;
    if (month <= 2) {
        month += 12;
        --year;
    }
    int d = 365.25*(year+4716);
    int e = 30.6001*(month+1);
    int mjd = day + d + e - 1524.5 - 2400000.5;
    return mjd;
}

void Julian::from_julian_day(const int mjd, int* date)const {
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

bool Julian::leap_year() const {
    if (yr % 4 == 0) {
        return true;
    } else {
        return false;
    }
}

bool Julian::calculate_if_leap_year(const int year) const {
    if (year % 4 == 0) {
        return true;
    } else {
        return false;
    }
}

std::string Julian::ical_type()const {
    return "JULIAN";
}

}
