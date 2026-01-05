//
// Created by Caesar on 2026/1/4.
//

#include "TypeDistribution.h"

#include "TypeList.h"

void testTypeDistribution() {
    std::cout << "************** test type distribution *********" << std::endl;
    using Types = TypeList<int, float, double, char>;
    ProcessAll<Types>::execute();
}
