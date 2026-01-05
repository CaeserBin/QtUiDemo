//
// Created by Caesar on 2026/1/4.
//

#include "CompileFactory.h"
void testCompileFactory() {
    std::cout << "*********** test compile factory ***********" << std::endl;
    Base *obj = Factory<FactoryTypes>::create(1); // 创建Derived<2>
}
