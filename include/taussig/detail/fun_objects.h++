// Taussig
//
// Written in 2013 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// Polymorphic function objects and traits

#ifndef TAUSSIG_DETAIL_FUN_OBJECTS_HPP
#define TAUSSIG_DETAIL_FUN_OBJECTS_HPP

#include <wheels/meta.h++> // TraitOf

#include <type_traits> // is_convertible, false_type
#include <utility> // forward, declval

namespace seq {
    namespace detail {
        struct equal_to {
            template <typename T, typename U>
            bool operator()(T&& t, U&& u) const {
                return std::forward<T>(t) == std::forward<U>(u);
            }
        };

        struct predicate_test {
            template <typename T, typename... Args>
            std::is_convertible<decltype(std::declval<T>()(std::declval<Args>()...)), bool> static test(int);
            template <typename...>
            std::false_type static test(...);
        };
        template <typename T, typename... Args>
        struct is_predicate : wheels::TraitOf<predicate_test, T, Args...> {};
    } // namespace detail
} // namespace seq

#endif // TAUSSIG_DETAIL_FUN_OBJECTS_HPP

