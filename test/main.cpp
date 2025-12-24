//
// Created by Caesar on 2025/12/17.
//

#include <iostream>

#include "MemoryPool.h"
#include "lib.h"

int main(int argc, char *argv[]) {
    SimpleFixedMemoryPool pool;

    // 分配一些块
    void *block1 = pool.allocate();
    void *block2 = pool.allocate();
    void *block3 = pool.allocate();

    std::cout << "分配3个块后:\n";
    pool.printStatus();

    // 释放一个块
    pool.deallocate(block2);
    std::cout << "释放1个块后:\n";
    pool.printStatus();

    // 再分配一些
    void *block4 = pool.allocate();
    void *block5 = pool.allocate();
    std::cout << "再分配2个块后:\n";
    pool.printStatus();

    // 清理
    pool.deallocate(block1);
    pool.deallocate(block3);
    pool.deallocate(block4);
    pool.deallocate(block5);

    return 0;
}
