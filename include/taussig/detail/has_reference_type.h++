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

// Test for presence of reference type typedef

#ifndef TAUSSIG_DETAIL_HAS_REFERENCE_TYPE_HPP
#define TAUSSIG_DETAIL_HAS_REFERENCE_TYPE_HPP

#include <taussig/detail/sequence_impl.h++>

#include <wheels/meta.h++> // Bool, TraitOf

namespace seq {
    namespace detail {
        struct reference_type_test {
            template <typename T>
            wheels::Bool<true, typename sequence_impl<T>::reference> static test(int);
            template <typename>
            wheels::Bool<false> static test(...);
        };
        template <typename T>
        struct has_reference_type : wheels::TraitOf<reference_type_test, T> {};
    } // namespace detail
} // namespace seq

#endif // TAUSSIG_DETAIL_HAS_REFERENCE_TYPE_HPP
