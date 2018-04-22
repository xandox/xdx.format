#pragma once

#include <xdx/format/details/forward.hpp>
#include <xdx/format/details/types.hpp>

namespace xdx::format::details
{

template <template <class, class> class Argument, size_t arguments_count, class C, class T>
void IndexedArguments<Argument, arguments_count, C, T>::print(Stream& stream, size_t idx) const {
    if (idx >= arguments_count) {
        throw std::invalid_argument(fmt("argument index '{index}' out of range", {{"index", idx}}));
    }
    args_[idx].print(stream);
}

template <template <class, class> class Argument, class C, class T>
void NamedArguments<Argument, C, T>::print(Stream& stream, const SV& name) const {
    const auto it = map_.find(name);
    if (it == map_.end()) {
        throw std::invalid_argument(fmt("value for named argument '{name}' not set", {{"name", name}}));
    }
    it->second.print(stream);
}
}  // namespace xdx::format::details
