//
// Created by Caesar on 2026/1/4.
//


#ifndef TYPE_LIST_H
#define TYPE_LIST_H
#include <cstddef>

// 最简单的类型列表
template<typename... Ts>
struct TypeList {};

// 别名模板，方便使用
template<typename... Ts>
using TL = TypeList<Ts...>;

// 示例
using IntList = TypeList<int, float, double>;
using EmptyList = TypeList<>;

template<typename List>
struct Size;

/******************************************************************************/
/***************************** 获取列表大小 ***********************************/
/*****************************************************************************/

/// template<typename...> class List 这是一个模板模板参数，表示 List
/// 是一个可以接受任意数量类型参数的模板。
///
/// typename... Ts 这是一个可变模板参数包，表示 Ts 可以是零个或多个类型。
///
/// struct Size<List<Ts...>>是一个部分特化，专门处理 List 模板实例化后的类型
///
/// sizeof...(Ts) 计算 Ts 中的类型数量，并将其作为std::integral_constant的值


template<template<typename...> class List, typename... Ts>
struct Size<List<Ts...>> : std::integral_constant<std::size_t, sizeof...(Ts)> {
};

/// 为什么需要模板模板参数
/// 通用性
/// 通过使用模板模板参数，我们可以编写一个通用的模板，它可以处理任何符合特定模式的模板。
/// 例如， 模板不仅可以处理 ` TypeList` ，还可以处理其他类似的类型列表模板。 `
/// Size`
/// 2. 灵活性
/// 模板模板参数使得代码更加灵活，可以适应不同的需求。
/// 例如，如果你有另一个类型列表模板 ` MyTypeList` ，你也可以用同样的
/// 模板来计算它的大小。 ` Size`

// C++17起可以简化
template<typename List>
constexpr std::size_t Size_v = Size<List>::value;

/******************************************************************************/
/***************************** 获取第N个类型 **********************************/
/*****************************************************************************/
template<typename List, std::size_t N>
struct At;

/// 分治法执行参数包递归展开
/// 类型参数包展开形式 : <T0<T1<T2<T3<T4>>>>> -> <T1<T2<T3<T4>>>> ->
/// <T2<T3<T4>>> -> <T3<T4>> -> <T4>

/// 递归终止条件
template<template<typename...> class List, typename T, typename... Ts>
struct At<List<T, Ts...>, 0> {
    using type = T;
};

template<template<typename...> class List, typename T, typename... Ts,
         std::size_t N>
struct At<List<T, Ts...>, N> {
    using type = typename At<List<Ts...>, N - 1>::type;
};

// // 使用
// using MyList = TypeList<int, float, char>;
// static_assert(std::is_same_v<At<MyList, 0>::type, int>);
// static_assert(std::is_same_v<At<MyList, 2>::type, char>);

/******************************************************************************/
/***************************** 头部插入 **************************************/
/*****************************************************************************/

template<typename List, typename T>
struct PushFront;

template<template<typename...> class List, typename... Ts, typename T>
struct PushFront<List<Ts...>, T> {
    using type = List<T, Ts...>;
};

// // 使用
// using L1 = TypeList<float, double>;
// using L2 = PushFront<L1, int>::type;  // TypeList<int, float, double>

/******************************************************************************/
/***************************** 尾部插入 **************************************/
/*****************************************************************************/

template<typename List, typename T>
struct PushBack;

template<template<typename...> class List, typename... Ts, typename T>
struct PushBack<List<Ts...>, T> {
    using type = List<Ts..., T>;
};

// 使用
// using L1 = TypeList<int, float>;
// using L2 = PushBack<L1, double>::type; // TypeList<int, float, double>

/******************************************************************************/
/***************************** 高级操作实现 ***********************************/
/***************************** 列表链接 **************************************/
/*****************************************************************************/
template<typename List1, typename List2>
struct Concat;

template<template<typename...> class List, typename... Ts1, typename... Ts2>
struct Concat<List<Ts1...>, List<Ts2...>> {
    using type = List<Ts1..., Ts2...>;
};

// 使用
// using L1 = TypeList<int, float>;
// using L2 = TypeList<char, double>;
// using L3 = Concat<L1, L2>::type; // TypeList<int, float, char, double>


/******************************************************************************/
/***************************** 高级操作实现 ***********************************/
/***************************** 反转列表 **************************************/
/*****************************************************************************/

template<typename List>
struct Reverse;

template<template<typename...> class List>
struct Reverse<List<>> {
    using type = List<>;
};

template<template<typename...> class List, typename T, typename... Ts>
struct Reverse<List<T, Ts...>> {
    using type =
            typename PushBack<typename Reverse<List<Ts...>>::type, T>::type;
};

// 使用
// using L1 = TypeList<int, float, char>;
// using L2 = Reverse<L1>::type; // TypeList<char, float, int>

/******************************************************************************/
/***************************** 高级操作实现 ***********************************/
/***************************** 查找类型 **************************************/
/*****************************************************************************/

template<typename List, typename T>
struct Contains;

template<template<typename...> class List, typename T>
struct Contains<List<>, T> : std::false_type {};

template<template<typename...> class List, typename U, typename... Ts,
         typename T>
struct Contains<List<U, Ts...>, T>
    : std::conditional_t<std::is_same_v<U, T>, std::true_type,
                         Contains<List<Ts...>, T>> {};

// 使用示例
// using MyList = TypeList<int, float, double>;
// static_assert(Contains<MyList, float>::value == true);
// static_assert(Contains<MyList, char>::value == false);

// 类型分发
// 编译期工厂
//
#endif // TYPE_LIST_H
