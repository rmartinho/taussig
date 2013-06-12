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

// Sequence equal() algorithm

#ifndef TAUSSIG_ALGORITHMS_EQUAL_HPP
#define TAUSSIG_ALGORITHMS_EQUAL_HPP

#include <taussig/primitives/empty.h++>
#include <taussig/primitives/front.h++>
#include <taussig/primitives/pop_front.h++>

#include <taussig/traits/is_sequence.h++>
#include <taussig/traits/reference_type.h++>

#include <taussig/detail/fun_objects.h++>

#include <wheels/meta/enable_if.h++>

namespace seq {
    //! {function}
    //! *Requires*: `S` and `R` are sequences [soft], and `Pred` is a predicate [soft].
    //! *Returns*: `true` if `s` and `r` have all the same elements in the same order,
    //!              under the equivalence relation defined by `pred`;
    //!            `false` otherwise.
    template <typename S, typename R, typename Pred,
              wheels::meta::EnableIf<is_sequence<S>, is_sequence<R>>...,
              wheels::meta::EnableIf<detail::is_predicate<Pred, ReferenceType<S>, ReferenceType<R>>>...>
    bool equal(S s, R r, Pred&& pred) {
        while(!seq::empty(s) && !seq::empty(r)) {
            if(!pred(seq::front(s),seq::front(r))) return false;
            seq::pop_front(s);
            seq::pop_front(r);
        }
        return seq::empty(s) == seq::empty(r);
    }
    //! {function}
    //! *Requires*: `S` and `R` are sequences [soft] and their elements are comparable.
    //! *Returns*: `true` if `s` and `r` have all the same elements in the same order,
    //!              according to operator==;
    //!            `false` otherwise.
    template <typename S, typename R,
              wheels::meta::EnableIf<is_sequence<S>, is_sequence<R>>...>
    bool equal(S&& s, R&& r) {
        return seq::equal(std::forward<S>(s), std::forward<R>(r), detail::equal_to{});
    }
} // namespace seq

#endif // TAUSSIG_ALGORITHMS_EQUAL_HPP

