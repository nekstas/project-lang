#include <catch2/catch_all.hpp>

#include "../../../src/lib/errors/errors.h"
#include "../../../src/lib/regex/ast/all.h"
#include "utils.h"

namespace {

using lang::regex::ast::CharNode;
using lang::regex::ast::ChoiceNode;
using lang::regex::ast::RepeatNode;
using lang::regex::ast::RepeatType;
using lang::regex::ast::SequenceNode;

TEST_CASE("lang::regex::ast nodes") {
    SECTION("lang::regex::ast::CharNode") {
        const auto node_a = CharNode('a');
        REQUIRE_FALSE(node_a.Equals(nullptr));
        const auto node_b = CharNode('b');
        REQUIRE_FALSE(node_a.Equals(&node_b));
        REQUIRE(node_a.Equals(&node_a));
        const auto node_also_a = CharNode('a');
        REQUIRE(node_a.Equals(&node_also_a));
    }

    SECTION("lang::regex::ast::NodesBaseNode") {
        AstBuilder ast_builder{};

        SECTION("Empty nodes list") {
            REQUIRE_THROWS_AS(ast_builder.Make<SequenceNode>(), errors::LogicError);
        }

        SECTION("nullptr element in nodes") {
            std::vector<std::unique_ptr<Node>> nodes;
            nodes.push_back({});
            REQUIRE_THROWS_AS(std::make_unique<ChoiceNode>(std::move(nodes)), errors::LogicError);
        }

        SECTION("Only one node in list") {
            REQUIRE_THROWS_AS(ast_builder.AddChar('a').Make<SequenceNode>(), errors::LogicError);
        }

        SECTION("Different sizes") {
            const auto node1 = ast_builder.AddChars("ab").Make<SequenceNode>();
            const auto node2 = ast_builder.AddChars("abc").Make<SequenceNode>();
            REQUIRE(!node1->Equals(node2.get()));
            REQUIRE(!node2->Equals(node1.get()));
        }

        SECTION("Simple equals") {
            const auto node1 = ast_builder.AddChars("cd").Make<SequenceNode>();
            const auto node2 = ast_builder.AddChars("cd").Make<SequenceNode>();
            REQUIRE(node1->Equals(node2.get()));
            REQUIRE(node2->Equals(node1.get()));
        }

        SECTION("Simple not equals") {
            const auto node1 = ast_builder.AddChars("!%").Make<SequenceNode>();
            const auto node2 = ast_builder.AddChars("%!").Make<SequenceNode>();
            REQUIRE(!node1->Equals(node2.get()));
            REQUIRE(!node2->Equals(node1.get()));
        }

        SECTION("Recursive equals") {
            const auto node1 = ast_builder.AddNode(AstBuilder{}.AddChars("st").Make<ChoiceNode>())
                                   .AddChars("p")
                                   .Make<SequenceNode>();
            const auto node2 = ast_builder.AddNode(AstBuilder{}.AddChars("st").Make<ChoiceNode>())
                                   .AddChars("p")
                                   .Make<SequenceNode>();
            REQUIRE(node1->Equals(node2.get()));
            REQUIRE(node2->Equals(node1.get()));
        }

        SECTION("Different types does not equal") {
            const auto node1 = ast_builder.AddChars("string").Make<SequenceNode>();
            const auto node2 = ast_builder.AddChars("string").Make<ChoiceNode>();
            REQUIRE_FALSE(node1->Equals(node2.get()));
            REQUIRE_FALSE(node2->Equals(node1.get()));
        }
    }

    SECTION("lang::regex::ast::RepeatNode") {
        AstBuilder ast_builder{};

        SECTION("Inner node is nullptr") {
            auto inner_node = ast_builder.AddChars("abc").Make<SequenceNode>();
            REQUIRE_THROWS_AS(std::make_unique<RepeatNode>(nullptr, RepeatType::ZERO_OR_ONE),
                              errors::LogicError);
        }

        SECTION("RepeatNode inside RepeatNode") {
            auto inner_node = std::make_unique<RepeatNode>(std::make_unique<CharNode>('a'),
                                                           RepeatType::ZERO_OR_MORE);
            REQUIRE_THROWS_AS(
                std::make_unique<RepeatNode>(std::move(inner_node), RepeatType::ONE_OR_MORE),
                errors::LogicError);
        }

        SECTION("Equals") {
            auto node1 = RepeatNode(std::make_unique<CharNode>('a'), RepeatType::ZERO_OR_MORE);
            auto node2 = RepeatNode(std::make_unique<CharNode>('a'), RepeatType::ZERO_OR_MORE);
            auto node3 = RepeatNode(std::make_unique<CharNode>('a'), RepeatType::ONE_OR_MORE);
            auto node4 = RepeatNode(std::make_unique<CharNode>('c'), RepeatType::ONE_OR_MORE);
            REQUIRE(node1.Equals(&node2));
            REQUIRE_FALSE(node1.Equals(&node3));
            REQUIRE_FALSE(node3.Equals(&node4));
        }
    }
}

}  // namespace
