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

// Sequence map() algorithm

#ifndef TAUSSIG_ALGORITHMS_MAP_HPP
#define TAUSSIG_ALGORITHMS_MAP_HPP

#include <taussig/primitives/empty.h++>
#include <taussig/primitives/pop_front.h++>
#include <taussig/primitives/front.h++>
#include <taussig/traits/is_true_sequence.h++>
#include <taussig/traits/true_sequence.h++>
#include <taussig/traits/reference_type.h++>
#include <taussig/traits/fake_sequence.h++>

#include <wheels/fun/result_of.h++>
#include <wheels/meta/decay.h++>

#include <utility> // forward, pair

namespace seq {
    template <typename Fun, typename Sequence>
    struct map_sequence : true_sequence {
    public:
        template <typename FunF, typename SequenceF>
        map_sequence(FunF&& fun, SequenceF&& s) : fun(std::forward<FunF>(fun)), s(std::forward<SequenceF>(s)) {}

        using reference = wheels::fun::ResultOf<Fun(ReferenceType<Sequence>)>;
        using value_type = wheels::meta::Decay<reference>;

        bool empty() const { return seq::empty(s); }
        void pop_front() { seq::pop_front(s); }
        reference front() const { return fun(seq::front(s)); }

    private:
        Fun fun;
        Sequence s;
    };
    static_assert(is_true_sequence<map_sequence<char(*)(char), fake_sequence<char>>>(), "map_sequence must be a true sequence");

    template <typename Fun, typename Sequence>
    map_sequence<Fun, Sequence> map(Fun&& fun, Sequence&& sequence) {
        return { std::forward<Fun>(fun), std::forward<Sequence>(sequence) };
    }
} // namespace seq

#endif // TAUSSIG_ALGORITHMS_MAP_HPP

