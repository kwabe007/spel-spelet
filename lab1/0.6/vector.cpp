// vector assignment
#include <iostream>
#include <vector>


void testVector(std::vector<int> cyka) {
    cyka.push_back(3);
}

int main ()
{
  std::vector<int> foo (3,0);
  std::vector<int> bar (5,0);
  std::cout << "Size of bar: " << int(bar.size()) << '\n';
  testVector(3);

  //foo = std::vector<int>();
  std::cout << "Size of bar: " << int(bar.size()) << '\n';
  return 0;
}
