#ifndef EVENT_HPP
#define EVENT_HPP

#include <string>
#include<vector>
#include<iostream>

namespace lab2 {

template <class T>

class Event {
    protected:
    int nr;


    public:
    T date;
    std::string name;
    std::string desc;
    Event();
    Event(const std::string in_name, const T in_date);
    explicit Event(const std::string name, const T date, const int nr, const std::string desc ="");
    explicit Event(const int yr_in, const int mth_in, const int dy_in);

    template <class T2>
    bool operator < (const Event<T2>& ref)const;
    template <class T2>
    bool operator <= (const Event<T2>& ref)const;
    template <class T2>
    bool operator == (const Event<T2>& ref)const;
    template <class T2>
    bool operator != (const Event<T2>& ref)const;
    ~Event();

};
template <class T>
lab2::Event<T>::Event() {
    name = "";
    desc = "";
}

template <class T>
lab2::Event<T>::Event(const std::string in_name, const T in_date) {
    date = in_date;
    name = in_name;
}

template <class T>
lab2::Event<T>::~Event() {
}

template <class T>
template <class T2>
bool lab2::Event<T>::operator < (const Event<T2>& ref)const{
    return (this->date < ref.date);
}

template <class T>
template <class T2>
bool lab2::Event<T>::operator <= (const Event<T2>& ref)const{
    return (this->date <= ref.date);
}

template <class T>
template <class T2>
bool lab2::Event<T>::operator == (const Event<T2>& ref)const{
    return (this->date == ref.date && this->name.compare(ref.name) == 0);
}

template <class T>
template <class T2>
bool lab2::Event<T>::operator != (const Event<T2>& ref)const{
    return (this->date != ref.date || this->name.compare(ref.name) != 0);
}

}


#endif
