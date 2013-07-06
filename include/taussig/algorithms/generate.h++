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

// Sequence generate() algorithm

#ifndef TAUSSIG_ALGORITHMS_GENERATE_HPP
#define TAUSSIG_ALGORITHMS_GENERATE_HPP

#include <wheels/adl/get.h++>
#include <wheels/fun/result_of.h++>
#include <wheels/meta/decay.h++>
//#include <wheels/tuple.h++>

#include <taussig/traits/true_sequence.h++>
#include <taussig/traits/value_type.h++>

#include <tuple> // tuple_element
#include <utility> // forward

namespace seq {
    template <typename Fun, typename State>
    struct generate_sequence : true_sequence {
    private:
        using Result = wheels::fun::ResultOf<Fun&(State)>;

    public:
        template <typename FunF, typename StateF>
        generate_sequence(FunF&& fun, StateF&& seed)
        : fun(std::forward<FunF>(fun)), result(wheels::fun::invoke(fun, std::forward<StateF>(seed))) {}

        using reference = typename std::tuple_element<0, ValueType<Result>>::type;
        using value_type = wheels::meta::Decay<reference>;

        bool empty() const {
            return !result;
        }
        reference front() const {
            return wheels::adl::get<0>(*result);
        }
        void pop_front() {
            result = wheels::fun::invoke(fun, wheels::adl::get<1>(std::move(*result)));
        }

    private:
        Fun fun;
        Result result;
    };

    namespace result_of {
        template <typename Fun, typename Seed>
        using generate = generate_sequence<wheels::meta::Decay<Fun>, Seed>;
    } // namespace result_of

    template <typename Fun, typename Seed>
    result_of::generate<Fun, Seed> generate(Fun&& fun, Seed&& seed) {
        return { std::forward<Fun>(fun), std::forward<Seed>(seed) };
    }
} // namespace seq

#endif // TAUSSIG_ALGORITHMS_GENERATE_HPP

