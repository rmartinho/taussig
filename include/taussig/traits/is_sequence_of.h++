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

// Sequence value type tester

#ifndef TAUSSIG_TRAITS_IS_SEQUENCE_OF_HPP
#define TAUSSIG_TRAITS_IS_SEQUENCE_OF_HPP

#include <taussig/traits/value_type.h++>

#include <wheels/meta.h++> // TraitOf

#include <type_traits> // is_same, false_type

namespace seq {
    namespace detail {
        struct sequence_of_test {
            template <typename T, typename U>
            std::is_same<U, ValueType<T>> static test(int);
            template <typename...>
            std::false_type static test(...);
        };
    } // namespace detail

    //! {trait}
    //! *Returns*: `true` if `S` is a sequence with values of type `V`;
    //!            `false` otherwise.
    template <typename S, typename V>
    struct is_sequence_of : wheels::TraitOf<detail::sequence_of_test, S, V> {};
} // namespace seq

#endif // TAUSSIG_TRAITS_IS_SEQUENCE_OF_HPP
