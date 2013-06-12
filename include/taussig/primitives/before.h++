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

// Sequence before() primitive

#ifndef TAUSSIG_PRIMITIVES_BEFORE_HPP
#define TAUSSIG_PRIMITIVES_BEFORE_HPP

#include <taussig/detail/sequence_impl.h++>

#include <wheels/meta/enable_if.h++>

namespace seq {
    //! {function}
    //! *Requires*: `S` is a sequence [soft]; and `part` is a subsequence of `whole` [undefined].
    //! *Returns*: a sequence with the elements of `whole` that are before the elements of `part`.
    template <typename S,
              wheels::meta::EnableIf<is_sequence<S>>...>
    S before(S const& whole, S const& part) {
        return detail::sequence_impl<S>::before(whole, part);
    }
} // namespace seq

#endif // TAUSSIG_PRIMITIVES_BEFORE_HPP
