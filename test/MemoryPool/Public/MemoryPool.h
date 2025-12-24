//
// Created by Caesar on 2025/12/18.
//


#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H


#include <cassert>
#include <cstddef>

class SimpleFixedMemoryPool {
    struct Block {
        Block *next; // 空闲链表指针（使用嵌入指针技巧）
    };

    // 池参数
    static constexpr size_t ALIGNMENT = 8; // 对齐要求
    static constexpr size_t BLOCK_SIZE = 64; // 每个块大小（字节）
    static constexpr size_t POOL_SIZE = 1024; // 总块数

public:
    SimpleFixedMemoryPool();
    ~SimpleFixedMemoryPool();
    // 3. 分配操作：从空闲链表取出一块
    void *allocate();
    // 4. 释放操作：将块放回空闲链表
    void deallocate(void *ptr);
    // 工具函数：显示当前状态
    void printStatus() const;
    // 禁用拷贝（简单实现）
    SimpleFixedMemoryPool(const SimpleFixedMemoryPool &) = delete;
    SimpleFixedMemoryPool &operator=(const SimpleFixedMemoryPool &) = delete;

private:
    // 计算对齐后的实际块大小
    static size_t alignBlockSize(const size_t size) {
        return (size + ALIGNMENT - 1) & ~(ALIGNMENT - 1);
    }

    void increaseTotalAllocated() const;
    void decreaseTotalAllocated() const;

    char *memory; // 大块内存起始地址
    Block *freeList; // 空闲链表头指针
    mutable size_t totalAllocated; // 已分配块数（用于调试）
    mutable size_t topAllocated;
};

#endif // MEMORY_POOL_H
