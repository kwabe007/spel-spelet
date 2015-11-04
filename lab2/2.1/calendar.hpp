#ifndef CALENDAR_HPP
#define CALENDAR_HPP

#include <string>
#include<vector>
#include<iostream>
#include "westerndate.hpp"
#include"event.hpp"

namespace lab2 {

template <class T>

class Calendar {
    protected:
    std::vector<Event<T>> event_vector;
    int current_date;
    int created_events;

    from_julian_date();

    public:
    Calendar();
    /*template<typename T2>
    Calendar<T>(const Calendar<T2>& ref);
    template<typename T2>
    Calendar<T>& operator=(const Calendar<T2>&);
    Calendar(const Calendar& ref);*/

    ~Calendar();

    add_event(std::string name, int );

};

template <class T>
lab2::Calendar<T>::Calendar(){
    year = 0;
    month = 0;
    day = 0;

    from_julian_date(year,month,day);
}
template <class T>
int lab2::Calendar<T>::from_julian_date(const yr,const mth,const date) const {
            int year = yr;
            int month = mth+1;
            int day = dy+1;
            year+=8000;
            if(month<3) { year--; month+=12; }
            return (year*365) +(year/4) -(year/100) +(year/400) -1200820
                    +(month*153+3)/5-92
                    +day-1 - 2400000.5;
    }
}



#endif
