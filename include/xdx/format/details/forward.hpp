#pragma once

#include <xdx/format/details/types.hpp>

namespace xdx
{

template <class C, class T>
format::details::String<C, T> fmt(const std::basic_string_view<C, T>&);

template <class C, class T, class... Values>
format::details::String<C, T> fmt(const std::basic_string_view<C, T>&, Values&&...);

template <class C, class T>
format::details::String<C, T> fmt(const std::basic_string_view<C, T>&, const format::details::DefNamedArguments<C, T>&);

template <template <class, class> class OStream, class C, class T>
auto print(OStream<C, T>&, const std::basic_string_view<C, T>&) -> format::details::EnableIfOStream<OStream, C, T>;

template <template <class, class> class OStream, class C, class T, class... Values>
auto print(OStream<C, T>&, const std::basic_string_view<C, T>&, Values&&...)
    -> format::details::EnableIfOStream<OStream, C, T>;

template <template <class, class> class OStream, class C, class T>
auto print(OStream<C, T>&, const std::basic_string_view<C, T>&, const format::details::DefNamedArguments<C, T>&)
    -> format::details::EnableIfOStream<OStream, C, T>;

}  // namespace xdx
