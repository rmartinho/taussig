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

// Sequence flat_map() algorithm

#ifndef TAUSSIG_ALGORITHMS_FLAT_MAP_HPP
#define TAUSSIG_ALGORITHMS_FLAT_MAP_HPP

#include <taussig/algorithms/flatten.h++>
#include <taussig/algorithms/map.h++>

#include <utility> // declval

namespace seq {
    template <typename Fun, typename Seq>
    auto flat_map(Fun&& fun, Seq&& s)
    -> decltype(seq::flatten(seq::map(std::forward<Fun>(fun), std::forward<Seq>(s)))) {
        return seq::flatten(seq::map(std::forward<Fun>(fun), std::forward<Seq>(s)));
    }

    namespace result_of {
        template <typename Fun, typename Seq>
        using flat_map = decltype(seq::flat_map(std::declval<Fun>(), std::declval<Seq>()));
    } // namespace result_of
} // namespace seq

#endif // TAUSSIG_ALGORITHMS_FLATTEN_HPP


