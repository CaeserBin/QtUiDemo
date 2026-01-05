//
// Created by Caesar on 2026/1/4.
//


#ifndef TYPE_CAST_H
#define TYPE_CAST_H
#include <type_traits>

#include "TypeList.h"


// 类型到值的映射
template<typename T>
struct TypeToValue;

template<>
struct TypeToValue<int> : std::integral_constant<int, 100> {};

template<>
struct TypeToValue<float> : std::integral_constant<int, 200> {};

template<>
struct TypeToValue<double> : std::integral_constant<int, 300> {};

// 遍历类型列表并获取值
template<typename List>
struct SumValues;

template<template<typename...> class List, typename T, typename... Ts>
struct SumValues<List<T, Ts...>>
    : std::integral_constant<int, TypeToValue<T>::value +
                                          SumValues<List<Ts...>>::value> {};

template<template<typename...> class List>
struct SumValues<List<>> : std::integral_constant<int, 0> {};


void testTypeCast();


#endif // TYPE_CAST_H
