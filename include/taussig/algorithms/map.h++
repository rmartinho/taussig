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
#include <wheels/meta/enable_if.h++>

#include <utility> // forward, pair, declval

namespace seq {
    template <typename Fun, typename Seq>
    struct map_sequence : true_sequence {
    private:
        using fun_type = wheels::meta::Decay<Fun>;
        using seq_type = wheels::meta::Decay<Seq>;
    public:
        template <typename FunF, typename SeqF>
        map_sequence(FunF&& fun, SeqF&& s)
        : fun(std::forward<FunF>(fun)), s(std::forward<SeqF>(s)) {}

        using reference = wheels::fun::ResultOf<fun_type&(ReferenceType<seq_type>)>;
        using value_type = wheels::meta::Decay<reference>;

        bool empty() const { return seq::empty(s); }
        void pop_front() { seq::pop_front(s); }
        reference front() const { return wheels::fun::invoke(fun, seq::front(s)); }

    private:
        fun_type fun;
        seq_type s;
    };
    static_assert(is_true_sequence<map_sequence<char(*)(char), fake_sequence<char>>>(), "map_sequence must be a true sequence");

    template <typename Fun, typename Seq,
              wheels::meta::EnableIf<is_sequence<Seq>>...,
              wheels::meta::EnableIf<wheels::fun::is_invocable<Fun, void(ReferenceType<Seq>)>>...,
              wheels::meta::DisableIf<std::is_void<wheels::fun::ResultOf<Fun(ReferenceType<Seq>)>>>...>
    map_sequence<Fun, Seq> map(Fun&& fun, Seq&& s) {
        return { std::forward<Fun>(fun), std::forward<Seq>(s) };
    }

    namespace result_of {
        template <typename Fun, typename Seq>
        using map = decltype(seq::map(std::declval<Fun>(), std::declval<Seq>()));
    } // namespace result_of
} // namespace seq

#endif // TAUSSIG_ALGORITHMS_MAP_HPP

