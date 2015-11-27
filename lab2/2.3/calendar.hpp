﻿#ifndef CALENDAR_HPP
#define CALENDAR_HPP

#include <string>
#include<vector>
#include<iostream>
#include<stdexcept>
#include <algorithm>
#include "date.hpp"
#include"event.hpp"

namespace lab2 {

template <class T>

class Calendar {
protected:
    T current_date;
public:
    std::vector<Event<T>> event_vector;
    int created_events;
    Calendar();
    template <class T2>
    Calendar(const Calendar<T2>& ref);
    explicit Calendar(const int year, const int month, const int day);

    /*template<typename T2>
    Calendar<T>(const Calendar<T2>& ref);
    template<typename T2>
    Calendar<T>& operator=(const Calendar<T2>&);
    Calendar(const Calendar& ref);*/

    ~Calendar();

    std::string get_date_str()const;
    T get_date()const;

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
bool Calendar<T>::add_event(const std::string name, const int year) {
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
    T temp_date;
    try {
        temp_date = T(year,month,day);
    } catch (const std::out_of_range& oor) {
        return false;
    }
    if (temp_date < current_date) {
        return false;
    }
    Event<T> event(name, temp_date);
    if (std::find(event_vector.begin(),event_vector.end(),event) == event_vector.end()) {
        event_vector.push_back(event);
        std::stable_sort(event_vector.begin(),event_vector.end());
        return true;
    }
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
            std::cerr << "event added: " << event.name << " " << event.date << std::endl;
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
std::ostream& operator<<(std::ostream& out,const Calendar<T>& ref){
    std::string out_string;
    typename std::vector<Event<T>>::const_iterator it = ref.event_vector.begin();
    /*for(;it != ref.event_vector.end(); ++it) {
        if(ref.current_date < it->date) {
            break;
        }
    }*/

    for (;it != ref.event_vector.end(); ++it) {
        if (it->date < ref.current_date) continue;
        out_string += it->date.get_date() + " : " + it->name + '\n';
        //std::cerr << it->date.year() << " " << it->date.month() << " " << it->date.day() << std::endl;
    }
    out << out_string;

    return out;
}

}

#endif
