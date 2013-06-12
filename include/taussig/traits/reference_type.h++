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

// Sequence reference type trait

#ifndef TAUSSIG_TRAITS_REFERENCE_TYPE_HPP
#define TAUSSIG_TRAITS_REFERENCE_TYPE_HPP

#include <taussig/detail/has_reference_type.h++>
#include <taussig/detail/sequence_impl.h++>

#include <wheels/meta/invoke.h++>

namespace seq {
    namespace detail {
        template <typename S,
                  bool = has_reference_type<S>()>
        struct reference_type {};

        template <typename S>
        struct reference_type<S, true> {
            using type = typename sequence_impl<S>::reference;
        };
    } // namespace detail

    //! {metafunction}
    //! *Requires*: `S` is a sequence [soft].
    //! *Returns*: the type of references to values in the sequence `S`.
    //! *Note*: this can be a non-reference type for non-persistent sequences.
    template <typename S>
    struct reference_type : detail::reference_type<S> {};

    template <typename S>
    using ReferenceType = wheels::meta::Invoke<reference_type<S>>;
} // namespace seq

#endif // TAUSSIG_TRAITS_REFERENCE_TYPE_HPP

