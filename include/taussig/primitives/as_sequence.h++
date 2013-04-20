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

#include <wheels/meta.h++> // Unqualified, identity, Invoke, Bool, TraitOf

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
            wheels::Bool<true, typename sequence_source<wheels::Unqualified<T>>::result> static test(int);
            template <typename>
            wheels::Bool<false> static test(...);
        };
        template <typename T>
        struct is_adapted_source : wheels::TraitOf<adapted_source_test, T> {};

        struct true_sequence_tag { using type = true_sequence_tag; };
        struct iterable_tag { using type = iterable_tag; };
        struct iterator_pair_tag { using type = iterator_pair_tag; };
        struct null_terminated_tag { using type = null_terminated_tag; };
        struct adapted_source_tag { using type = adapted_source_tag; };

        template <typename T,
                  bool = is_true_sequence<wheels::Unqualified<T>>(),
                  bool = has_begin_end<T, std::forward_iterator_tag>(),
                  bool = is_iterator_pair<T>(),
                  bool = is_null_terminated_string<wheels::Unqualified<T>>(),
                  bool = is_adapted_source<T>()>
        struct source_kind_of : wheels::identity<void> {};
        template <typename T>
        using SourceKindOf = wheels::Invoke<source_kind_of<T>>;

        template <typename T, bool I, bool P, bool Z, bool A>
        struct source_kind_of<T, true, I, P, Z, A> : true_sequence_tag {};
        template <typename T, bool P, bool A>
        struct source_kind_of<T, false, true, P, true, A> : null_terminated_tag {};
        template <typename T, bool P, bool A>
        struct source_kind_of<T, false, true, P, false, A> : iterable_tag {};
        template <typename T, bool Z, bool A>
        struct source_kind_of<T, false, false, true, Z, A> : iterator_pair_tag {};
        template <typename T, bool A>
        struct source_kind_of<T, false, false, false, true, A> : null_terminated_tag {};
        template <typename T>
        struct source_kind_of<T, false, false, false, false, true> : adapted_source_tag {};

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
            using char_type = wheels::Unqualified<Char>;
        public:
            using result = std::pair<Char const*, Char const*>;
            static result forward(Char* p) { return { p, p + std::char_traits<char_type>::length(p) }; }
        };
        template <typename Char>
        struct as_sequence_impl<Char, null_terminated_tag>
        : as_sequence_impl<wheels::Unqualified<Char>, null_terminated_tag> {};

        // TODO deal with the Unqualified bits here
        template <typename T>
        struct as_sequence_impl<T, adapted_source_tag> : sequence_source<wheels::Unqualified<T>> {};
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
