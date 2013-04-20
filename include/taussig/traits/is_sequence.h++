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

// Sequence tester

#ifndef TAUSSIG_TRAITS_IS_SEQUENCE_HPP
#define TAUSSIG_TRAITS_IS_SEQUENCE_HPP

#include <taussig/traits/value_type.h++>

#include <wheels/meta.h++> // Bool, TraitOf

namespace seq {
    namespace detail {
        struct sequence_test {
            template <typename T>
            wheels::Bool<true, ValueType<T>> static test(int);
            template <typename...>
            wheels::Bool<false> static test(...);
        };
    } // namespace detail

    //! {trait}
    //! *Returns*: `true` if `S` is a sequence;
    //!            `false` otherwise.
    template <typename S>
    struct is_sequence : wheels::TraitOf<detail::sequence_test, S> {};
} // namespace seq

#endif // TAUSSIG_TRAITS_IS_SEQUENCE_HPP
