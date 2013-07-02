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

// Obtaining sequences

#ifndef TAUSSIG_PRIMITIVES_AS_SEQUENCE_HPP
#define TAUSSIG_PRIMITIVES_AS_SEQUENCE_HPP

#include <taussig/traits/is_true_sequence.h++>

#include <taussig/detail/iterators.h++> // has_begin_end, is_iterator_pair, ConstIteratorOf
#include <taussig/detail/characters.h++> // is_null_terminated_string

#include <wheels/meta/unqual.h++>
#include <wheels/meta/id.h++>
#include <wheels/meta/invoke.h++>
#include <wheels/meta/bool.h++>
#include <wheels/meta/trait_of.h++>
#include <wheels/meta/depend_on.h++>
#include <wheels/optional.h++>

#include <iterator> // forward_iterator_tag, begin, end
#include <utility> // forward, pair
#include <string> // char_traits
#include <cstddef> // size_t

namespace seq {
    // TODO hook for partial specialization
    template <typename S>
    struct sequence_source {};

    namespace detail {
        struct adapted_source_test {
            template <typename T>
            // TODO deal with the Unqualified bits here
            wheels::meta::DependOn<wheels::meta::True, typename sequence_source<wheels::meta::Unqual<T>>::result> static test(int);
            template <typename>
            wheels::meta::False static test(...);
        };
        template <typename T>
        struct is_adapted_source : wheels::meta::TraitOf<adapted_source_test, T> {};

        // TODO get into separate detail file
        template <typename T>
        struct is_optional : wheels::meta::False {};
        template <typename T>
        struct is_optional<wheels::optional<T>> : wheels::meta::True {};

        struct true_sequence_tag { using type = true_sequence_tag; };
        struct optional_tag { using type = optional_tag; };
        struct iterable_tag { using type = iterable_tag; };
        struct iterator_pair_tag { using type = iterator_pair_tag; };
        struct null_terminated_tag { using type = null_terminated_tag; };
        struct adapted_source_tag { using type = adapted_source_tag; };

        template <typename T,
                  bool = is_true_sequence<wheels::meta::Unqual<T>>(),
                  bool = is_optional<wheels::meta::Unqual<T>>(),
                  bool = has_begin_end<T, std::forward_iterator_tag>(),
                  bool = is_iterator_pair<T>(),
                  bool = is_null_terminated_string<wheels::meta::Unqual<T>>(),
                  bool = is_adapted_source<T>()>
        struct source_kind_of : wheels::meta::id<void> {};
        template <typename T>
        using SourceKindOf = wheels::meta::Invoke<source_kind_of<T>>;

        template <typename T, bool O, bool I, bool P, bool Z, bool A>
        struct source_kind_of<T, true, O, I, P, Z, A> : true_sequence_tag {};
        template <typename T, bool I, bool P, bool Z, bool A>
        struct source_kind_of<T, false, true, I, P, Z, A> : optional_tag {};
        template <typename T, bool O, bool I, bool P, bool Z>
        struct source_kind_of<T, false, O, I, P, Z, true> : adapted_source_tag {};
        template <typename T, bool P>
        struct source_kind_of<T, false, false, true, P, true, false> : null_terminated_tag {};
        template <typename T, bool P>
        struct source_kind_of<T, false, false, true, P, false, false> : iterable_tag {};
        template <typename T, bool Z>
        struct source_kind_of<T, false, false, false, true, Z, false> : iterator_pair_tag {};
        template <typename T>
        struct source_kind_of<T, false, false, false, false, true, false> : null_terminated_tag {};

        //! {traits}
        //! *Note*: implementation backend for `as_sequence` and `result_of::as_sequence`.
        template <typename T,
                  typename Type = SourceKindOf<T>>
        struct as_sequence_impl {};

        template <typename S>
        struct as_sequence_impl<S, true_sequence_tag> {
            using result = S;
            static result forward(S&& s) { return std::forward<S>(s); }
        };

        template <typename Optional>
        struct as_sequence_impl<Optional, optional_tag> {
            using result = Optional;
            static result forward(Optional&& o) { return std::forward<Optional>(o); }
        };

        template <typename Iterable>
        struct as_sequence_impl<Iterable, iterable_tag> {
        private:
            using iterator = ConstIteratorOf<Iterable>;
        public:
            using result = std::pair<iterator, iterator>;
            // TODO ADL begin end
            static result forward(Iterable const& r) { return { std::begin(r), std::end(r) }; }
        };

        template <typename Pair>
        struct as_sequence_impl<Pair, iterator_pair_tag> {
            using result = Pair;
            static result forward(Pair&& p) { return std::forward<Pair>(p); }
        };

        template <typename Char, std::size_t N>
        struct as_sequence_impl<Char[N], null_terminated_tag> {
            using result = std::pair<Char const*, Char const*>;
            static result forward(Char(&str)[N]) { return { str, str+N-1 }; }
        };
        template <typename Char, std::size_t N>
        struct as_sequence_impl<Char(&)[N], null_terminated_tag>
        : as_sequence_impl<Char[N], null_terminated_tag> {};
        template <typename Char>
        struct as_sequence_impl<Char*, null_terminated_tag> {
        private:
            using char_type = wheels::meta::Unqual<Char>;
        public:
            using result = std::pair<Char const*, Char const*>;
            static result forward(Char* p) { return { p, p + std::char_traits<char_type>::length(p) }; }
        };
        template <typename Char>
        struct as_sequence_impl<Char, null_terminated_tag>
        : as_sequence_impl<wheels::meta::Unqual<Char>, null_terminated_tag> {};

        // TODO deal with the Unqualified bits here
        template <typename T>
        struct as_sequence_impl<T, adapted_source_tag> : sequence_source<wheels::meta::Unqual<T>> {};
    } // namespace detail

    namespace result_of {
        //! {metafunction}
        //! *Requires*: `T` is a sequence source [soft]. TODO
        //! *Effects*: computes the result type for `seq::as_sequence`.
        //! *Returns*: `T` if `T` is a sequence type or a reference to one;
        //!            `U const(&)[N]` if `T` is a reference to an array of non-character type `U[N]`;
        //!            `Char const*` if `T` is a pointer `Char*` to a possibly `const` character type,
        //!              or if `T` is a reference to an array of character type `Char[N]`.
        template <typename T>
        using as_sequence = typename detail::as_sequence_impl<T>::result;
    } // namespace result_of

    //! {function}
    //! *Requires*: `T` is a sequence source [soft]; TODO
    //!             if `T` is a pointer type, `t` is a valid pointer to the first element of a null-terminated string [undefined].
    //! *Effects*: forwards a sequence with the normalized interface, possibly using a wrapper.
    template <typename T>
    result_of::as_sequence<T> as_sequence(T&& t) {
        return detail::as_sequence_impl<T>::forward(std::forward<T>(t));
    }
} // namespace seq

#endif // TAUSSIG_PRIMITIVES_AS_SEQUENCE_HPP
