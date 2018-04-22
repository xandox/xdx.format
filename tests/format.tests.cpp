#include <gtest/gtest.h>

#include <xdx/format.hpp>

TEST(xdx_format_tests, no_args) {
    ASSERT_EQ("some string without args", xdx::fmt("some string without args"));
}

TEST(xdx_format_tests, special_chars_dollar_without_digits) {
    ASSERT_EQ("some string with $ special char", xdx::fmt("some string with $ special char"));
}

TEST(xdx_format_tests, special_chars_dollar_with_escape) {
    ASSERT_EQ("some string with $10 special char", xdx::fmt("some string with \\$10 special char"));
}

TEST(xdx_format_tests, special_chars_double_brace) {
    ASSERT_EQ("some string with { special char", xdx::fmt("some string with {{ special char"));
}

TEST(xdx_format_tests, special_chars_double_brace_escape) {
    ASSERT_EQ("some string with {name arg} special char", xdx::fmt("some string with {{name arg} special char"));
}

TEST(xdx_format_tests, special_chars_brace_escape) {
    ASSERT_EQ("some string with {name arg} special char", xdx::fmt("some string with \\{name arg} special char"));
}

TEST(xdx_format_tests, special_chars_empty_braces) {
    ASSERT_EQ("some string with {} special char", xdx::fmt("some string with {} special char"));
}

TEST(xdx_format_tests, indexed_arguments) {
    ASSERT_EQ("1 2 3", xdx::fmt("$0 $1 $2", 1, 2, 3));
}

TEST(xdx_format_tests, indexed_arguments_all_the_same) {
    ASSERT_EQ("1 1 1", xdx::fmt("$0 $0 $0", 1, 2, 3));
}

TEST(xdx_format_tests, indexed_arguments_reorder) {
    ASSERT_EQ("3 2 1", xdx::fmt("$2 $1 $0", 1, 2, 3));
}

TEST(xdx_format_tests, indexed_arguments_out_of_range) {
    ASSERT_THROW(xdx::fmt("$2 $1 $10", 1, 2, 3), std::invalid_argument);
}

TEST(xdx_format_tests, named_arguments) {
    ASSERT_EQ("1 2 3", xdx::fmt("{0} {1} {2}", {{"0", 1}, {"1", 2}, {"2", 3}}));
}

TEST(xdx_format_tests, named_arguments_name_is_any_string) {
    ASSERT_EQ("1 2 3", xdx::fmt("{with spaces} {\r\n} {   }", {{"with spaces", 1}, {"\r\n", 2}, {"   ", 3}}));
}

TEST(xdx_format_tests, named_arguments_all_the_same) {
    ASSERT_EQ("1 1 1", xdx::fmt("{0} {0} {0}", {{"0", 1}, {"1", 2}, {"2", 3}}));
}

TEST(xdx_format_tests, named_arguments_reorder) {
    ASSERT_EQ("3 2 1", xdx::fmt("{2} {1} {0}", {{"0", 1}, {"1", 2}, {"2", 3}}));
}

TEST(xdx_format_tests, named_arguments_out_of_range) {
    ASSERT_THROW(xdx::fmt("{2} {1} {unknown_arg}", {{"0", 1}, {"1", 2}, {"2", 3}}), std::invalid_argument);
}
