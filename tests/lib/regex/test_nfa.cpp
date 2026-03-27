#include <catch2/catch_test_macros.hpp>
#include <cmath>

#include "../../../src/lib/errors/errors.h"
#include "../../../src/lib/regex/algo/nfa/matcher.h"
#include "../../../src/lib/regex/parser/parser.h"
#include "../../../src/lib/regex/visitors/nfa_builder.h"

namespace Catch {  // NOLINT

template <>
struct StringMaker<lang::regex::algo::Matcher::Result> {
    static std::string convert(lang::regex::algo::Matcher::Result const& result) {  // NOLINT
        if (!result.matched) {
            return utils::FormatStream{} << "Result{matched=false}";
        }
        return utils::FormatStream{} << "Result{matched=true,length=" << result.length
                                     << ",final_id=" << result.final_id << "}";
    }
};
}  // namespace Catch

namespace {

using Result = lang::regex::algo::Matcher::Result;

class MatcherCreator {
public:
    MatcherCreator& Begin() {
        builder_.Clear();
        return *this;
    }

    MatcherCreator& AddToken(const std::string& regex) {
        const auto ptr = parser_.Parse(regex);
        assert(ptr != nullptr);
        builder_.ExtendFromAst(*ptr);
        return *this;
    }

    std::unique_ptr<lang::regex::algo::Matcher> End() const {
        return std::make_unique<lang::regex::algo::nfa::Matcher>(builder_.GetNfa());
    }

private:
    lang::regex::Parser parser_;
    lang::regex::visitors::NfaBuilder builder_;
};

TEST_CASE("lang::regex::visitors::NfaBuilder + lang::regex::algo::NfaEngine") {
    MatcherCreator creator;
    auto match = [&creator](const std::initializer_list<std::string> tokens,
                            const std::string& code) {
        creator.Begin();
        for (const auto& token : tokens) {
            creator.AddToken(token);
        }
        return creator.End()->Match(code);
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
        REQUIRE(match({"a", "a"}, "aaa") == Result{true, 1, 0});
        REQUIRE(match({"a?", "a"}, "aaa") == Result{true, 1, 0});
        REQUIRE(match({"a", "a?"}, "aaa") == Result{true, 1, 0});
    }

    SECTION("Not only first and last results") {
        REQUIRE(match({"a", "abc", "abcde"}, "") == Result{false});
        REQUIRE(match({"a", "abc", "abcde"}, "a") == Result{true, 1, 0});
        REQUIRE(match({"a", "abc", "abcde"}, "abc") == Result{true, 3, 1});
        REQUIRE(match({"a", "abc", "abcde"}, "abcde") == Result{true, 5, 2});
        REQUIRE(match({"a", "abc", "abcde"}, "abcdefg") == Result{true, 5, 2});
    }

    SECTION("Difficult example") {
        const std::string regexp = "(https?://)?example.(com|ru|org)(/(example|a+))*";
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
    }}

}  // namespace
