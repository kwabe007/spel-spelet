#include <iostream>


class Polygon {

  public:
    int width, height;
    Polygon() : width(5) {
        std::cout << "default ctor" << std::endl;
    }
    Polygon(Polygon& other) {
        std::cout << "copy ctor" << std::endl;
    }

    Polygon& operator= (Polygon& other) {
        std::cout << "assignment" << std::endl;
        return *this;
    }

    void set_values (int a, int b)
      { width=a; height=b; }
    int area ()
      { return 0; }
};

class Shape : public Polygon {

  public:
    Shape() {
        std::cout << "default Cont ctor" << std::endl;
    }
    Shape(Shape& other) {
        std::cout << "copy Cont ctor" << std::endl;
    }

    Shape& operator= (Shape& other) {
        std::cout << "Cont assignment" << std::endl;
        return *this;
    }

    void set_values (int a, int b)
      { }
    int area ()
      { return 0; }
};
class Square : public Shape {

  public:
    Square() {
        std::cout << "default sq ctor" << std::endl;
    }
    Square(Square& other) {
        std::cout << "copy sq ctor" << std::endl;
    }

    Square& operator= (Square& other) {
        std::cout << "sq assignment" << std::endl;
        return *this;
    }

    void set_values (int a, int b)
      { }
    int area ()
      { return 0; }
};


int main () {
    Square sq;
    return 0;
}
