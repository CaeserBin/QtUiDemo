//
// Created by Caesar on 2025/12/18.
//

#include "MemoryPool.h"

#include <iostream>

SimpleFixedMemoryPool::SimpleFixedMemoryPool() :
    memory(nullptr), freeList(nullptr), totalAllocated(0), topAllocated(0) {
    // 1. 预分配大块内存
    const size_t actualBlockSize = alignBlockSize(BLOCK_SIZE);
    const size_t totalMemory = actualBlockSize * POOL_SIZE;
    memory = new char[totalMemory];
    // 2. 初始化空闲链表（所有块都在空闲链表中）
    freeList = reinterpret_cast<Block *>(memory);
    // 将大块内存连接成空闲链表
    char *current = memory;
    for (size_t i = 0; i < POOL_SIZE - 1; ++i) {
        auto *currentBlock = reinterpret_cast<Block *>(current);
        auto *nextBlock = reinterpret_cast<Block *>(current + actualBlockSize);
        currentBlock->next = nextBlock;
        current += actualBlockSize;
    }
    // 最后一个块的next置为nullptr
    auto *lastBlock = reinterpret_cast<Block *>(current);
    lastBlock->next = nullptr;
    std::cout << "内存池初始化完成，块大小: " << actualBlockSize
              << " 字节，总块数: " << POOL_SIZE << "\n";
}

SimpleFixedMemoryPool::~SimpleFixedMemoryPool() {
    delete[] memory;
    std::cout << "内存池销毁，峰值使用: " << topAllocated << "/" << POOL_SIZE
              << " 块\n";
}

void *SimpleFixedMemoryPool::allocate() {
    if (freeList == nullptr) {
        std::cerr << "内存池耗尽！\n";
        return nullptr;
    }
    Block *allocatedBlock = freeList;
    freeList = freeList->next;
    increaseTotalAllocated();

    // 返回块的内存地址（跳过Block头）
    return static_cast<void *>(allocatedBlock);
}

void SimpleFixedMemoryPool::deallocate(void *ptr) {
    if (ptr == nullptr)
        return;

    // 将返回的指针转换回Block指针
    Block *freedBlock = static_cast<Block *>(ptr);

    // 插入到空闲链表头部
    freedBlock->next = freeList;
    freeList = freedBlock;
    decreaseTotalAllocated();
}

void SimpleFixedMemoryPool::printStatus() const {
    size_t freeCount = 0;
    const Block *current = freeList;
    while (current) {
        freeCount++;
        current = current->next;
    }
    std::cout << "状态: 已分配 " << totalAllocated << "，空闲 " << freeCount
              << "，总计 " << POOL_SIZE << "\n";
}

void SimpleFixedMemoryPool::increaseTotalAllocated() const {
    if (++totalAllocated > topAllocated)
        topAllocated = totalAllocated;
}

void SimpleFixedMemoryPool::decreaseTotalAllocated() const { --totalAllocated; }
