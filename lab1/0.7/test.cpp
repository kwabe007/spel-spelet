// template specialization
#include <iostream>
#include "kth_cprog_template_container.hpp"
#include <typeinfo>
#include <vector>
using namespace std;

class NotMA
{
private:
    int cyka;
public:
    NotMA(){
        cyka = 0;
    }
    NotMA(const int i) {
        cyka = i;
    }
    NotMA(const NotMA& ref) {
        cyka = ref.cyka;
    }
    NotMA(NotMA&& ref) = delete;
};

template<typename T>
void printVector(const Vector<T>& vect) {
    for (T * it = vect.begin(); it != vect.end(); ++it) {
        cout << (int)*it << endl;
    }
    cout << "Size: " << vect.size() << endl;
    cout << "Cap: " << vect.capacity() << endl;
}

int main () {
  NotMA notma(3);
  Vector<double> shit(100,3.14);
  shit.insert(2, 55);
  shit.insert(2, 55);
  shit.clear();
  shit.push_back(23);
  shit.push_back(23);
  cout << shit << endl;
  shit.insert(2, 55);
  shit.insert(2, 55.5);
  shit.push_back(23);
  shit.insert(2, 55);
  shit.insert(0, 55);
  shit.push_back(23);
  shit.insert(0, 55);
  shit.push_back(23);
  //shit.reset();
  cout <<"this is shit ---------" << endl;
  printVector(shit);
  Vector<int> myint (7);
  Vector<float> myfloat;
  shit.reset();
  cout <<"this is first shit ---------" << endl;
  printVector(shit);
  shit.sort(false);
  cout <<"this is more shit ---------" << endl;
  printVector(shit);
  shit.sort(true);
  //shit.reset();
  cout <<"final shit ---------" << endl;
  printVector(shit);

  //TVector<NotMA> (2);

  for (int i =1;i<3;++i) {
    myint.push_back(i);
  }
  myfloat.push_back(22.05);
  cout << "myint" << endl;
  printVector(myint);
  myint.insert(2, 55);
  myint.erase(9);
  cout << "myint" << endl;
  printVector(myint);
  cout << "mychar" << endl;
  printVector(myfloat);
  std::cout << typeid(myfloat[1]).name() << '\n';

  return 0;
}
