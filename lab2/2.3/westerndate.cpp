#include "westerndate.hpp"
#include<iostream>

namespace lab2 {
lab2::WesternDate::WesternDate() : Date() {
    setup();
}
lab2::WesternDate::WesternDate(const int yr_in, const int mth_in, const int dy_in):Date(yr_in,mth_in,dy_in) {
    setup();
}
lab2::WesternDate::WesternDate(const Date& ref):Date(ref) {
    setup();
}
lab2::WesternDate::WesternDate(const Date* ref_ptr):Date(ref_ptr) {
    setup();
}
lab2::WesternDate::WesternDate(const WesternDate& ref):Date(ref) {
    setup();
}
lab2::WesternDate::~WesternDate(){}
void lab2::WesternDate::setup(){
    mpy = 12;
    ly_month = 1;
    months = new int[12]{31,28,31,30,31,30,31,31,30,31,30,31};
    ly_default = 28;
    wkds = {"monday","tuesday","wednesday","thursday","friday","saturday","sunday"};
    month_names = {"january","february","mars","april","may","june","july","august","september","october","november","december"};
}
int lab2::WesternDate::week_day() const {
    int wd = (mod_julian_day()+ 2) % wkds.size();
    ++wd;
    return wd;
}
std::string lab2::WesternDate::week_day_name()const {
    int wd = week_day();
    return wkds[wd-1];
}
std::string lab2::WesternDate::month_name()const {
    return month_names[mth];
}

}
