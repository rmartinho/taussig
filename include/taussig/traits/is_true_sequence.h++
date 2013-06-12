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

// True sequence tester

#ifndef TAUSSIG_TRAITS_IS_TRUE_SEQUENCE_HPP
#define TAUSSIG_TRAITS_IS_TRUE_SEQUENCE_HPP

#include <wheels/meta/all.h++>
#include <wheels/meta/bool.h++>
#include <wheels/meta/unqual.h++>
#include <wheels/meta/trait_of.h++>

#include <type_traits> // is_convertible, is_void, is_same

namespace seq {
    namespace detail {
        struct true_sequence_test {
            template <typename T>
            wheels::meta::All<
                typename wheels::meta::Unqual<T>::is_true_sequence,
                std::is_convertible<decltype(std::declval<T>().empty()), bool>,
                std::is_convertible<decltype(std::declval<T>().front()), typename T::value_type>,
                std::is_void<decltype(std::declval<T>().pop_front())>
            > static test(int);
            template <typename...>
            wheels::meta::False static test(...);
        };
    } // namespace detail

    //! {trait}
    //! *Returns*: `true` if `S` is a sequence with sequence operations as member functions;
    //!            `false` otherwise.
    template <typename T>
    using is_true_sequence = wheels::meta::TraitOf<detail::true_sequence_test, T>;
} // namespace seq

#endif // TAUSSIG_TRAITS_IS_TRUE_SEQUENCE_HPP
