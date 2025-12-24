//
// Created by Caesar on 2025/12/17.
//


#ifndef LIB_H
#define LIB_H

namespace mlb {
    template<typename T, T v>
    struct integral_constant {
        static constexpr T value = v;
        typedef T value_type;
        typedef integral_constant type;
    };

    struct true_type : integral_constant<bool, true> {};
    struct false_type : integral_constant<bool, false> {};

    /**************************************************************************/
    /**************************** is_integral *********************************/
    /**************************************************************************/
    template<typename T>
    struct is_integral : integral_constant<bool, false> {};
    template<>
    struct is_integral<bool> : true_type {};
    template<>
    struct is_integral<char> : true_type {};
    template<>
    struct is_integral<signed char> : true_type {};
    template<>
    struct is_integral<unsigned char> : true_type {};
    template<>
    struct is_integral<wchar_t> : true_type {};
    template<>
    struct is_integral<short> : true_type {};
    template<>
    struct is_integral<unsigned short> : true_type {};
    template<>
    struct is_integral<int> : true_type {};
    template<>
    struct is_integral<unsigned int> : true_type {};
    template<>
    struct is_integral<long> : true_type {};
    template<>
    struct is_integral<unsigned long> : true_type {};
    template<>
    struct is_integral<long long> : true_type {};
    template<>
    struct is_integral<unsigned long long> : true_type {};
    template<>
    struct is_integral<char16_t> : true_type {};
    template<>
    struct is_integral<char32_t> : true_type {};

    /**************************************************************************/
    /**************************** enable_if ***********************************/
    /**************************************************************************/
    template<bool B, class T = void>
    struct enable_if {};

    template<class T>
    struct enable_if<true, T> {
        typedef T type;
    };

    template<bool B, typename T>
    using enable_if_t = typename enable_if<B, T>::type;

    /**************************************************************************/
    /**************************** is_const ************************************/
    /**************************************************************************/

    template<typename T>
    struct is_const : false_type {};
    template<typename T>
    struct is_const<const T> : true_type {};

    /**************************************************************************/
    /**************************** is_class ************************************/
    /**************************************************************************/

    // helper class, sizeof(two) = 2
    struct two {
        char c[2];
    };
    namespace is_class_imp {
        template<class T>
        char test(int T::*); // 接收成员指针，只有类和结构体才满足具备成员的条件
        template<class T>
        two test(...); // 接收一切参数,只有travel类型才会返回two
    } // namespace is_class_imp

    template<class T>
    struct is_class
        : integral_constant<bool, sizeof(is_class_imp::test<T>(nullptr)) == 1> {
    };

    /**************************************************************************/
    /**************************** is_enum *************************************/
    /**************************************************************************/

    template<typename T>
    struct is_enum : integral_constant<bool, __is_enum(T)> {};

    template<typename T>
    using is_enum_v = typename is_enum<T>::value;

    /**************************************************************************/
    /**************************** is_union ************************************/
    /**************************************************************************/
    template<typename T>
    struct is_union : integral_constant<bool, __is_union(T)> {};
    template<typename T>
    inline constexpr bool is_union_v = is_union<T>::value;

    /**************************************************************************/
    /**************************** is_void *************************************/
    /**************************************************************************/

    template<class T>
    struct is_void : false_type {};

    template<>
    struct is_void<void> : true_type {};

    /**************************************************************************/
    /**************************** is_reference ********************************/
    /**************************************************************************/

    // 基础模板
    template<class T>
    struct is_reference : false_type {};

    // 左值引用特化
    template<class T>
    struct is_reference<T &> : true_type {};

    // 右值引用特化
    template<class T>
    struct is_reference<T &&> : true_type {};

    /**************************************************************************/
    /**************************** is_nullptr **********************************/
    /**************************************************************************/

    template<class T>
    struct is_nullptr : false_type {};

    typedef decltype(nullptr) nullptr_t;
    template<>
    struct is_nullptr<nullptr_t> : true_type {};

    /**************************************************************************/
    /**************************** is_array ************************************/
    /**************************************************************************/

    template<class T>
    struct is_array : false_type {};
    template<class T>
    struct is_array<T[]> : true_type {};

    /**************************************************************************/
    /**************************** is_function *********************************/
    /**************************************************************************/
    // template<class T>
    // struct is_function : false_type {};
    template<typename T>
    struct is_function : integral_constant<bool, !is_const<const T>::value> {};

    template<class T>
    struct is_function<T (*)()> : true_type {};
    template<class T>
    struct is_function<T (&)()> : true_type {};
    template<class T>
    struct is_function<T (&&)()> : true_type {};
    template<class T, class... Args>
    struct is_function<T (*)(Args...)> : true_type {};
    template<class T, class... Args>
    struct is_function<T (&)(Args...)> : true_type {};
    template<class T, class... Args>
    struct is_function<T (&&)(Args...)> : true_type {};


    /**************************************************************************/
    /**************************** is_pointer **********************************/
    /**************************************************************************/
    template<class T>
    struct is_pointer : false_type {};
    template<class T>
    struct is_pointer<T *> : true_type {};
    template<class T>
    struct is_pointer<T *const> : true_type {};
    template<class T>
    struct is_pointer<T *volatile> : true_type {};
    template<class T>
    struct is_pointer<T *const volatile> : true_type {};


    /**************************************************************************/
    /**************************** remove_reference ****************************/
    /**************************************************************************/
    template<class T>
    struct remove_reference {
        typedef T type;
    };
    template<class T>
    struct remove_reference<T &> {
        typedef T type;
    };
    template<class T>
    struct remove_reference<T &&> {
        typedef T type;
    };

    /**************************************************************************/
    /**************************** remove_extent *******************************/
    /**************************************************************************/

    template<class T>
    struct remove_extent {
        typedef T type;
    };
    template<class T>
    struct remove_extent<T[]> {
        typedef T type;
    };
    template<class T, size_t N>
    struct remove_extent<T[N]> {
        typedef T type;
    };


    /**************************************************************************/
    /**************************** remove_const ********************************/
    /**************************************************************************/
    template<typename T>
    struct remove_const {
        typedef T type;
    };
    template<typename T>
    struct remove_const<const T> {
        typedef T type;
    };
    template<typename T>
    struct remove_const<const T &> {
        typedef T &type;
    };
    template<typename T>
    struct remove_const<const T &&> {
        typedef T &&type;
    };
    template<typename T>
    struct remove_const<const T *> {
        typedef T *type;
    };
    template<typename T>
    struct remove_const<const T *const> {
        typedef T *const type;
    };

    /**************************************************************************/
    /**************************** decay ***************************************/
    /**************************************************************************/

    // template<class T>
    // struct decay {
    //     typedef typename remove_reference<T>::type U;
    //     typedef typename std::conditional<
    //             is_array<U>::value, typename remove_extent<U>::type *,
    //             typename std::conditional<
    //                     is_function<U>::value,
    //                     typename std::add_pointer<U>::type,
    //                     typename std::remove_cv<U>::type>::type>::type type;
    // };

    /**************************************************************************/
    /**************************** common_type *********************************/
    /**************************************************************************/

    // 类声明，注意三个点，这说明这个类可以有任意多个模板参数
    template<class... T>
    struct common_type;

    // 针对只有一个模板参数的特化
    template<class T>
    struct common_type<T> {
        typedef typename std::decay<T>::type type;
    };

    // 针对两个模板参数的特化
    template<class T, class U>
    struct common_type<T, U> {
    private:
        static T &&t();
        static U &&u();
        static bool f();

    public:
        typedef typename std::decay<decltype(f() ? t() : u())>::type type;
    };

    // 针对三个或以上模板参数的特化
    template<class T, class U, class... V>
    struct common_type<T, U, V...> {
        typedef typename common_type<typename common_type<T, U>::type,
                                     V...>::type type;
    };

} // namespace mlb
#endif // LIB_H
