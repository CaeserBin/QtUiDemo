//
// Created by Caesar on 2026/1/4.
//


#ifndef TYPE_DISTRIBUTION_H
#define TYPE_DISTRIBUTION_H
#include <iostream>

template<typename T>
void process() {
    std::cout << "Default: " << typeid(T).name() << std::endl;
}

template<>
inline void process<int>() {
    std::cout << "Processing int" << std::endl;
}

template<>
inline void process<float>() {
    std::cout << "Processing float" << std::endl;
}

// 遍历类型列表并处理
template<typename List>
struct ProcessAll;

template<template<typename...> class List, typename T, typename... Ts>
struct ProcessAll<List<T, Ts...>> {
    static void execute() {
        process<T>();
        ProcessAll<List<Ts...>>::execute();
    }
};

template<template<typename...> class List>
struct ProcessAll<List<>> {
    static void execute() {}
};

void testTypeDistribution();

#endif // TYPE_DISTRIBUTION_H
