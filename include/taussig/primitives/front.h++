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

// Sequence front() primitive

#ifndef TAUSSIG_PRIMITIVES_FRONT_HPP
#define TAUSSIG_PRIMITIVES_FRONT_HPP

#include <taussig/traits/is_sequence.h++>
#include <taussig/traits/reference_type.h++>

#include <taussig/detail/sequence_impl.h++>

#include <wheels/meta/enable_if.h++>

namespace seq {
    //! {function}
    //! *Requires*: `S` is a sequence [soft]; and `!empty(s)` [undefined].
    //! *Returns*: the first element of the sequence `s`.
    template <typename S,
              wheels::meta::EnableIf<is_sequence<S>>...>
    ReferenceType<S> front(S const& s) { return detail::sequence_impl<S>::front(s); }
} // namespace seq

#endif // TAUSSIG_PRIMITIVES_FRONT_HPP

