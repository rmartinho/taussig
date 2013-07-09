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

// Sequence flatten() algorithm

#ifndef TAUSSIG_ALGORITHMS_FLATTEN_HPP
#define TAUSSIG_ALGORITHMS_FLATTEN_HPP

#include <taussig/primitives/empty.h++>
#include <taussig/primitives/front.h++>
#include <taussig/primitives/pop_front.h++>
#include <taussig/primitives/as_sequence.h++>
#include <taussig/traits/true_sequence.h++>
#include <taussig/traits/is_true_sequence.h++>
#include <taussig/traits/fake_sequence.h++>
#include <taussig/traits/reference_type.h++>
#include <taussig/traits/value_type.h++>

#include <taussig/detail/source_sequence.h++>

#include <wheels/fun/result_of.h++>
#include <wheels/meta/decay.h++>
#include <wheels/meta/enable_if.h++>
#include <wheels/meta/is_related.h++>
#include <wheels/optional.h++>

#include <utility> // forward, declval

namespace seq {
    template <typename Seq>
    struct flatten_sequence : true_sequence {
    private:
        using seq_type = wheels::meta::Decay<Seq>;
        using subseq_type = detail::source_sequence<ReferenceType<seq_type>>;

    public:
        template <typename SeqF,
                  wheels::meta::DisableIfRelated<SeqF, flatten_sequence<Seq>>...>
        flatten_sequence(SeqF&& s) : s(std::forward<SeqF>(s)) {}

        using reference = ReferenceType<subseq_type>;
        using value_type = wheels::meta::Decay<reference>;

        bool empty() const {
            skip_empties();
            return seq::empty(s) && current_empty();
        }
        void pop_front() {
            skip_empties();
            seq::pop_front(*current);
        }
        reference front() const {
            skip_empties();
            return seq::front(*current);
        }

    private:
        // TODO oh my mutable
        mutable wheels::optional<subseq_type> current;
        mutable seq_type s;

        bool current_empty() const {
            return !current || seq::empty(*current);
        }

        void skip_empties() const {
            while(!seq::empty(s) && current_empty()) {
                current = subseq_type(seq::front(s));
                seq::pop_front(s);
            }
        }
    };
    static_assert(is_true_sequence<flatten_sequence<fake_sequence<fake_sequence<char>>>>(), "flatten_sequence must be a true sequence");

    namespace result_of {
        template <typename Seq>
        using flatten = flatten_sequence<Seq>;
    } // namespace result_of

    template <typename Seq,
              wheels::meta::EnableIf<is_sequence<Seq>>...,
              wheels::meta::EnableIf<is_sequence<result_of::as_sequence<ReferenceType<Seq>>>>...>
    result_of::flatten<Seq> flatten(Seq&& sequence) {
        return { std::forward<Seq>(sequence) };
    }
} // namespace seq

#endif // TAUSSIG_ALGORITHMS_FLATTEN_HPP

