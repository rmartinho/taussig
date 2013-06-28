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

// Source-owning sequence

#ifndef TAUSSIG_ALGORITHMS_DETAIL_SOURCE_SEQUENCE_HPP
#define TAUSSIG_ALGORITHMS_DETAIL_SOURCE_SEQUENCE_HPP

#include <taussig/primitives/empty.h++>
#include <taussig/primitives/front.h++>
#include <taussig/primitives/pop_front.h++>
#include <taussig/primitives/as_sequence.h++>
#include <taussig/traits/true_sequence.h++>
#include <taussig/traits/is_true_sequence.h++>
#include <taussig/traits/fake_sequence.h++>
#include <taussig/traits/reference_type.h++>
#include <taussig/traits/value_type.h++>

#include <wheels/meta/decay.h++>

#include <utility> // forward

namespace seq {
    namespace detail {
        template <typename Source>
        struct source_sequence : true_sequence {
        public:
            template <typename SourceF>
            source_sequence(SourceF&& source)
            : source(std::forward<SourceF>(source))
            , sequence(seq::as_sequence(this->source)) {}

            using sequence_type = wheels::meta::Decay<seq::result_of::as_sequence<Source>>;
            using reference = ReferenceType<sequence_type>;
            using value_type = ValueType<sequence_type>;

            bool empty() const {
                return seq::empty(sequence);
            }
            void pop_front() {
                seq::pop_front(sequence);
            }
            reference front() const {
                return seq::front(sequence);
            }

        private:
            wheels::meta::Decay<Source> source;
            sequence_type sequence;
        };
        static_assert(is_true_sequence<source_sequence<fake_sequence<int>>>(), "");
    } // namespace detail
} // namespace seq

#endif // TAUSSIG_ALGORITHMS_DETAIL_SOURCE_SEQUENCE_HPP

