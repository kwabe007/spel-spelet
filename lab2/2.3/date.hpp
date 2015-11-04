#ifndef DATE_HPP
#define DATE_HPP

#include<string>
#include<iostream>
#include<vector>
#include <stdexcept>

namespace lab2 {

class Date {

protected:

    int yr;
    int mth;
    int dy;
    int mpy;
    int current_dpm;
    int ly_interval;
    int ly_month;
    int ly_default;
    int* months;
    bool leap_year;
    int date[3];
    int mjd_create;
    std::string current_wd;
    std::vector<std::string> wkds;
    std::vector<std::string> month_names;

    void add_d();
    void add_m();
    void add_y();
    void rem_d();
    void rem_m();
    void rem_y();
    virtual bool is_leap_year(const int year) const=0;
    void set_date(const int year,const int month,const int day);
    virtual void setup_ly_cond()=0;
    virtual int mod_julian_day()const=0;
    virtual void from_julian_day(const int mjd, int* date)const=0;
    int mjd_setup(const int year,const int month, const int day);

public:

    Date();
    Date(const int mjd);
    explicit Date(const int yr_in,const int mth_in,const int dy_in);
    Date(const Date& ref);
    Date(const Date* ref_ptr);

    virtual ~Date()=0;

    //Public access functions
    int year()const;
    int month()const;
    int day()const;
    virtual int week_day()const=0;
    virtual std::string week_day_name()const=0;
    virtual std::string month_name()const=0;
    int days_this_month()const;
    int days_per_week() const;
    int months_per_year()const;
    std::string get_date() const;

    //Public mutator functions
    void add_year(const int incr = 1);
    void add_month(const int incr = 1);

    //Copying operator functions
    int operator + (const Date& ref)const;
    int operator - (const Date& ref)const;

    //Mutating operator functions
    Date& operator = (const Date& ref);
    Date& operator ++ ();
    Date& operator -- ();
    Date& operator += (const int incr);
    Date& operator -= (const int incr);

    //Comparing operator functions
    bool operator == (const Date& ref)const;
    bool operator <= (const Date& ref)const;
    bool operator >= (const Date& ref)const;
    bool operator < (const Date& ref)const;
    bool operator > (const Date& ref)const;
    bool operator != (const Date& ref)const;

    friend std::ostream& operator<<(std::ostream& out, const Date& ref);

};

}

#endif // DATE_HPP
