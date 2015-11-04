#include <string>
#include <iostream>


#include "parse.hpp"

void insert_names(const std::string text) {
    std::string str = text;
    for(std::string::iterator it = str.begin(); it != str.end(); ++it) {
        if (*it == '/' && it + 1 != str.end()) {
            if (*(it+1) == '@') {
                std::cout << "ALLAHU AKBAR!" << std::endl;
            }
        }
    }
}

int main() {

    std::string text("Ditt namn är /@PLAYER_NAME. Du saknar jobb, pengar och har typ ingen framtid. Du bor tillsammans med dina två s.k. 'vänner' /@FRIEND_NAME1 och /@FRIEND_NAME2 i en");
    insert_names(text);
}
