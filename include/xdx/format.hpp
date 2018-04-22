#pragma once

#include <xdx/format/details/do_format.hpp>

#include <sstream>

namespace xdx
{

template <template <class, class> class OStream, class C, class T>
auto print(OStream<C, T>& ostream, const std::basic_string_view<C, T>& fmt_string)
    -> format::details::EnableIfOStream<OStream, C, T>& {
    using Frmtr = format::details::Formater<format::details::Argument, C, T>;
    Frmtr::do_format(ostream, fmt_string, {});
    return ostream;
}

template <template <class> class OStream, class C, size_t N>
auto print(OStream<C>& ostream, const C (&fmt_string)[N]) -> format::details::EnableIfOStreamCOnly<OStream, C>& {
    using Frmtr = format::details::Formater<format::details::Argument, C, std::char_traits<C>>;
    Frmtr::do_format(ostream, fmt_string, {});
    return ostream;
}

template <template <class, class> class OStream, class C, class T, class... Values>
auto print(OStream<C, T>& ostream, const std::basic_string_view<C, T>& fmt_string, Values&&... values)
    -> format::details::EnableIfOStream<OStream, C, T>& {
    using Frmtr = format::details::Formater<format::details::Argument, C, T>;
    Frmtr::do_format(ostream, fmt_string, {}, std::forward<Values>(values)...);
    return ostream;
}

template <template <class> class OStream, class C, size_t N, class... Values>
auto print(OStream<C>& ostream, const C (&fmt_string)[N], Values&&... values)
    -> format::details::EnableIfOStreamCOnly<OStream, C>& {
    using Frmtr = format::details::Formater<format::details::Argument, C, std::char_traits<C>>;
    Frmtr::do_format(ostream, fmt_string, {}, std::forward<Values>(values)...);
    return ostream;
}

template <template <class, class> class OStream, class C, class T>
auto print(OStream<C, T>& ostream,
           const std::basic_string_view<C, T>& fmt_string,
           const format::details::DefNamedArguments<C, T>& nargs) -> format::details::EnableIfOStream<OStream, C, T>& {
    using Frmtr = format::details::Formater<format::details::Argument, C, T>;
    Frmtr::do_format(ostream, fmt_string, nargs);
    return ostream;
}

template <template <class> class OStream, class C, size_t N>
auto print(OStream<C>& ostream, const C (&fmt_string)[N], const format::details::DefNamedArguments<C>& nargs)
    -> format::details::EnableIfOStreamCOnly<OStream, C>& {
    using Frmtr = format::details::Formater<format::details::Argument, C, std::char_traits<C>>;
    Frmtr::do_format(ostream, fmt_string, nargs);
    return ostream;
}

template <class C, class T>
format::details::String<C, T> fmt(const std::basic_string_view<C, T>& fmt_string) {
    std::ostringstream ostream;
    return print(ostream, fmt_string).str();
}

template <class C, size_t N>
format::details::String<C> fmt(const C (&fmt_string)[N]) {
    std::ostringstream ostream;
    return print(ostream, std::basic_string_view<C>(fmt_string, N - 1)).str();
}

template <class C, class T, class... Values>
format::details::String<C, T> fmt(const std::basic_string_view<C, T>& fmt_string, Values&&... values) {
    std::ostringstream ostream;
    return print(ostream, fmt_string, std::forward<Values>(values)...).str();
}

template <class C, size_t N, class... Values>
format::details::String<C> fmt(const C (&fmt_string)[N], Values&&... values) {
    std::ostringstream ostream;
    return print(ostream, std::basic_string_view<C>(fmt_string, N - 1), std::forward<Values>(values)...).str();
}

template <class C, class T>
format::details::String<C, T> fmt(const std::basic_string_view<C, T>& fmt_string,
                                  const format::details::DefNamedArguments<C, T>& nargs) {
    std::ostringstream ostream;
    return print(ostream, fmt_string, nargs).str();
}

template <class C, size_t N>
format::details::String<C> fmt(const C (&fmt_string)[N], const format::details::DefNamedArguments<C>& nargs) {
    std::ostringstream ostream;
    return print(ostream, std::basic_string_view<C>(fmt_string, N - 1), nargs).str();
}

}  // namespace xdx
