#ifndef Event_HPP
#define Event_HPP

#include <string>
#include<vector>
#include<iostream>

namespace lab2 {

template <class T>

class Event {
    protected:
    int nr;
    T date;
    std::string name;
    std::string desc;


    public:
    Event();
    explicit Event(const std::string name, const T date, const int nr, const std::string desc ="");
    explicit Event(const int yr_in, const int mth_in, const int dy_in);

    ~Event();

};



}


#endif
