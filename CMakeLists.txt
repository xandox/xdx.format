cmake_minimum_required(VERSION 3.10)

include($ENV{XDX_CMAKE_ROOT}/xdx.cmake)

xdx_interface_begin(
    NAME xdx.format
    NAMESPACE xdx::format
)

xdx_project_add_headers(
    ../format.hpp
    details/types.hpp
    details/do_format.hpp
    details/forward.hpp
    details/types.impl.hpp
)

xdx_project_add_tests(
    format.tests.cpp
)

xdx_interface_end()

