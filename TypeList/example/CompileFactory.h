//
// Created by Caesar on 2026/1/4.
//


#ifndef COMPILE_FACTORY_H
#define COMPILE_FACTORY_H
#include <iostream>
#include "TypeList.h"

// 基类
class Base {
public:
    virtual ~Base() = default;
    virtual void print() const = 0;
};

// 具体类
template<int N>
class Derived final : public Base {
public:
    void print() const override {
        std::cout << "Derived<" << N << ">" << std::endl;
    }
};

// 类型列表：支持的类型
using FactoryTypes = TypeList<Derived<1>, Derived<2>, Derived<3>>;

// 工厂函数
template<typename List, typename Enable = void>
struct Factory;

template<template<typename...> class List, typename T, typename... Ts>
struct Factory<List<T, Ts...>, std::enable_if_t<sizeof...(Ts) >= 0>> {
    static Base *create(const std::size_t id) {
        if (id == 0) {
            return new T();
        }
        return Factory<List<Ts...>>::create(id - 1);
    }
};

template<template<typename...> class List>
struct Factory<List<>> {
    static Base *create(std::size_t) { return nullptr; }
};

void testCompileFactory();


#endif // COMPILE_FACTORY_H
