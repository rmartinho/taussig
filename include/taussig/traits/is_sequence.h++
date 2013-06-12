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

#include <wheels/meta/bool.h++>
#include <wheels/meta/depend_on.h++>
#include <wheels/meta/trait_of.h++>

namespace seq {
    namespace detail {
        struct sequence_test {
            template <typename T>
            wheels::meta::DependOn<wheels::meta::True, ValueType<T>> static test(int);
            template <typename...>
            wheels::meta::False static test(...);
        };
    } // namespace detail

    //! {trait}
    //! *Returns*: `true` if `S` is a sequence;
    //!            `false` otherwise.
    template <typename S>
    struct is_sequence : wheels::meta::TraitOf<detail::sequence_test, S> {};
} // namespace seq

#endif // TAUSSIG_TRAITS_IS_SEQUENCE_HPP
