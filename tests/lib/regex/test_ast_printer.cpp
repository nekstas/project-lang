#include <catch2/catch_test_macros.hpp>

#include "../../../src/lib/errors/errors.h"
#include "../../../src/lib/regex/parser/parser.h"
#include "../../../src/lib/regex/visitors/ast_printer.h"

TEST_CASE("lib::regex::visitors::AstPrinter") {
    lib::regex::Parser parser;
    lib::regex::visitors::AstPrinter ast_printer(0, false);
    auto make_ast = [&parser, &ast_printer](const std::string& code) {
        auto ptr = parser.Parse(code);
        return ast_printer.ToString(ptr.get());
    };

    SECTION("Empty") {
        REQUIRE(make_ast("") == "[null]");
    }
    SECTION("Just char") {
        REQUIRE(make_ast("a") == "['a']");
    }
    SECTION("Russian char") {
        REQUIRE(make_ast("я") == "[\"я\"]");
        REQUIRE(
            make_ast("Привет мир!") ==
            "[seq][\"П\"][\"р\"][\"и\"][\"в\"][\"е\"][\"т\"][' '][\"м\"][\"и\"][\"р\"]['!'][/seq]");
    }
    SECTION("Simple sequence") {
        REQUIRE(make_ast("abc") == "[seq]['a']['b']['c'][/seq]");
    }
    SECTION("Escape sequences") {
        REQUIRE(make_ast("\\(") == "['(']");
        REQUIRE(make_ast("\\|") == "['|']");
        REQUIRE(make_ast("\\)") == "[')']");
        REQUIRE(make_ast("\\*") == "['*']");
        REQUIRE(make_ast("\\+") == "['+']");
        REQUIRE(make_ast("\\?") == "['?']");
    }
    SECTION("Bracket symbols") {
        REQUIRE(make_ast("\\(\\)") == "[seq]['('][')'][/seq]");
    }
    SECTION("Special escape sequences") {
        REQUIRE(make_ast("\\\\") == "['\\\\']");
        REQUIRE(make_ast("\\'") == "['\\'']");
        REQUIRE(make_ast("\\n") == "['\\n']");
        REQUIRE(make_ast("\\t") == "['\\t']");
        REQUIRE(make_ast("\\\\\\\\") == "[seq]['\\\\']['\\\\'][/seq]");
    }
    SECTION("Simple alternative") {
        REQUIRE(make_ast("(a|b)") == "[choice]['a']['b'][/choice]");
    }
    SECTION("Only one alternative") {
        REQUIRE(make_ast("(a)") == "['a']");
    }
    SECTION("Many brackets") {
        REQUIRE(make_ast("((((a|b))))") == "[choice]['a']['b'][/choice]");
    }
    SECTION("Recursive") {
        REQUIRE(make_ast("((((a|b))|((c))))") ==
                "[choice][choice]['a']['b'][/choice]['c'][/choice]");
        REQUIRE(make_ast("(abc|def)") ==
                "[choice][seq]['a']['b']['c'][/seq][seq]['d']['e']['f'][/seq][/choice]");
    }
    SECTION("Different repeats") {
        REQUIRE(make_ast("a*") == "[repeat *]['a'][/repeat]");
        REQUIRE(make_ast("a+") == "[repeat +]['a'][/repeat]");
        REQUIRE(make_ast("a?") == "[repeat ?]['a'][/repeat]");
    }
    SECTION("Sequence of repeats") {
        REQUIRE(
            make_ast("a*b+c?") ==
            "[seq][repeat *]['a'][/repeat][repeat +]['b'][/repeat][repeat ?]['c'][/repeat][/seq]");
    }
    SECTION("Repeat of choice") {
        REQUIRE(make_ast("(a|b)*c") ==
                "[seq][repeat *][choice]['a']['b'][/choice][/repeat]['c'][/seq]");
    }
    SECTION("Repeat of sequence") {
        REQUIRE(make_ast("c(ab)*") == "[seq]['c'][repeat *][seq]['a']['b'][/seq][/repeat][/seq]");
    }
    SECTION("Repeat of a Russian char") {
        REQUIRE(make_ast("ая+") == "[seq][\"а\"][repeat +][\"я\"][/repeat][/seq]");
        REQUIRE(make_ast("а(я)+") == "[seq][\"а\"][repeat +][\"я\"][/repeat][/seq]");
    }
}
