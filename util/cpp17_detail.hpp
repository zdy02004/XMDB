/*
g++ -C -std=c++11 cpp17_detail.hpp 
由于std::invoke_result 在 c++ 17 才有
而本项目定位是支持  c++ 11 的，所以 扒了一个 c++ 17 的实现
*/

#ifndef CPP17_DETAIL
#define CPP17_DETAIL
#include <type_traits>
#include <utility>

namespace inner_cpp17_detail {
template <class T>
struct is_reference_wrapper : std::false_type {};
template <class U>
struct is_reference_wrapper<std::reference_wrapper<U>> : std::true_type {};
 
template <class Base, class T, class Derived, class... Args>
auto INVOKE(T Base::*pmf, Derived&& ref, Args&&... args)
 -> typename std::enable_if<std::is_function<T>::value &&
                     std::is_base_of<Base, typename std::decay<Derived>::type>::value,
    decltype((std::forward<Derived>(ref).*pmf)(std::forward<Args>(args)...))>::type;
 
template <class Base, class T, class RefWrap, class... Args>
auto INVOKE(T Base::*pmf, RefWrap&& ref, Args&&... args)
 -> typename std::enable_if<std::is_function<T>::value &&
                     is_reference_wrapper<typename std::decay<RefWrap>::type>::value,
    decltype((ref.get().*pmf)(std::forward<Args>(args)...))>::type;
 
template <class Base, class T, class Pointer, class... Args>
auto INVOKE(T Base::*pmf, Pointer&& ptr, Args&&... args)
 -> typename std::enable_if<std::is_function<T>::value &&
                     !is_reference_wrapper<typename std::decay<Pointer>::type>::value &&
                     !std::is_base_of<Base, typename std::decay<Pointer>::type>::value,
    decltype(((*std::forward<Pointer>(ptr)).*pmf)(std::forward<Args>(args)...))>::type;
 
template <class Base, class T, class Derived>
auto INVOKE(T Base::*pmd, Derived&& ref)
 -> typename std::enable_if<!std::is_function<T>::value &&
                     std::is_base_of<Base, typename std::decay<Derived>::type>::value,
    decltype(std::forward<Derived>(ref).*pmd)>::type;
 
template <class Base, class T, class RefWrap>
auto INVOKE(T Base::*pmd, RefWrap&& ref)
 -> typename std::enable_if<!std::is_function<T>::value &&
                     is_reference_wrapper<typename std::decay<RefWrap>::type>::value,
    decltype(ref.get().*pmd)>::type;
 
template <class Base, class T, class Pointer>
auto INVOKE(T Base::*pmd, Pointer&& ptr)
 -> typename std::enable_if<!std::is_function<T>::value &&
                     !is_reference_wrapper<typename std::decay<Pointer>::type>::value &&
                     !std::is_base_of<Base, typename std::decay<Pointer>::type>::value,
    decltype((*std::forward<Pointer>(ptr)).*pmd)>::type;
 
template <class F, class... Args>
auto INVOKE(F&& f, Args&&... args)
 -> typename std::enable_if<!std::is_member_pointer<typename std::decay<F>::type>::value,
    decltype(std::forward<F>(f)(std::forward<Args>(args)...))>::type;
} // namespace inner_cpp17_detail
 

 
// Conforming C++14 implementation (is also a valid C++11 implementation):
namespace inner_cpp17_detail {
template <typename AlwaysVoid, typename, typename...>
struct invoke_result { };
template <typename F, typename...Args>
struct invoke_result<decltype(void(inner_cpp17_detail::INVOKE(std::declval<F>(), std::declval<Args>()...))),
                 F, Args...> {
    using type = decltype(inner_cpp17_detail::INVOKE(std::declval<F>(), std::declval<Args>()...));
};



} // namespace inner_cpp17_detail
 
 
namespace cpp17_detail {
 
template <class F, class... ArgTypes>
struct invoke_result : inner_cpp17_detail::invoke_result<void, F, ArgTypes...> {};
	
	
	
}





#endif 
