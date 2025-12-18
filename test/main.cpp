//
// Created by Caesar on 2025/12/17.
//

#include <iostream>

#include "lib.h"

struct A {
    int a;
};

union U {};

int main(int argc, char *argv[]) {
    std::cout << mlb::is_integral<int>::value << std::endl;
    std::cout << mlb::is_integral<char>::value << std::endl;
    std::cout << mlb::is_class<A>::value << std::endl;
    std::cout << mlb::is_union_v<U> << std::endl;
}
