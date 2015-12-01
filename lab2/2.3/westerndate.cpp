#include "westerndate.hpp"
#include<iostream>

namespace lab2 {
WesternDate::WesternDate() : Date() {
    setup();
}
WesternDate::WesternDate(const int yr_in, const int mth_in, const int dy_in):Date(yr_in,mth_in,dy_in) {
    setup();
}
WesternDate::WesternDate(const Date& ref):Date(ref) {
    setup();
}
WesternDate::WesternDate(const Date* ref_ptr):Date(ref_ptr) {
    setup();
}
WesternDate::WesternDate(const WesternDate& ref):Date(ref) {
    setup();
}
WesternDate::~WesternDate(){}
void WesternDate::setup(){
    mpy = 12;
    ly_month = 1;
    leap_days = 1;
    months = std::vector<int>({31,28,31,30,31,30,31,31,30,31,30,31});
    ly_default = 28;
    wkds = {"monday","tuesday","wednesday","thursday","friday","saturday","sunday"};
    month_names = {"january","february","march","april","may","june","july","august","september","october","november","december"};
}
unsigned int WesternDate::week_day() const {
    int wd = (mod_julian_day()+ 2) % wkds.size();
    ++wd;
    return wd;
}
std::string WesternDate::week_day_name()const {
    int wd = week_day();
    return wkds[wd-1];
}

}
