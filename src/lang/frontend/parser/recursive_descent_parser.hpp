#pragma once

#include <cassert>
#include <iostream>

#include "../../../lib/lang/context/base_context.h"
#include "../../../lib/lang/frontend/parser/parser.hpp"
#include "../../ast/enums/binary_operation.h"
#include "../../ast/expr/binary_expression.h"
#include "../../ast/expr/lit/int_literal.h"
#include "../../ast/node.hpp"
#include "../../enums/token_type.h"

namespace lang::frontend {

namespace impl::parser {

// template <lib::lang::ContextLike Context>
// class RecursiveDescentParserBase {
// public:
//     RecursiveDescentParserBase(const Tokens& tokens, Context& ctx) : tokens_(tokens), ctx_(ctx) {}
//
//     bool IsEof() const {
//         return tokens_[pos_].Is(e::TokenType::END_OF_FILE);
//     }
//
//     const Token& Peek() const {
//         assert(pos_ < tokens_.size());
//         return tokens_[pos_];
//     }
//
//     void Advance() {
//         assert(!IsEof());
//         ++pos_;
//     }
//
//     const Token& Consume() {
//         assert(!IsEof());
//         return tokens_[pos_++];
//     }
//
//     // bool AdvanceIf(uint8_t ch) {
//     //     if (!IsEof() && code_[pos_] == ch) {
//     //         ++pos_;
//     //         return true;
//     //     }
//     //     return false;
//     // }
//     //
//     // void Match(uint8_t ch) {
//     //     THROW_REGEX_PARSER_ERROR_IF(IsEof() || code_[pos_] != ch, "Expected: " << ch << ".");
//     //     ++pos_;
//     // }
//     //
//     // void Match(const std::set<uint8_t>& options) {
//     //     THROW_REGEX_PARSER_ERROR_IF(IsEof() || !options.contains(code_[pos_]),
//     //         "Expected one of: " << GenerateExpected(options));
//     //     ++pos_;
//     // }
//     //
//     // uint8_t ConsumeAsciiChar() {
//     //     uint8_t code = Consume();
//     //     THROW_REGEX_PARSER_ERROR_IF(!::utils::IsAsciiChar(code), "Expected ASCII char.");
//     //     return code;
//     // }
//
// private:
//     Tokens tokens_;
//     size_t pos_ = 0;
//     Context& ctx_;
// };

// template <lib::lang::ContextLike Context>
// class RecursiveDescentParser : protected RecursiveDescentParserBase<Context> {
// private:
//     using Super = RecursiveDescentParserBase<Context>;
//
// public:
//     using RecursiveDescentParserBase<Context>::RecursiveDescentParserBase;
//
//     std::shared_ptr<ast::Node> Parse() {
//         return ParseBinaryExpression();
//     }
//
// private:
//     std::shared_ptr<ast::Expression> ParseBinaryExpression() {
//         return ParseComparisonExpression();
//     }
//
//     std::shared_ptr<ast::Expression> ParseComparisonExpression() {
//         std::shared_ptr<ast::Expression> result = ParsePlusMinusExpression();
//         if (Super::Peek().Is({TokenType::EQ_O, TokenType::NE_O, TokenType::LT_O, TokenType::LE_O,
//                 TokenType::GT_O, TokenType::GE_O})) {
//             auto token = Super::Consume();
//             auto right = ParsePlusMinusExpression();
//             auto type = ast::enums::TokenTypeToBinaryOperation(token.GetType());
//             result = std::make_shared<ast::expr::BinaryExpression>(type, std::move(result), right);
//         }
//         return result;
//     }
//
//     std::shared_ptr<ast::Expression> ParsePlusMinusExpression() {
//         std::shared_ptr<ast::Expression> result = ParseMulDivExpression();
//         while (Super::Peek().Is({TokenType::PLUS_O, TokenType::MINUS_O})) {
//             auto token = Super::Consume();
//             auto right = ParseMulDivExpression();
//             auto type = ast::enums::TokenTypeToBinaryOperation(token.GetType());
//             result = std::make_shared<ast::expr::BinaryExpression>(type, std::move(result), right);
//         }
//         return result;
//     }
//
//     std::shared_ptr<ast::Expression> ParseMulDivExpression() {
//         std::shared_ptr<ast::Expression> result = ParseLiteral();
//         while (Super::Peek().Is({TokenType::STAR_O, TokenType::SLASH_O})) {
//             auto token = Super::Consume();
//             auto right = ParseLiteral();
//             auto type = ast::enums::TokenTypeToBinaryOperation(token.GetType());
//             result = std::make_shared<ast::expr::BinaryExpression>(type, std::move(result), right);
//         }
//         return result;
//     }
//
//     std::shared_ptr<ast::expr::Literal> ParseLiteral() {
//         if (Super::Peek().Is(TokenType::INT_LITERAL)) {
//             auto token = Super::Consume();
//             return std::make_shared<ast::expr::lit::IntLiteral>(token.GetValue());
//         }
//         return nullptr;
//     }
// };

}  // namespace impl::parser

// template <lib::lang::ContextLike Context>
// class RecursiveDescentParser : public lib::lang::frontend::Parser<TokenType, ast::Node, Context>
// { public:
//     std::shared_ptr<ast::Node> Run(impl::parser::Tokens tokens, Context& ctx) const override {
//         std::cerr << "tokens.size() = " << tokens.size() << "\n";
//         for (const auto& token : tokens) {
//             std::cerr << token << "\n";
//         }
//         auto result = impl::parser::RecursiveDescentParser<Context>{tokens, ctx}.Parse();
//         return std::move(result);
//     }
//
//     std::string Name() const override {
//         return "RecursiveDescentParser";
//     }
//
// private:
//     using Super = lib::lang::frontend::Parser<TokenType, ast::Node, Context>;
//
// public:
// };

}  // namespace lang::frontend
