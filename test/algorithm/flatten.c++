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

// Tests for <taussig/algorithms/flatten.h++>

#include <taussig/algorithms/flatten.h++>
#include <taussig/primitives.h++>
#include <taussig/interop.h++>

#include <catch.hpp>

#include <vector>

TEST_CASE("flatten", "flatten tests") {
    std::vector<int> v1 { 1, 2, 3 };
    std::vector<int> v2 { 4, 5, 6 };
    std::vector<int> v3 { 7, 8, 9 };
    std::vector<decltype(seq::as_sequence(v1))> v {
        seq::as_sequence(v1),
        seq::as_sequence(v2),
        seq::as_sequence(v3),
    };
    auto s = seq::as_sequence(v);
    auto f = seq::flatten(s);
    std::vector<int> expected { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    auto result = seq::materialize<std::vector<int>>(f);

    REQUIRE(expected.size() == result.size());
    for(auto i = 0u; i < v.size(); ++i) {
        CHECK(expected[i] == result[i]);
    }
}


