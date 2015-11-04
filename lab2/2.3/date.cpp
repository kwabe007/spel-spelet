#include "date.hpp"
#include<string>
#include<iostream>
#include<vector>
#include"kattistime.h"
#include<stdexcept>

namespace lab2 {

lab2::Date::Date(){
    time_t mytime;
    time(&mytime);
    struct tm *t = gmtime(&mytime);
    int year  = t->tm_year + 1900;
    int month = t->tm_mon + 1;      // månaderna och dagarna
    int day   = t->tm_mday;
    mjd_create = mjd_setup(year, month, day);
}
lab2::Date::Date(const int mjd){
    if (mjd < -101127 || mjd > 416787) {
        throw std::out_of_range ("Out of range");
    }
    mjd_create = mjd;
}
lab2::Date::Date(const int yr_in,const int mth_in,const int dy_in){
    yr = yr_in;
    mth = mth_in-1;
    dy = dy_in-1;
}
lab2::Date::Date(const Date& ref){
    //std::cout << "date " << ref.get_date() << std::endl;
    mjd_create = ref.mod_julian_day();
}
lab2::Date::Date(const Date* ref_ptr){
    mjd_create = ref_ptr->mod_julian_day();
}
lab2::Date::~Date(){}
int lab2::Date::day() const {
    return dy + 1;
}
int lab2::Date::month() const {
    return mth + 1;
}
int lab2::Date::year() const {
    return yr;
}
std::string lab2::Date::get_date() const {
    std::string out_string;
    out_string.append(std::to_string(year()) + "-");
    std::string m = std::to_string(month());
    if (m.size() == 1){
        m.insert(0,"0");
    }
    out_string.append(m + "-");
    std::string d = std::to_string(day());
    if (d.size() == 1){
        d.insert(0,"0");
    }
    out_string.append(d);
    return out_string;
}
void lab2::Date::add_d() {
    if (++dy >= current_dpm) {
        dy = 0;
        add_m();
    }
}
void lab2::Date::add_m() {
    ++mth;
    if (mth >= mpy) {
        mth = 0;
        add_y();
    }
    current_dpm = *(months + mth);
}
void lab2::Date::add_y() {
    ++yr;
    leap_year = is_leap_year(yr);
    months[ly_month] = ly_default+leap_year;
}
void lab2::Date::rem_d() {
    if (--dy < 0) {
        rem_m();
        dy = current_dpm-1;
    }
}
void lab2::Date::rem_m() {
    --mth;
    if (mth < 0) {
        mth = mpy-1;
        rem_y();
    }
    current_dpm = *(months + mth);
}
void lab2::Date::rem_y() {
    --yr;
    leap_year = is_leap_year(yr);
    months[ly_month] = ly_default+leap_year;
}
int lab2::Date::days_this_month() const {
    return current_dpm;
}
int lab2::Date::months_per_year() const {
    return mpy;
}
int lab2::Date::days_per_week() const {
    return wkds.size();
}
Date& lab2::Date::operator = (const Date& ref){
    if (this != &ref) {
        int mjd = ref.mod_julian_day();
        from_julian_day(mjd,date);
        yr = date[0];
        mth = date[1]-1;
        dy = date[2]-1;
        setup_ly_cond();
    }
    return *this;
}
int lab2::Date::operator + (const Date& ref) const {
    int sum = this->mod_julian_day() + ref.mod_julian_day();
    return sum;
}
int lab2::Date::operator - (const Date& ref) const {
    int difference = this->mod_julian_day() - ref.mod_julian_day();
    return difference;
}
Date& lab2::Date::operator ++ () {
    add_d();
    return *this;
    }
Date& lab2::Date::operator -- () {
    rem_d();
    return *this;
    }
Date& lab2::Date::operator += (const int incr){
    for (int i = 0; i < incr; ++i) {
        add_d();
    }
    return *this;
}
Date& lab2::Date::operator -= (const int decr){
    for (int i = 0; i < decr; ++i) {
        rem_d();
    }
    return *this;
}
void lab2::Date::add_year(const int incr) {
    if (is_leap_year(yr) && mth == ly_month && dy + 1 == months[mth]){
        yr+=incr;
        if (is_leap_year(yr) == false) {
            months[ly_month] = ly_default;
            current_dpm = months[mth];
            dy = current_dpm-1;
        }
    }
}
void lab2::Date::add_month(const int incr) {
    if (incr >= 0) {
        for (int i = 0; i < incr; ++i) {
            if (dy >= months[mth+1%mpy] ) {
                for (int j = 0; j < 30; ++j) {
                    add_d();
                }
            } else {
                add_m();
            }
        }
    } else {
        for (int i = 0; i < incr*(-1); ++i) {
            if (dy >= months[mth-1%mpy] ) {
                for (int j = 0; j < 30; ++j) {
                    rem_d();
                }
            } else {
                rem_m();
            }
        }
    }
}

bool lab2::Date::operator == (const Date& ref) const {
    if (this->mod_julian_day() == ref.mod_julian_day()) {
        return true;
    }
    else {
        return false;
    }
}
bool lab2::Date::operator <= (const Date& ref) const{
    if (this->mod_julian_day() <= ref.mod_julian_day()) {
        return true;
    }
    else {
        return false;
    }
}
bool lab2::Date::operator >= (const Date& ref) const {
    if (this->mod_julian_day() >= ref.mod_julian_day()) {
        return true;
    }
    else {
        return false;
    }
}
bool lab2::Date::operator > (const Date& ref) const {
    if (this->mod_julian_day() > ref.mod_julian_day()) {
        return true;
    }
    else {
        return false;
    }
}
bool lab2::Date::operator < (const Date& ref) const {
    if (this->mod_julian_day() < ref.mod_julian_day()) {
        return true;
    }
    else {
        return false;
    }
}
bool lab2::Date::operator != (const Date& ref) const {
    if (this->mod_julian_day() != ref.mod_julian_day()) {
        return true;
    }
    else {
        return false;
    }
}
int lab2::Date::mjd_setup(const int y,const int m, const int d){
        int year = y;
        int month = m;
        int day = d;
        year+=8000;
        if(month<3) { year--; month+=12; }
        return (year*365) +(year/4) -(year/100) +(year/400) -1200820
                +(month*153+3)/5-92
                +day-1 - 2400000.5;
}
std::ostream& operator<<(std::ostream& out, const Date& ref) {
    std::string out_string = ref.get_date();
    out << out_string;
    return out;
}
}
