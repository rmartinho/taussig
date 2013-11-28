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

// Tests for <taussig/algorithms/flat_map.h++>

#include <taussig/algorithms/flat_map.h++>
#include <taussig/primitives.h++>
#include <taussig/interop.h++>

#include <catch.hpp>

#include <vector>

TEST_CASE("flat_map", "flat_map tests") {
    auto f = [](int i) { return std::vector<int>{ i*3+1, i*3+2, i*3+3 }; };
    std::vector<int> v { 0, 1, 2 };
    auto s = seq::as_sequence(v);
    auto r = seq::flat_map(f, s);
    std::vector<int> expected { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std::vector<int> result = seq::materialize(r);

    REQUIRE(expected.size() == result.size());
    for(auto i = 0u; i < v.size(); ++i) {
        CHECK(expected[i] == result[i]);
    }
}

