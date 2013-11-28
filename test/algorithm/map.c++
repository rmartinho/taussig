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

// Tests for <taussig/algorithms/map.h++>

#include <taussig/algorithms/map.h++>
#include <taussig/primitives.h++>
#include <taussig/interop.h++>

#include <catch.hpp>

#include <vector>
#include <type_traits>

TEST_CASE("map", "map tests") {
    std::vector<int> v { 1, 2, 3, 4, 5 };
    auto s = seq::as_sequence(v);
    auto m = seq::map([](int x) { return 2.0*x; }, s);
    auto result = seq::materialize<std::vector<double>>(m);

    REQUIRE(v.size() == result.size());
    for(auto i = 0u; i < v.size(); ++i) {
        CHECK((v[i]*2.0) == result[i]);
    }
}

