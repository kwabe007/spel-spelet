#ifndef UINTVECTOR
#define UINTVECTOR

#include <cstdio>
#include <stdexcept>
#include <algorithm>
#include <initializer_list>

class UIntVector;

class UIntVector {
private:
    int vLength;
    unsigned int* vPnData;

public:

    explicit UIntVector(){
        vLength = 0;
        vPnData = nullptr;
    }
    UIntVector(std::initializer_list<unsigned int> list){
        vLength = list.size();
        vPnData = new unsigned int[list.size()];
        std::copy(list.begin(), list.end(), vPnData);
    }
    explicit UIntVector(const std::size_t vSize){
        vLength = vSize;
        vPnData = new unsigned int[vSize]();
    }
    UIntVector(const UIntVector& ref){
        vPnData = new unsigned int[ref.vLength];
        std::copy(ref.vPnData, ref.vPnData + ref.vLength, vPnData);
        vLength = ref.vLength;
    }
    UIntVector(UIntVector&& ref) {
        vLength = ref.vLength;
        vPnData = ref.vPnData;
        ref.vLength = 0;
        ref.vPnData = nullptr;
    }
    UIntVector& operator= (UIntVector const& ref) {
        if (this != &ref) {
            unsigned int * newVPnData = new unsigned int [ref.vLength];
            std::copy(ref.vPnData, ref.vPnData + ref.vLength, newVPnData);
            delete [] vPnData;
            vPnData = newVPnData;
            vLength = ref.vLength;
        }
        return *this;
    }
    UIntVector& operator= (UIntVector&& ref) {
        if (this != &ref) {
            delete [] vPnData;
            vLength = 0;
            vLength = ref.vLength;
            vPnData = ref.vPnData;
            ref.vLength = 0;
            ref.vPnData = nullptr;
        }
        return *this;
    }

    ~UIntVector() {
        delete[] vPnData;
    }

    void reset() {
        for (int i = 0;i < vLength;++i) {
            vPnData[i] = 0;
        }
    }
    std::size_t size() const {
        return vLength;
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
