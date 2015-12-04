#ifndef CALENDAR_HPP
#define CALENDAR_HPP

#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "date.hpp"
#include "event.hpp"
#include "debugmacro.h"

namespace lab2 {

template <class T>

class Calendar {
protected:
    T current_date;
    std::string get_date_trunc_str(const T& date)const;
    std::string ical_builder()const;
    std::vector<Event<T>> event_vector;
    int created_events;
    T get_date()const;

    template<typename T2> friend class Calendar;

public:

    Calendar();
    template <class T2>
    Calendar(const Calendar<T2>& ref);
    explicit Calendar(const int year, const int month, const int day);

    ~Calendar();




    bool add_event(const std::string name);
    bool add_event(const std::string name, const int year);
    bool add_event(const std::string name, const int year, const int month);
    bool add_event(const std::string name, const int year, const int month, const int day);

    bool remove_event(const std::string name);
    bool remove_event(const std::string name, const int year);
    bool remove_event(const std::string name, const int year, const int month);
    bool remove_event(const std::string name, const int year, const int month, const int day);
    bool set_date(const int year, const int month, const int day);


    template <class T2>
    Calendar<T>& operator=(const Calendar<T2>&);
    template <class T2>
    bool operator==(const Calendar<T2>&)const;
    template <class T2>
    bool operator!=(const Calendar<T2>&)const;
    template<class K>
    friend std::ostream& operator<<(std::ostream& out, const Calendar<K>& ref);
    std::string get_date_str()const;
};

template <class T>
Calendar<T>::Calendar(){
    T date;
    current_date = date;
}

template <class T>
template< class T2>
Calendar<T>::Calendar(const Calendar<T2>& ref){
    current_date = ref.get_date();
    for (typename std::vector<Event<T2>>::const_iterator it = ref.event_vector.begin(); it != ref.event_vector.end(); ++it) {
        Event<T> event;
        event.date = it->date;
        event.name = it->name;
        event.desc = it->desc;
        event_vector.push_back(event);
    }
}

template <class T>
Calendar<T>::Calendar(const int year, const int month, const int day){
    T date(year,month,day);
    current_date = date;
}

template <class T>
Calendar<T>::~Calendar(){
}

template <class T>
bool Calendar<T>::set_date(const int year, const int month, const int day){
    try {
        current_date = T(year, month, day);
    } catch (const std::out_of_range& oor) {
        return false;
    }
    typename std::vector<Event<T>>::iterator it;
    for (it = event_vector.end()-1; it != event_vector.begin()-1; --it) {
        if (it->date < current_date) {
            break;
        }
    }
    event_vector.erase(event_vector.begin(),it+1);
    return true;
}

template <class T>
bool Calendar<T>::add_event(const std::string name) {
    T temp_date;
    int year = temp_date.year();
    int month = temp_date.month();
    int day = temp_date.day();
    return add_event(name, year, month, day);
}

template <class T>
bool Calendar<T>::add_event(const std::string name, const int year ) {
    T temp_date;
    int month = temp_date.month();
    int day = temp_date.day();
    return add_event(name, year, month, day);
}

template <class T>
bool Calendar<T>::add_event(const std::string name, const int year, const int month) {
    T temp_date;
    int day = temp_date.day();
    return add_event(name, year, month, day);
}

template <class T>
bool Calendar<T>::add_event(const std::string name, const int year, const int month, const int day) {
    T temp_date;,
    try {
        temp_date = T(year,month,day);
    } catch (const std::out_of_range& oor) {
        return false;
    }
    debug_println(BIT0, "Adding event with name '" << name << "' and date " << temp_date);

    Event<T> event(name, temp_date);
    if (std::find(event_vector.begin(),event_vector.end(),event) == event_vector.end()) {
        event_vector.push_back(event);
        std::stable_sort(event_vector.begin(),event_vector.end());
        return true;
    }
    debug_println(BIT0, "Found event already with name '" << name << "' and date " << temp_date);
    return false;
}

template <class T>
bool Calendar<T>::remove_event(const std::string name) {
    T temp_date;
    int year = temp_date.year();
    int month = temp_date.month();
    int day = temp_date.day();
    return remove_event(name, year, month, day);
}

template <class T>
bool Calendar<T>::remove_event(const std::string name, const int year) {
    T temp_date;
    int month = temp_date.month();
    int day = temp_date.day();
    return remove_event(name, year, month, day);
}

template <class T>
bool Calendar<T>::remove_event(const std::string name, const int year, const int month) {
    T temp_date;
    int day = temp_date.day();
    return remove_event(name, year, month, day);
}

template <class T>
bool Calendar<T>::remove_event(const std::string name, const int year, const int month, const int day) {
    T temp_date;
    try {
        temp_date = T(year,month,day);
    } catch (const std::out_of_range& oor) {
        return false;
    }
    Event<T> event(name, temp_date);
    typename std::vector<Event<T>>::iterator it;
    it = std::find(event_vector.begin(),event_vector.end(),event);
    if ( it != event_vector.end()) {
        event_vector.erase(it);
        return true;
    }
    return false;
}

template <class T>
std::string Calendar<T>::get_date_str()const{
    std::string out_string;
    out_string.append(current_date.week_day_name()+ " " + current_date.get_date());
    return out_string;
}

template <class T>
T Calendar<T>::get_date()const{
    T temp_date(current_date);
    return temp_date;
}

template <class T>
template< class T2>
Calendar<T>& Calendar<T>::operator =(const Calendar<T2>& ref){
    if (*this != ref) {
        current_date = ref.get_date();
        event_vector.clear();
        for (typename std::vector<Event<T2>>::const_iterator it = ref.event_vector.begin(); it != ref.event_vector.end(); ++it) {
            Event<T> event;
            event.date = it->date;
            event.name = it->name;
            event.desc = it->desc;
            event_vector.push_back(event);
            debug_println(BIT0, "event added: " << event.name << " " << event.date);
        }
    }
    return *this;
}

template <class T>
template< class T2>
bool Calendar<T>::operator ==(const Calendar<T2>& ref)const{
    if (current_date == ref.get_date() && event_vector.size() == ref.event_vector.size()) {
        if (std::equal (event_vector.begin(), event_vector.end(), ref.event_vector.begin())) {
            return true;
        }
    }
    return false;
}

template <class T>
template< class T2>
bool Calendar<T>::operator !=(const Calendar<T2>& ref)const{
    if (current_date == ref.get_date() && event_vector.size() == ref.event_vector.size()) {
        if (std::equal (event_vector.begin(), event_vector.end(), ref.event_vector.begin())) {
            return false;
        }
    }
    return true;
}

template <class T>
std::string Calendar<T>::ical_builder()const{
    std::string ical;
    ical += "BEGIN:VCALENDAR\n";
    ical += "VERSION:2.0\n";
    ical += "PRODID://Business Name//Product Name//EN\n";
    ical += "CALSCALE:"+current_date.ical_type()+"\n";
    ical += "X-WR-TIMEZONE:Europe/Stockholm\n";
    debug_print(BIT0, "Going through events");
    for (Event<T> event:event_vector) {
        if (event.date < current_date) continue;
        ical += "BEGIN:VEVENT\n";
        ical += "DTSTART;VALUE=DATE:"+get_date_trunc_str(event.date)+"\n";
        ical += "SUMMARY:"+event.name+"\n";
        ical += "END:VEVENT\n";
    }
    ical += "END:VCALENDAR";
    return ical;
}

template <class T>
std::string Calendar<T>::get_date_trunc_str(const T& date)const {
    std::string out_string;
    std::string year = std::to_string(date.year());
    std::string month = std::to_string(date.month());
    if (month.size() == 1){
        month.insert(0,"0");
    }
    std::string day = std::to_string(date.day());
    if (day.size() == 1){
        day.insert(0,"0");
    }
    out_string.append(year+month+day);
    return out_string;
}


template <class T>
std::ostream& operator<<(std::ostream& out,const Calendar<T>& ref){
    std::string out_string;
    /*typename std::vector<Event<T>>::const_iterator it = ref.event_vector.begin();
    for (;it != ref.event_vector.end(); ++it) {
        if (it->date < ref.current_date) continue;
        out_string += it->date.get_date() + " : " + it->name + '\n';
    }*/
    out_string += ref.ical_builder();
    out << out_string;

    return out ;
}

}

#endif
