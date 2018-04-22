#pragma once

#include <xdx/format/details/forward.hpp>
#include <xdx/format/details/types.hpp>

namespace xdx::format::details
{

/*
 * format_string - "blah blah blah {arg_name} blah $arg_index blah blah"
 */

template <template <class, class> class Argument, class C, class T>
struct Formater
{
    using Arg = Argument<C, T>;
    using NArgs = NamedArguments<Argument, C, T>;
    using Stream = OStream<C, T>;
    using SV = StringView<C, T>;
    template <size_t values_count>
    using IArgs = IndexedArguments<Argument, values_count, C, T>;

    static constexpr C IndexedGroupStart = '$';
    static constexpr C NamedGroupStart = '{';
    static constexpr C NamedGroupEnd = '}';
    static constexpr C Escape = '\\';

    struct Range
    {
        size_t s = 0;
        size_t e = 0;
    };

    enum RType
    {
        None,
        Any,
        Index,
        Name,
        End
    };

    static constexpr bool isany(C ch) {
        return ch != IndexedGroupStart && ch != NamedGroupStart;
    }

    static constexpr bool isdigit(C ch) {
        return '0' <= ch && ch <= '9';
    }

    static std::pair<Range, RType> next_range(const SV& sv, size_t s) {
        auto size = sv.size();
        auto start = s;
        auto end = s;

        for (; end < size && isany(sv[end]); ++end) {
        }

        if (end != start) {
            return {{start, end + 1}, Any};
        }

        if (sv[end] == Escape) {
            if ((end + 1) == size) {
                return {{start, end}, End};
            }
            return {{end + 1, end + 2}, Any};
        }

        if (sv[end] == IndexedGroupStart) {
            if ((end + 1) == size || !isdigit(sv[end + 1])) {
                return {{start, end + 1}, Any};
            }
            start = end + 1;
            for (; end < size && isdigit(sv[end]); ++end) {
            }
            return {{start, end + 1}, Index};
        }

        if (sv[end] == NamedGroupStart) {
            if ((end + 1) == size) {
                return {{start, end + 1}, Any};
            }
            if (sv[end + 1] == NamedGroupStart) {
                return {{end, end + 1}, Any};
            }
            if (sv[end + 1] == NamedGroupEnd) {
                return {{start, end + 1}, Any};
            }

            start = end + 1;
            for (; end < size && sv[end] != NamedGroupEnd; ++end) {
            }

            return {{start, end + 1}, Name};
        }

        return {{}, End};
    }

    static size_t make_index(const SV& input) {
        size_t result = 0;
        for (auto ch : input) {
            result = result * 10 + (ch - '0');
        }
        return result;
    }

    template <class... Values>
    static void do_format(Stream& stream, const SV& format_string, const NArgs& nargs, Values&&... values) {
        IArgs<sizeof...(Values)> iargs(std::forward<Values>(values)...);

        size_t start_index = 0;

        while (start_index < format_string.size()) {
            auto [range, type] = next_range(format_string, start_index);
            switch (type) {
                case End:
                    return;
                case Any:
                    stream << (format_string.substr(range.s, range.e - range.s));
                    break;
                case Name:
                    nargs.print(stream, format_string.substr(range.s, range.e - range.s - 1));
                    break;
                case Index:
                    iargs.print(stream, make_index(format_string.substr(range.s, range.e - range.s)));
                    break;
                case None:
                default:
                    break;
            }
            start_index = range.e;
        }
    }
};

}  // namespace xdx::format::details
