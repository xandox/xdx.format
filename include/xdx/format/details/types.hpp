#pragma once

#include <functional>
#include <initializer_list>
#include <map>
#include <ostream>
#include <string>
#include <string_view>

namespace xdx::format::details
{

template <class C, class T = std::char_traits<C>>
using OStream = std::basic_ostream<C, T>;

template <template <class, class> class Stream, class C, class T = std::char_traits<C>>
using EnableIfOStream = std::enable_if_t<std::is_base_of<OStream<C, T>, Stream<C, T>>::value, Stream<C, T>>;

template <template <class> class Stream, class C>
using EnableIfOStreamCOnly = std::enable_if_t<std::is_base_of<OStream<C>, Stream<C>>::value, Stream<C>>;

template <class C, class T = std::char_traits<C>>
using StringView = std::basic_string_view<C, T>;

template <class C, class T = std::char_traits<C>, class A = std::allocator<C>>
using String = std::basic_string<C, T, A>;

template <class C, class T = std::char_traits<C>>
struct Argument
{
    using Stream = OStream<C, T>;
    using Print = std::function<void(Stream&)>;

    template <class U>
    Argument(U&& u)
        : print([v = std::forward<U>(u)](Stream& s) { s << v; }) {
    }

    Print print;
};

template <template <class, class> class Argument, size_t arguments_count, class C, class T = std::char_traits<C>>
class IndexedArguments
{
public:
    using Arg = Argument<C, T>;
    using Stream = typename Arg::Stream;

    IndexedArguments() = default;

    template <class... Values>
    IndexedArguments(Values&&... values)
        : args_{Arg{std::forward<Values>(values)}...} {
    }

    static constexpr size_t count() {
        return arguments_count;
    }

    void print(Stream& stream, size_t idx) const;

private:
    std::array<Arg, arguments_count> args_;
};

template <template <class, class> class Argument, class C, class T = std::char_traits<C>>
struct NamedArguments
{
public:
    using Arg = Argument<C, T>;
    using Stream = typename Arg::Stream;
    using SV = StringView<C, T>;
    using Map = std::map<SV, Arg>;
    using VT = typename Map::value_type;

public:
    NamedArguments() = default;

    NamedArguments(const std::initializer_list<VT>& values)
        : map_{values} {
    }

    void print(Stream& stream, const SV& name) const;

    bool has(const SV& name) const {
        return map_.find(name) != map_.end();
    }

private:
    Map map_;
};

template <size_t arguments_count, class C, class T = std::char_traits<C>>
using DefIndexedArguments = IndexedArguments<Argument, arguments_count, C, T>;

template <class C, class T = std::char_traits<C>>
using DefNamedArguments = NamedArguments<Argument, C, T>;

}  // namespace xdx::format::details
