//
// Created by Caesar on 2026/1/4.
//

#include "TypeCast.h"

#include <iostream>
void testTypeCast() {
    std::cout << "*************** test type cast ***********" << std::endl;
    using Types = TypeList<int, float, double>;
    static_assert(SumValues<Types>::value == 600); // 100 + 200 + 300
}
