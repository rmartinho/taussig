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

// Sequence archetype

#ifndef TAUSSIG_TRAITS_FAKE_SEQUENCE_HPP
#define TAUSSIG_TRAITS_FAKE_SEQUENCE_HPP

#include <type_traits> // true_type

namespace seq {
    template <typename T>
    struct fake_sequence {
        using is_true_sequence = std::true_type;

        using value_type = T;
        using reference = T;

        bool empty() const;
        void pop_front();
        reference front() const;
    };
} // namespace seq

#endif // TAUSSIG_TRAITS_TRUE_SEQUENCE_HPP

