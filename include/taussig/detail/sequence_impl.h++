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

// Sequence implementation

#ifndef TAUSSIG_DETAIL_SEQUENCE_IMPL_HPP
#define TAUSSIG_DETAIL_SEQUENCE_IMPL_HPP

#include <taussig/traits/is_true_sequence.h++>

#include <taussig/detail/iterators.h++> // IteratorValueType, IteratorReferenceType

#include <wheels/meta/unqual.h++>

#include <utility> // pair

namespace seq {
    namespace detail {
        template <typename S,
                bool = is_true_sequence<S>()>
        struct sequence_impl_unqual {};

        template <typename S>
        struct sequence_impl_unqual<S, true> {
            using value_type = typename S::value_type;
            using reference = typename S::reference; // TODO make reference optional

            static bool empty(S const& s) { return s.empty(); }
            static reference front(S const& s) { return s.front(); }
            static void pop_front(S& s) { s.pop_front(); }
            static S before(S const& whole, S const& part) { whole.before(part); }
        };

        template <typename I>
        struct sequence_impl_unqual<std::pair<I, I>, false> {
            using value_type = IteratorValueType<I>;
            using reference = IteratorReferenceType<I>;

            static bool empty(std::pair<I, I> const& p) { return p.first == p.second; }
            static reference front(std::pair<I, I> const& p) { return *p.first; }
            static void pop_front(std::pair<I, I>& p) { ++p.first; }
            static std::pair<I, I> before(std::pair<I, I> const& whole, std::pair<I, I> const& part) {
                return { whole.first, part.first };
            }
        };
        template <typename S>
        struct sequence_impl : sequence_impl_unqual<wheels::meta::Unqual<S>> {};
    } // namespace detail
} // namespace seq

#endif // TAUSSIG_DETAIL_SEQUENCE_IMPL_HPP

