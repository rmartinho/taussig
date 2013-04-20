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

// Sequence value type trait

#ifndef TAUSSIG_TRAITS_VALUE_TYPE_HPP
#define TAUSSIG_TRAITS_VALUE_TYPE_HPP

#include <taussig/detail/has_value_type.h++>
#include <taussig/detail/sequence_impl.h++>

#include <wheels/meta.h++> // Invoke

namespace seq {
    namespace detail {
        template <typename S,
                  bool = has_value_type<S>()>
        struct value_type {};

        template <typename S>
        struct value_type<S, true> {
            using type = typename sequence_impl<S>::value_type;
        };
    } // namespace detail

    //! {metafunction}
    //! *Requires*: `S` is a sequence [soft].
    //! *Returns*: the type of values in the sequence `S`.
    template <typename S>
    struct value_type : detail::value_type<S> {};

    template <typename S>
    using ValueType = wheels::Invoke<value_type<S>>;
} // namespace seq

#endif // TAUSSIG_TRAITS_VALUE_TYPE_HPP
