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

// Tests for <taussig/sequence.h++>

#include <taussig/taussig.h++>

#include <catch.h++>

TEST_CASE("sequence", "sequence tests") {
    auto&& str = seq::as_sequence(u"\U00010000ab");
    REQUIRE(!seq::empty(str));
    REQUIRE(seq::front(str) == u'\xD800');
    seq::pop_front(str);
    REQUIRE(!seq::empty(str));
    REQUIRE(seq::front(str) == u'\xDC00');
    seq::pop_front(str);
    REQUIRE(!seq::empty(str));
    REQUIRE(seq::front(str) == u'a');
    seq::pop_front(str);
    REQUIRE(!seq::empty(str));
    REQUIRE(seq::front(str) == u'b');
    seq::pop_front(str);
    REQUIRE(seq::empty(str));
}
TEST_CASE("sequence_iterator", "sequence iterator tests") {
    auto&& str = seq::as_sequence(u"\U00010000ab");
    char16_t res[] = u"\xD800\xDC00" u"ab";
    int i = 0;
    for(auto it = seq::begin(str); it != seq::end(str); ++it) {
        REQUIRE(*it == res[i]);
        ++i;
    }
}
