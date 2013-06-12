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

// Sequence shift_front() algorithm

#ifndef TAUSSIG_ALGORITHMS_SHIFT_FRONT_HPP
#define TAUSSIG_ALGORITHMS_SHIFT_FRONT_HPP

#include <taussig/primitives/front.h++>
#include <taussig/primitives/pop_front.h++>
#include <taussig/traits/value_type.h++>
#include <taussig/traits/is_sequence.h++>

#include <wheels/meta/bool.h++>
#include <wheels/meta/trait_of.h++>
// EnableIf, Bool, TraitOf

#include <type_traits> // is_same
#include <cassert>

namespace seq {
    namespace detail {
        struct shift_front_test {
            template <typename T>
            std::is_same<ValueType<T>, decltype(std::declval<T>().shift_front())> static test(int);
            template <typename>
            wheels::meta::False static test(...);
        };
        template <typename T>
        struct has_shift_front : wheels::meta::TraitOf<shift_front_test, T> {};

        template <typename S,
                  bool = has_shift_front<S>()>
        struct shift_front {
            static ValueType<S> call(S& s) { return s.shift_front(); }
        };
        template <typename S>
        struct shift_front<S, false> {
            static ValueType<S> call(S& s) {
                ValueType<S> item = seq::front(s);
                seq::pop_front(s);
                return item;
            }
        };
    } // namespace detail

    //! {function}
    //! *Requires*: `S` is a sequence [soft] and `!empty(s)` [undefined].
    //! *Effects*: skips the first element of the sequence `s`.
    //! *Returns*: the value that was skipped.
    template <typename S,
              wheels::meta::EnableIf<is_sequence<S>>...>
    ValueType<S> shift_front(S& s) {
        assert(!seq::empty(s));
        detail::shift_front<S>::call(s);
    }
} // namespace seq

#endif // TAUSSIG_ALGORITHMS_SHIFT_FRONT_HPP

