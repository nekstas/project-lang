#include <catch2/catch_test_macros.hpp>

#include "../../../src/lib/regex/algo/dfa/builder.h"
#include "../../../src/lib/regex/algo/dfa/matcher.h"
#include "../../../src/lib/regex/algo/nfa/matcher.h"
#include "../../../src/lib/regex/compiler/compiler.h"
#include "../../../src/lib/regex/errors.h"
#include "../../../src/lib/regex/parser/parser.h"
#include "../../../src/lib/regex/visitors/nfa_builder.h"
#include "catch2/catch_template_test_macros.hpp"

namespace Catch {  // NOLINT

template <>
struct StringMaker<lib::regex::algo::Matcher::Result> {
    static std::string convert(lib::regex::algo::Matcher::Result const& result) {  // NOLINT
        if (!result.matched) {
            return utils::FormatStream{} << "Result{matched=false}";
        }
        return utils::FormatStream{} << "Result{matched=true,length=" << result.length
                                     << ",final_id=" << result.final_id << "}";
    }
};
}  // namespace Catch

namespace {

using Result = lib::regex::algo::Matcher::Result;

TEMPLATE_TEST_CASE("lib::regex::algo::Matcher implementations", "", lib::regex::algo::nfa::Matcher,
    lib::regex::algo::dfa::Matcher) {
    lib::regex::Compiler compiler;
    auto match = [&compiler](
                     const std::initializer_list<std::string> regexes, const std::string& code) {
        compiler.Clear();
        size_t i = 0;
        for (const auto& regex : regexes) {
            size_t final_id = compiler.AddRegex(regex);
            REQUIRE(final_id == i);
            ++i;
        }
        if constexpr (std::is_same_v<TestType, lib::regex::algo::nfa::Matcher>) {
            return TestType(compiler.CompileToNfa()).Match(code);
        } else {
            return TestType(compiler.CompileToDfa()).Match(code);
        }
    };

    SECTION("Basic") {
        REQUIRE(match({"a"}, "a") == Result{true, 1, 0});
        REQUIRE(match({"abc"}, "abc") == Result{true, 3, 0});
        REQUIRE(match({"a"}, "abc") == Result{true, 1, 0});
    }

    SECTION("Zero or one repeat") {
        REQUIRE(match({"a?"}, "abc") == Result{true, 1, 0});
        REQUIRE(match({"a?"}, "") == Result{true, 0, 0});
        REQUIRE(match({"a?"}, "b") == Result{true, 0, 0});
    }

    SECTION("Zero or more repeat") {
        REQUIRE(match({"a*"}, "") == Result{true, 0, 0});
        REQUIRE(match({"a*"}, "a") == Result{true, 1, 0});
        REQUIRE(match({"a*"}, "aaaaa") == Result{true, 5, 0});
        REQUIRE(match({"a*"}, "b") == Result{true, 0, 0});
    }

    SECTION("One or more repeat") {
        REQUIRE(match({"a+"}, "") == Result{false});
        REQUIRE(match({"a+"}, "b") == Result{false});
        REQUIRE(match({"a+"}, "a") == Result{true, 1, 0});
        REQUIRE(match({"a+"}, "aaaaa") == Result{true, 5, 0});
    }

    SECTION("Alternative") {
        REQUIRE(match({"(a|b)"}, "") == Result{false});
        REQUIRE(match({"(a|b)"}, "a") == Result{true, 1, 0});
        REQUIRE(match({"(a|b)"}, "b") == Result{true, 1, 0});
    }

    SECTION("Max prefix") {
        REQUIRE(match({"a", "abc"}, "abc") == Result{true, 3, 1});
    }

    SECTION("Is prefix") {
        REQUIRE(match({"a"}, "ba") == Result{false});
    }

    SECTION("Min final_id") {
        REQUIRE(match({"aa", "a+"}, "abb") == Result{true, 1, 1});
        REQUIRE(match({"aa", "a+"}, "aab") == Result{true, 2, 0});
        REQUIRE(match({"(ab)?(cd)?e?", "a?(bc)?(de)?"}, "") == Result{true, 0, 0});
        REQUIRE(match({"(ab)?(cd)?e?", "a?(bc)?(de)?"}, "a") == Result{true, 1, 1});
        REQUIRE(match({"(ab)?(cd)?e?", "a?(bc)?(de)?"}, "ab") == Result{true, 2, 0});
        REQUIRE(match({"(ab)?(cd)?e?", "a?(bc)?(de)?"}, "abc") == Result{true, 3, 1});
        REQUIRE(match({"(ab)?(cd)?e?", "a?(bc)?(de)?"}, "abcd") == Result{true, 4, 0});
        REQUIRE(match({"(ab)?(cd)?e?", "a?(bc)?(de)?"}, "abcde") == Result{true, 5, 0});
    }

    SECTION("Not only first and last results") {
        REQUIRE(match({"a", "abc", "abcde"}, "") == Result{false});
        REQUIRE(match({"a", "abc", "abcde"}, "a") == Result{true, 1, 0});
        REQUIRE(match({"a", "abc", "abcde"}, "abc") == Result{true, 3, 1});
        REQUIRE(match({"a", "abc", "abcde"}, "abcde") == Result{true, 5, 2});
        REQUIRE(match({"a", "abc", "abcde"}, "abcdefg") == Result{true, 5, 2});
    }

    SECTION("Difficult example") {
        const std::string regexp = "(https?://)?example\\.(com|ru|org)(/(example|a+))*";
        REQUIRE(match({regexp}, "example.com") == Result{true, 11, 0});
        REQUIRE(match({regexp}, "http://example.com") == Result{true, 18, 0});
        REQUIRE(match({regexp}, "https://example.com") == Result{true, 19, 0});
        REQUIRE(match({regexp}, "https://example.ru") == Result{true, 18, 0});
        REQUIRE(match({regexp}, "https://example.org") == Result{true, 19, 0});
        REQUIRE(match({regexp}, "https://example.org/a") == Result{true, 21, 0});
        REQUIRE(match({regexp}, "https://example.org/aaaaa") == Result{true, 25, 0});
        REQUIRE(match({regexp}, "https://example.org/example") == Result{true, 27, 0});
        REQUIRE(match({regexp}, "https://example.org/example/a/a/aaa") == Result{true, 35, 0});
        REQUIRE(match({regexp}, "http://example.org/example/a/a/aaa is a website.") ==
                Result{true, 34, 0});
    }

    SECTION("UTF-8 example") {
        REQUIRE(match({"а"}, "а") == Result{true, 2, 0});
        REQUIRE(match({"Привет, мир!"}, "Привет, мир!") == Result{true, 21, 0});
        REQUIRE(match({"а*ба+"}, "ба") == Result{true, 4, 0});
        REQUIRE(match({"а*ба+"}, "аба") == Result{true, 6, 0});
        REQUIRE(match({"а*ба+"}, "абааа") == Result{true, 10, 0});
        REQUIRE(match({"а*ба+"}, "ааабааа") == Result{true, 14, 0});
    }

    SECTION("Useless token regexp") {
        if constexpr (std::is_same_v<TestType, lib::regex::algo::dfa::Matcher>) {
            REQUIRE_THROWS_AS(match({"a+", "aa"}, "aab"), lib::regex::errors::DfaBuilderError);
        }
    }

    SECTION("Char classes") {
        SECTION("\\w, \\W") {
            REQUIRE(match({"\\w+", "\\W+"},
                        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_+") ==
                    Result{true, 63, 0});
            REQUIRE(match({"\\w+", "\\W+"}, " !@#$%^&*(0") == Result{true, 10, 1});
        }
        SECTION("\\d, \\D") {
            REQUIRE(match({"\\d+", "\\D+"}, "0123456789_") == Result{true, 10, 0});
            REQUIRE(match({"\\d+", "\\D+"}, "0123456789a") == Result{true, 10, 0});
            REQUIRE(match({"\\d+", "\\D+"}, " !@#$%^&*(0") == Result{true, 10, 1});
            REQUIRE(match({"\\d+", "\\D+"}, "abc012") == Result{true, 3, 1});
        }
        SECTION("\\s, \\S") {
            REQUIRE(match({"\\s+", "\\S+"}, " \t\n\r\f\v_") == Result{true, 6, 0});
            REQUIRE(match({"\\s+", "\\S+"}, "a9.? a9.?") == Result{true, 4, 1});
        }
        SECTION("Any char except newline") {
            REQUIRE(match({".+"},
                        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_!@#$%^&*("
                        " \t\r\f\v\n") == Result{true, 77, 0});
            REQUIRE(match({".+"}, "\na\n") == Result{false});
        }
    }

    SECTION("Char set") {
        SECTION("Simple") {
            REQUIRE(match({"[a-zA-Z0-9_]+", "[^a-zA-Z0-9_]+"},
                        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_+") ==
                    Result{true, 63, 0});
            REQUIRE(
                match({"[a-zA-Z0-9_]+", "[^a-zA-Z0-9_]+"}, " !@#$%^&*(0") == Result{true, 10, 1});
        }
        SECTION("Char class inside") {
            REQUIRE(match({"[\\w]+", "[\\W]+"},
                        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_+") ==
                    Result{true, 63, 0});
            REQUIRE(match({"[\\w]+", "[\\W]+"}, " !@#$%^&*(0") == Result{true, 10, 1});
            REQUIRE(match({"[^\\W]+", "[^\\w]+"},
                        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_+") ==
                    Result{true, 63, 0});
            REQUIRE(match({"[^\\W]+", "[^\\w]+"}, " !@#$%^&*(0") == Result{true, 10, 1});
        }
        SECTION("Custom range") {
            REQUIRE(match({"[a-c?-]+"}, "-?--a?b?c?-?--") == Result{true, 14, 0});
        }
    }
}
}  // namespace
