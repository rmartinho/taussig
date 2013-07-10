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

// Materialization of sequences into containers

#ifndef TAUSSIG_INTEROP_MATERIALIZE_HPP
#define TAUSSIG_INTEROP_MATERIALIZE_HPP

#include <taussig/traits/is_sequence.h++>
#include <taussig/traits/value_type.h++>

#include <taussig/interop/begin_end.h++>

#include <wheels/meta/enable_if.h++>
#include <wheels/meta/is_deduced.h++>

#include <utility> // forward

namespace seq {
    //! {function}
    //! *Requires*: `S` is a sequence [soft];
    //!             `C` is a container.
    //! *Returns*: a `C` container with all elements from the sequence.
    template <typename C,
              typename S,
              wheels::meta::EnableIf<is_sequence<S>>...>
    C materialize(S&& s) {
        // asymmetry in forward because end doesn't use the argument, and only begin owns it
        return C(seq::begin(std::forward<S>(s)), seq::end(s));
    }

    //! {function}
    //! *Requires*: `S` is a sequence [soft];
    //!             `C<seq::ValueType<S>>` is a container.
    //! *Returns*: a `C` container with all elements from the sequence.
    template <template <typename...> class C,
              typename S,
              wheels::meta::EnableIf<is_sequence<S>>...>
    C<ValueType<S>> materialize(S&& s) {
        return materialize<C<ValueType<S>>>(std::forward<S>(s));
    }

    namespace detail {
        template <typename S>
        struct materializer {
            template <typename C> // TODO require container
            operator C() const {
                return materialize<C>(std::forward<S>(sequence));
            }

            S& sequence;
        };
    } // namespace detail

    //! {function}
    //! *Requires*: `S` is a sequence [soft].
    //! *Returns*: a proxy implicitly convertible to container types;
    //!            converting the proxy results in a container with all elements from the sequence.
    template <typename C = wheels::meta::deduced,
              typename S,
              wheels::meta::EnableIf<wheels::meta::is_deduced<C>>...,
              wheels::meta::EnableIf<is_sequence<S>>...>
    detail::materializer<S> materialize(S&& s) {
        return { s }; // no forwarding because a reference is stored directly
    }
} // namespace seq

#endif // TAUSSIG_INTEROP_MATERIALIZE_HPP

