cmake_minimum_required(VERSION 3.10)

include($ENV{XDX_CMAKE_ROOT}/xdx.cmake)

xdx_project(
    TYPE interface
    NAME xdx.format
    NAMESPACE xdx::format
    HEADERS
        details/types.hpp
        details/forward.hpp
        details/do_format.hpp
        ../format.hpp
    TESTS
        format.tests.cpp
)
