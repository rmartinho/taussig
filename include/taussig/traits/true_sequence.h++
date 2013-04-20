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

// True sequence marker

#ifndef TAUSSIG_TRAITS_TRUE_SEQUENCE_HPP
#define TAUSSIG_TRAITS_TRUE_SEQUENCE_HPP

#include <type_traits> // true_type

namespace seq {
    //! {tag}
    //! *Effects*: marks a derived type as a sequence that provides sequence
    //!            operations directly as member functions.
    struct true_sequence {
        using is_true_sequence = std::true_type;
    };
} // namespace seq

#endif // TAUSSIG_TRAITS_TRUE_SEQUENCE_HPP
