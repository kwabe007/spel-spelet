#ifndef TVECTOR
#define TVECTOR

#include <cstdio>
#include <stdexcept>
#include <algorithm>
#include <initializer_list>
#include <type_traits>
#include <iostream>

template <typename T>
class Vector{
    static_assert(std::is_move_assignable<T>::value,"Not move-assignable, asshole!");
    static_assert(std::is_move_constructible<T>::value,"Not move-constructible u cheeky scrub");
private:
    int vLength;
    int vCap;
    T * vPnData;

public:
    explicit Vector(){
        vLength = 0;
        vCap = 0;
        vPnData = nullptr;
    }
    explicit Vector(const std::initializer_list<T> list){
        vLength = list.size();
        vPnData = new T[list.size()];
        vCap = vLength;
        std::copy(list.begin(), list.end(), vPnData);
    }
    explicit Vector(const std::size_t vSize){
        vLength = vSize;
        vCap = vLength;
        vPnData = new T[vSize]{};
        //reset();
    }
    explicit Vector(const std::size_t vSize, const T val){
        vLength = vSize;
        vCap = vLength;
        vPnData = new T[vSize];
        for (int i = 0;i<vLength;++i) {
            vPnData[i]=val;
        }
    }
    Vector(const Vector& ref){
        vLength = ref.vLength;
        vCap = ref.vCap;
        vPnData = new T[vCap];
        std::copy(ref.vPnData, ref.vPnData + ref.vLength, vPnData);
    }
    Vector(Vector&& ref) {
        vLength = ref.vLength;
        vPnData = ref.vPnData;
        vCap = ref.vCap;
        ref.vCap = 0;
        ref.vLength = 0;
        ref.vPnData = nullptr;
    }

    Vector& operator= (Vector const& ref) {
        if (this != &ref) {
            T * newVPnData = new T [ref.vCap];
            std::copy(ref.vPnData, ref.vPnData + ref.vLength, newVPnData);
            delete [] vPnData;
            vPnData = newVPnData;
            vLength = ref.vLength;
            vCap = vLength;
        }
        return *this;
    }
    Vector& operator= (Vector&& ref) {
        if (this != &ref) {
            delete [] vPnData;
            vLength = ref.vLength;
            vCap = ref.vCap;
            vPnData = ref.vPnData;
            ref.vCap = 0;
            ref.vLength = 0;
            ref.vPnData = nullptr;
        }
        return *this;
    }
    friend std::ostream & operator<<(std::ostream & out, const
    Vector& vec) {
        out << "(" << vec.vLength << ", " <<
        vec.vCap << ")";
        return out;
    }

~Vector() {
    delete[] vPnData;
}

void reset() {
    for (std::size_t i = 0;i < vCap;++i) {
        vPnData[i] = T{};
    }
}
void clear() {
    vLength = 0;
    //vCap = 0;
}
void sort(bool ascend) {
    std::stable_sort(vPnData,vPnData+vLength);
    if (ascend) {
    }
    else {
        std::reverse(vPnData,vPnData+vLength);
    }

}

std::size_t size() const {
    return vLength;
}
std::size_t capacity() const {
    return vCap;
}
void push_back(T val) {
    if (vLength == vCap) {
        allocate();
    }
    vPnData[vLength] = val;
    ++vLength;
}
void insert(const std::size_t index, T val) {
    if (index >= 0 && index < vLength){
        if (vLength == vCap) {
            allocate();
        }
        for (int i=vLength; i>index;--i) {
            vPnData[i] = *(vPnData + i - 1);
        }
        vPnData[index] = val;
        ++vLength;
    }else if (index == vLength) {
        push_back(val);
    } else {
        throw std::out_of_range("OUT OF RANGE, BITCH!");
    }
}
void erase(const std::size_t index) {
    if (index >= 0 && index < vLength){
        for (int i=index; i<vLength-1;++i) {
            vPnData[i] = *(vPnData + i + 1);
        }
        --vLength;
    } else {
        throw std::out_of_range("OUT OF RANGE, BITCH!");
    }
}
T * begin() const{
   if (vLength > 0) {
       return vPnData;
   } else {
       return nullptr;
   }
}
T * end() const{
   if (vLength > 0) {
       return vPnData+vLength;
   } else {
       return nullptr;
   }
}
T * find(T const& val) const{
   for (int i = 0; i < vLength; ++i) {
       if (vPnData[i] == val) {
           return vPnData + i;
       }
   }
   return end();
}
void allocate() {
    if (vCap == 0) {
        vCap = 1;
    }
    vCap = vCap * 2;
    T * newVPnData = new T [vCap];
    std::copy(vPnData, vPnData + vLength, newVPnData);
    delete [] vPnData;
    vPnData = newVPnData;
}

T& operator[] (const int index) {
    if (index >= 0 && index < vLength) {
    return vPnData[index];
    }
    else {
        throw std::out_of_range("Index out of range");
    }
}
const T& operator[] (const int index) const {
    if (index >= 0 && index < vLength) {
    return vPnData[index];
    }
    else {
        throw std::out_of_range("Index out of range");
    }
}
};


#endif
