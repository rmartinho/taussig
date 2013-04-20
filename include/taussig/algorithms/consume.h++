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

// Sequence consume() algorithm

#ifndef TAUSSIG_ALGORITHMS_CONSUME_HPP
#define TAUSSIG_ALGORITHMS_CONSUME_HPP

#include <taussig/primitives/empty.h++>
#include <taussig/primitives/pop_front.h++>
#include <taussig/traits/is_sequence.h++>

#include <wheels/meta.h++> // EnableIf

namespace seq {
    //! {function}
    //! *Requires*: `S` is a sequence [soft].
    //! *Effects*: skips elements from the sequence `s` until it is empty.
    template <typename S,
              wheels::EnableIf<is_sequence<S>>...>
    void consume(S& s) {
        while(!seq::empty(s)) {
            seq::pop_front(s);
        }
    }
} // namespace seq

#endif // TAUSSIG_ALGORITHMS_CONSUME_HPP
