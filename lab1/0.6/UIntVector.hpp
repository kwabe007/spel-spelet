#ifndef UINTVECTOR
#define UINTVECTOR

#include <cstdio>
#include <stdexcept>
#include <algorithm>

class Vector;

class Vector {
private:
    int vLength;
    unsigned int* vPnData;

public:
    Vector(){
        vLength = 0;
        vPnData = 0;
    }
    Vector(const std::size_t vSize){
    vLength = vSize;
        vPnData = new unsigned int[vSize];
    }
    Vector(const Vector & ref){
        vLength = ref.vLength;
        vPnData = new unsigned int (*ref.vPnData);
    }
    Vector& operator= (Vector const& ref) {
        if (this != &ref) {
            unsigned int * newVPnData = new unsigned int [ref.vLength];
            std::copy(ref.vPnData, ref.vPnData + ref.vLength, newVPnData);

            delete [] vPnData;

            vPnData = newVPnData;
            vLength = ref.vLength;
        }

        return *this;
    }
    Vector(std::initializer_list<unsigned int> list)
        :vPnData { new unsigned int[list.size()]};
    {

    }

~Vector() {
    delete[] vPnData;
}

/*void reset() {
    for (int i = 0;i < vLength;++i) {
        vPnData[i] = {};

    }

}*/
std::size_t size() {
    return vLength;
}
unsigned int& operator[] (const int index) {
    if (index >= 0 && index < vLength) {
    return vPnData[index];
    }
    else {
        throw std::out_of_range("Index out of range");
    }
}
 unsigned int& operator[] (const int index) const {
    if (index >= 0 && index < vLength) {
    return vPnData[index];
    }
    else {
        throw std::out_of_range("Index out of range");
    }
}


};



#endif
