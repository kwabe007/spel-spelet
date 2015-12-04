#ifndef WESTERNDATE__
#define WESTERNDATE__

#include "date.hpp"

namespace lab2 {

class WesternDate: public Date{
protected:
    virtual void setup_ly_cond()=0;
    virtual bool leap_year() const=0;
    virtual bool calculate_if_leap_year(const int year) const=0;
    virtual int mod_julian_day()const=0;
    virtual void from_julian_day(const int mjd, int* date)const =0;
    void setup();
    static std::vector<std::string>wkds = {"monday","tuesday","wednesday","thursday","friday","saturday","sunday"};
    std::vector<std::string> get_wkdy_vector();

public:
    WesternDate();
    explicit WesternDate(const int yr_in, const int mth_in, const int dy_in);
    WesternDate(const Date& ref);
    WesternDate(const Date* ref_ptr);
    WesternDate(const WesternDate& ref);
    ~WesternDate();


    unsigned int week_day() const;
    std::string week_day_name()const;
    virtual std::string ical_type()const=0;

};
}

#endif
