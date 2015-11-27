#include "date.hpp"
#include<string>
#include<iostream>
#include<vector>
#include"kattistime.h"
#include<stdexcept>

namespace lab2 {

Date::Date(){
    time_t mytime;
    k_time(&mytime);
    struct tm *t = gmtime(&mytime);
    int year  = t->tm_year + 1900;
    int month = t->tm_mon + 1;      // månaderna och dagarna
    int day   = t->tm_mday;
    mjd_create = mjd_setup(year, month, day);
}
Date::Date(const int mjd){
    if (mjd < -101127 || mjd > 416787) {
        throw std::invalid_argument ("Out of range");
    }
    mjd_create = mjd;
}
Date::Date(const int yr_in,const int mth_in,const int dy_in){
    yr = yr_in;
    mth = mth_in-1;
    dy = dy_in-1;
}
Date::Date(const Date& ref){
    mjd_create = ref.mod_julian_day();
}
Date::Date(const Date* ref_ptr){
    mjd_create = ref_ptr->mod_julian_day();
}
Date::~Date(){}
int Date::day() const {
    return dy + 1;
}
int Date::month() const {
    return mth + 1;
}
int Date::year() const {
    return yr;
}
void Date::add_d() {
    if (++dy >= current_dpm()) {
        dy = 0;
        add_m();
    }
}
void Date::add_m() {
    ++mth;
    if (mth >= mpy) {
        mth = 0;
        add_y();
    }
}
void Date::add_y() {
    ++yr;
}
void Date::rem_d() {
    if (--dy < 0) {
        rem_m();
        dy = current_dpm()-1;
    }
}
void Date::rem_m() {
    --mth;
    if (mth < 0) {
        mth = mpy-1;
        rem_y();
    }
}
void Date::rem_y() {
    --yr;
}

int Date::current_dpm() const {
    if (leap_year() && mth == ly_month)
    return months[mth] + leap_days;
    return months[mth];
}

int Date::days_this_month() const {
    return current_dpm();
}
int Date::months_per_year() const {
    return mpy;
}
int Date::days_per_week() const {
    return wkds.size();
}
Date& Date::operator = (const Date& ref){
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
int Date::operator + (const Date& ref) const {
    int sum = this->mod_julian_day() + ref.mod_julian_day();
    return sum;
}
int Date::operator - (const Date& ref) const {
    int difference = this->mod_julian_day() - ref.mod_julian_day();
    return difference;
}
Date& Date::operator ++ () {
    add_d();
    return *this;
    }
Date& Date::operator -- () {
    rem_d();
    return *this;
    }
Date& Date::operator += (const int incr){
    if (incr >= 0) {
        for (int i = 0; i < incr; ++i) {
            add_d();
        }
    } else {
        int rev = incr * (-1);
        for (int i = 0; i < rev; ++i) {
            rem_d();
        }
    }
    return *this;
}
Date& Date::operator -= (const int decr){
    if (decr >= 0) {
        for (int i = 0; i < decr; ++i) {
            rem_d();
        }
    } else {
        int rev = decr * (-1);
        for (int i = 0; i < rev; ++i) {
            add_d();
        }
    }

    return *this;
}
void Date::add_year(const int incr) {
    //std::cerr << (int)is_(yr) << std::endl;
    yr += incr;
    if (dy >= current_dpm()) {
        dy = current_dpm()-1;
    }
}
void Date::add_month(const int incr) {
    if(incr >= 0) {
        yr += (incr+mth)/mpy;
        mth = (mth+incr)%mpy;
    } else {
        int decr = incr * (-1);
        yr -= (mth < decr) ? 1 + (decr-(mth+1))/mpy : 0;
        int decr_mod = decr%mpy;
        mth = (mth < decr_mod) ? mth-decr_mod+mpy : mth-decr_mod;

    }
    if (dy >= current_dpm())
    dy = current_dpm()-1;
}

bool Date::operator == (const Date& ref) const {
    if (this->mod_julian_day() == ref.mod_julian_day()) {
        return true;
    }
    else {
        return false;
    }
}
bool Date::operator <= (const Date& ref) const{
    if (this->mod_julian_day() <= ref.mod_julian_day()) {
        return true;
    }
    else {
        return false;
    }
}
bool Date::operator >= (const Date& ref) const {
    if (this->mod_julian_day() >= ref.mod_julian_day()) {
        return true;
    }
    else {
        return false;
    }
}
bool Date::operator > (const Date& ref) const {
    if (this->mod_julian_day() > ref.mod_julian_day()) {
        return true;
    }
    else {
        return false;
    }
}
bool Date::operator < (const Date& ref) const {
    if (this->mod_julian_day() < ref.mod_julian_day()) {
        return true;
    }
    else {
        return false;
    }
}
bool Date::operator != (const Date& ref) const {
    if (this->mod_julian_day() != ref.mod_julian_day()) {
        return true;
    }
    else {
        return false;
    }
}
int Date::mjd_setup(const int y,const int m, const int d){
        int year = y;
        int month = m;
        int day = d;
        year+=8000;
        if(month<3) { year--; month+=12; }
        return (year*365) +(year/4) -(year/100) +(year/400) -1200820
                +(month*153+3)/5-92
                +day-1 - 2400000.5;
}
std::string Date::get_date() const {
    std::string days = std::to_string(day());
    std::string months = std::to_string(month());
    std::string years = std::to_string(year());
    if (months.size() == 1) months.insert(0,"0");
    if (days.size() == 1) days.insert(0,"0");
    std::string final(years+"-"+months+"-"+days);
    return final;
}
std::ostream& operator<<(std::ostream& out, const Date& ref) {
    std::string out_string;
    out_string.append(std::to_string(ref.year()) + "-");
    std::string month = std::to_string(ref.month());
    if (month.size() == 1){
        month.insert(0,"0");
    }
    out_string.append(month + "-");
    std::string day = std::to_string(ref.day());
    if (day.size() == 1){
        day.insert(0,"0");
    }
    out_string.append(day);
    out << out_string;
    return out;
}
}
