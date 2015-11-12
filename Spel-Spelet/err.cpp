#include <iostream>

int main() {
    std::string mystring;
    while(true) {
        std::cin >> mystring;
        if (std::cin.eof()){
            break;
        }
        std::cout << mystring << std::endl;
    }
}
