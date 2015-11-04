#include<iostream>

template <typename T>
bool algo (T* start, T* end) {
    if (end-start <= 1) {
        return false;
    }

    T prec = *start;
    T prec2 = *(start + 1);
    for (T* it = start + 1; it != end ; ++it) {
        if(*it== prec || *it != prec2) {
            return false;
        }
        prec2 = prec;
        prec = *it;
    }
    return true;
}


int main() {
    int test1[5] = {1,2,1,2,1};
    int * test1end = test1 + 5;
    bool answer1 = algo(test1, test1end);

    int test2[6] = {1,2,1,2,1,2};
    int * test2end = test2 + 6;
    bool answer2 = algo(test2, test2end);

    int test3[6] = {1,2,1,2,1,3};
    int * test3end = test3 + 6;
    bool answer3 = algo(test3, test3end);

    int test4[5] = {2,1,2,1,2};
    int * test4end = test4 + 5;
    bool answer4 = algo(test4, test4end);

    int test5[1] = {1};
    int * test5end = test5 + 1;
    bool answer5 = algo(test5, test5end);


    std::cout << "Answer1: " << answer1 << std::endl;
    std::cout << "Answer2: " << answer2 << std::endl;
    std::cout << "Answer3: " << answer3 << std::endl;
    std::cout << "Answer4: " << answer4 << std::endl;
    std::cout << "Answer5: " << answer5 << std::endl;



    return 0;
}
