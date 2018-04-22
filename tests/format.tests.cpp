#include <gtest/gtest.h>

#include <xdx/format.hpp>

TEST(xdx_format_tests, no_args) {
    using namespace std;
    ASSERT_EQ("some string without args", xdx::fmt("some string without args"sv));
}
