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

// Tests for <taussig/algorithms/generate.h++>

#include <taussig/algorithms/generate.h++>
#include <taussig/primitives.h++>
#include <taussig/interop.h++>

#include <wheels/optional.h++>

#include <catch.h++>

#include <vector>
#include <tuple>
#include <type_traits>

TEST_CASE("generate", "generate tests") {
    auto gene = [](int n) {
        return n < 10? wheels::optional<std::tuple<int, int>>(std::make_tuple(n, n+1)) : wheels::none;
    };
    auto s = seq::generate(gene, 0);
    std::vector<int> v = seq::materialize(s);
    std::vector<int> result { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    REQUIRE(v.size() == result.size());
    for(auto i = 0u; i < result.size(); ++i) {
        CHECK(v[i] == result[i]);
    }
}

