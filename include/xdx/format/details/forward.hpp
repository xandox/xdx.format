#pragma once

#include <xdx/format/details/types.hpp>

namespace xdx
{

template <template <class, class> class OStream, class C, class T>
auto print(OStream<C, T>& ostream, const std::basic_string_view<C, T>& fmt_string)
    -> format::details::EnableIfOStream<OStream, C, T>&;

template <template <class> class OStream, class C, size_t N>
auto print(OStream<C>& ostream, const C (&fmt_string)[N]) -> format::details::EnableIfOStreamCOnly<OStream, C>&;

template <template <class, class> class OStream, class C, class T, class... Values>
auto print(OStream<C, T>& ostream, const std::basic_string_view<C, T>& fmt_string, Values&&... values)
    -> format::details::EnableIfOStream<OStream, C, T>&;

template <template <class> class OStream, class C, size_t N, class... Values>
auto print(OStream<C>& ostream, const C (&fmt_string)[N], Values&&... values)
    -> format::details::EnableIfOStreamCOnly<OStream, C>&;

template <template <class, class> class OStream, class C, class T>
auto print(OStream<C, T>& ostream,
           const std::basic_string_view<C, T>& fmt_string,
           const format::details::DefNamedArguments<C, T>& nargs) -> format::details::EnableIfOStream<OStream, C, T>&;

template <template <class> class OStream, class C, size_t N>
auto print(OStream<C>& ostream, const C (&fmt_string)[N], const format::details::DefNamedArguments<C>& nargs)
    -> format::details::EnableIfOStreamCOnly<OStream, C>&;

template <class C, class T>
format::details::String<C, T> fmt(const std::basic_string_view<C, T>& fmt_string);

template <class C, size_t N>
format::details::String<C> fmt(const C (&fmt_string)[N]);

template <class C, class T, class... Values>
format::details::String<C, T> fmt(const std::basic_string_view<C, T>& fmt_string, Values&&... values);

template <class C, size_t N, class... Values>
format::details::String<C> fmt(const C (&fmt_string)[N], Values&&... values);

template <class C, class T>
format::details::String<C, T> fmt(const std::basic_string_view<C, T>& fmt_string,
                                  const format::details::DefNamedArguments<C, T>& nargs);

template <class C, size_t N>
format::details::String<C> fmt(const C (&fmt_string)[N], const format::details::DefNamedArguments<C>& nargs);

}  // namespace xdx
