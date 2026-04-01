#pragma once

#include <cassert>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "../../../lib/lang/context/base_context.h"
#include "../../../lib/lang/frontend/parser/parser.hpp"
#include "../../../lib/lang/macros.h"
#include "../../ast/enums/binary_operation.h"
#include "../../ast/enums/unary_operation.h"
#include "../../ast/expr/binary_expression.h"
#include "../../ast/expr/function_call_expression.h"
#include "../../ast/expr/lit/int_literal.h"
#include "../../ast/expr/unary_expression.h"
#include "../../ast/expr/variable_expression.h"
#include "../../ast/program.h"
#include "../../ast/stmt/assignment_statement.h"
#include "../../ast/stmt/block_statement.h"
#include "../../ast/stmt/function_call_statement.h"
#include "../../ast/stmt/function_define_node.h"
#include "../../ast/stmt/if_else_statement.h"
#include "../../ast/stmt/if_statement.h"
#include "../../ast/stmt/return_statement.h"
#include "../../ast/stmt/variable_declare_statement.h"
#include "../../ast/stmt/while_statement.h"
#include "../../diag/list/syntax.h"
#include "../../token_type.h"

namespace lang::frontend {

namespace impl::parser {

using Token = lib::lang::source::Token<TokenType>;
using Tokens = lib::lang::frontend::Tokens<TokenType>;

inline bool IsComparisonToken(TokenType token_type) {
    return token_type == TokenType::EQ_O || token_type == TokenType::NE_O ||
           token_type == TokenType::LT_O || token_type == TokenType::LE_O ||
           token_type == TokenType::GT_O || token_type == TokenType::GE_O;
}

template <lib::lang::ContextLike Context>
class RecursiveDescentParser {
private:
    using Stage = lib::flow::Stage<Context>;

public:
    RecursiveDescentParser(const Tokens& tokens, Context& ctx, const Stage& stage)
        : tokens_(tokens), ctx_(ctx), stage_(stage) {}

    std::shared_ptr<ast::Node> Parse() {
        std::vector<std::shared_ptr<ast::stmt::FunctionDefineNode>> functions;
        while (!IsEof()) {
            functions.push_back(ParseFunctionDefineNode());
        }
        return std::make_shared<ast::Program>(std::move(functions));
    }

private:
    bool IsEof() const {
        return Peek().Is(TokenType::END_OF_FILE);
    }

    const Token& Peek(size_t offset = 0) const {
        size_t index = pos_ + offset;
        if (index >= tokens_.size()) {
            return tokens_.back();
        }
        return tokens_[index];
    }

    bool Check(TokenType token_type) const {
        return Peek().Is(token_type);
    }

    bool Match(TokenType token_type) {
        if (Check(token_type)) {
            ++pos_;
            return true;
        }
        return false;
    }

    const Token& Consume() {
        assert(pos_ < tokens_.size());
        return tokens_[pos_++];
    }

    const Token& ConsumeOrReport(TokenType token_type, const std::string& expected) {
        if (Check(token_type)) {
            return Consume();
        }
        ReportExpected(Peek(), expected);
    }

    [[noreturn]] void ReportExpected(const Token& token, const std::string& expected) {
        ctx_.diag.template Report<lang::diag::ParserExpectedTokenFatal>(
            stage_, token.GetSpan(), expected, TokenTypeToString(token.GetType()));
        UNREACHABLE;
    }

    [[noreturn]] void ReportUnsupportedType(const Token& token) {
        ctx_.diag.template Report<lang::diag::ParserUnsupportedTypeFatal>(
            stage_, token.GetSpan(), token.GetValue());
        UNREACHABLE;
    }

    const Token& ConsumeIdentifier(const std::string& expected = "identifier") {
        return ConsumeOrReport(TokenType::IDENTIFIER, expected);
    }

    std::string ParseIntTypeName() {
        const auto& type_token = ConsumeIdentifier("type name \"Int\"");
        if (type_token.GetValue() != "Int") {
            ReportUnsupportedType(type_token);
        }
        return type_token.GetValue();
    }

    std::shared_ptr<ast::stmt::FunctionDefineNode> ParseFunctionDefineNode() {
        ConsumeOrReport(TokenType::FN_K, "\"fn\"");
        std::string function_name = ConsumeIdentifier("function name").GetValue();

        ConsumeOrReport(TokenType::LPAREN, "\"(\"");
        std::vector<ast::stmt::FunctionParameter> parameters;
        if (!Check(TokenType::RPAREN)) {
            parameters.push_back(ParseFunctionParameter());
            while (Match(TokenType::COMMA)) {
                parameters.push_back(ParseFunctionParameter());
            }
        }
        ConsumeOrReport(TokenType::RPAREN, "\")\"");

        std::optional<std::string> return_type;
        if (Match(TokenType::ARROW)) {
            return_type = ParseIntTypeName();
        }

        auto body = ParseBlockStatement();
        return std::make_shared<ast::stmt::FunctionDefineNode>(
            std::move(function_name), std::move(parameters), std::move(body), std::move(return_type));
    }

    ast::stmt::FunctionParameter ParseFunctionParameter() {
        ast::stmt::FunctionParameter parameter;
        parameter.is_mutable = Match(TokenType::MUT_K);
        parameter.name = ConsumeIdentifier("parameter name").GetValue();
        ConsumeOrReport(TokenType::COLON, "\":\"");
        parameter.type_name = ParseIntTypeName();
        return parameter;
    }

    std::shared_ptr<ast::stmt::BlockStatement> ParseBlockStatement() {
        ConsumeOrReport(TokenType::LBRACE, "\"{\"");

        std::vector<std::shared_ptr<ast::Statement>> statements;
        while (!Check(TokenType::RBRACE)) {
            if (IsEof()) {
                ReportExpected(Peek(), "\"}\"");
            }
            statements.push_back(ParseStatement());
        }

        ConsumeOrReport(TokenType::RBRACE, "\"}\"");
        return std::make_shared<ast::stmt::BlockStatement>(std::move(statements));
    }

    std::shared_ptr<ast::Statement> ParseStatement() {
        if (Check(TokenType::IF_K)) {
            return ParseIfStatement();
        }
        if (Check(TokenType::WHILE_K)) {
            return ParseWhileStatement();
        }
        if (Check(TokenType::RETURN_K)) {
            return ParseReturnStatement();
        }
        if (Check(TokenType::LET_K) || Check(TokenType::MUT_K)) {
            return ParseVariableDeclareStatement();
        }
        if (Check(TokenType::IDENTIFIER)) {
            if (Peek(1).Is(TokenType::ASSIGN_O)) {
                return ParseAssignmentStatement();
            }
            if (Peek(1).Is(TokenType::LPAREN)) {
                return ParseFunctionCallStatement();
            }
            ReportExpected(Peek(1), "\"=\" or \"(\" after identifier");
        }

        ReportExpected(Peek(), "statement");
    }

    std::shared_ptr<ast::Statement> ParseIfStatement() {
        ConsumeOrReport(TokenType::IF_K, "\"if\"");
        ConsumeOrReport(TokenType::LPAREN, "\"(\"");
        auto condition = ParseExpression();
        ConsumeOrReport(TokenType::RPAREN, "\")\"");

        auto then_block = ParseBlockStatement();
        if (Match(TokenType::ELSE_K)) {
            auto else_block = ParseBlockStatement();
            return std::make_shared<ast::stmt::IfElseStatement>(
                std::move(condition), std::move(then_block), std::move(else_block));
        }
        return std::make_shared<ast::stmt::IfStatement>(std::move(condition), std::move(then_block));
    }

    std::shared_ptr<ast::Statement> ParseWhileStatement() {
        ConsumeOrReport(TokenType::WHILE_K, "\"while\"");
        ConsumeOrReport(TokenType::LPAREN, "\"(\"");
        auto condition = ParseExpression();
        ConsumeOrReport(TokenType::RPAREN, "\")\"");

        auto body = ParseBlockStatement();
        return std::make_shared<ast::stmt::WhileStatement>(std::move(condition), std::move(body));
    }

    std::shared_ptr<ast::Statement> ParseReturnStatement() {
        ConsumeOrReport(TokenType::RETURN_K, "\"return\"");

        if (Check(TokenType::SEMICOLON)) {
            Consume();
            return std::make_shared<ast::stmt::ReturnStatement>();
        }

        auto expression = ParseExpression();
        ConsumeOrReport(TokenType::SEMICOLON, "\";\"");
        return std::make_shared<ast::stmt::ReturnStatement>(std::move(expression));
    }

    std::shared_ptr<ast::Statement> ParseVariableDeclareStatement() {
        bool is_mutable = false;
        if (Match(TokenType::LET_K)) {
            is_mutable = false;
        } else {
            ConsumeOrReport(TokenType::MUT_K, "\"let\" or \"mut\"");
            is_mutable = true;
        }

        std::string variable_name = ConsumeIdentifier("variable name").GetValue();

        std::optional<std::string> type_name;
        if (Match(TokenType::COLON)) {
            type_name = ParseIntTypeName();
        }

        std::shared_ptr<ast::Expression> initial_value = nullptr;
        if (Match(TokenType::ASSIGN_O)) {
            initial_value = ParseExpression();
        }

        ConsumeOrReport(TokenType::SEMICOLON, "\";\"");
        return std::make_shared<ast::stmt::VariableDeclareStatement>(
            is_mutable, std::move(variable_name), std::move(type_name), std::move(initial_value));
    }

    std::shared_ptr<ast::Statement> ParseAssignmentStatement() {
        std::string variable_name = ConsumeIdentifier("variable name").GetValue();
        ConsumeOrReport(TokenType::ASSIGN_O, "\"=\"");

        auto expression = ParseExpression();
        ConsumeOrReport(TokenType::SEMICOLON, "\";\"");

        return std::make_shared<ast::stmt::AssignmentStatement>(
            std::move(variable_name), std::move(expression));
    }

    std::shared_ptr<ast::Statement> ParseFunctionCallStatement() {
        const auto& function_name_token = ConsumeIdentifier("function name");
        auto call_expr = ParseFunctionCallExpressionFromName(function_name_token.GetValue());
        ConsumeOrReport(TokenType::SEMICOLON, "\";\"");
        return std::make_shared<ast::stmt::FunctionCallStatement>(std::move(call_expr));
    }

    std::shared_ptr<ast::Expression> ParseExpression() {
        return ParseComparisonExpression();
    }

    std::shared_ptr<ast::Expression> ParseComparisonExpression() {
        auto result = ParsePlusMinusExpression();
        if (IsComparisonToken(Peek().GetType())) {
            auto operation_token = Consume();
            auto right = ParsePlusMinusExpression();
            auto operation = ast::enums::TokenTypeToBinaryOperation(operation_token.GetType());
            result = std::make_shared<ast::expr::BinaryExpression>(
                operation, std::move(result), std::move(right));
        }
        return result;
    }

    std::shared_ptr<ast::Expression> ParsePlusMinusExpression() {
        auto result = ParseMulDivExpression();
        while (Check(TokenType::PLUS_O) || Check(TokenType::MINUS_O)) {
            auto operation_token = Consume();
            auto right = ParseMulDivExpression();
            auto operation = ast::enums::TokenTypeToBinaryOperation(operation_token.GetType());
            result = std::make_shared<ast::expr::BinaryExpression>(
                operation, std::move(result), std::move(right));
        }
        return result;
    }

    std::shared_ptr<ast::Expression> ParseMulDivExpression() {
        auto result = ParseUnaryExpression();
        while (Check(TokenType::STAR_O) || Check(TokenType::SLASH_O)) {
            auto operation_token = Consume();
            auto right = ParseUnaryExpression();
            auto operation = ast::enums::TokenTypeToBinaryOperation(operation_token.GetType());
            result = std::make_shared<ast::expr::BinaryExpression>(
                operation, std::move(result), std::move(right));
        }
        return result;
    }

    std::shared_ptr<ast::Expression> ParseUnaryExpression() {
        if (Match(TokenType::MINUS_O)) {
            auto expression = ParseUnaryExpression();
            return std::make_shared<ast::expr::UnaryExpression>(
                ast::enums::UnaryOperation::NEG, std::move(expression));
        }
        return ParsePrimaryExpression();
    }

    std::shared_ptr<ast::Expression> ParsePrimaryExpression() {
        if (Check(TokenType::INT_LITERAL)) {
            return std::make_shared<ast::expr::lit::IntLiteral>(Consume().GetValue());
        }

        if (Check(TokenType::IDENTIFIER)) {
            const auto& token = Consume();
            if (Check(TokenType::LPAREN)) {
                return ParseFunctionCallExpressionFromName(token.GetValue());
            }
            return std::make_shared<ast::expr::VariableExpression>(token.GetValue());
        }

        if (Match(TokenType::LPAREN)) {
            auto expression = ParseExpression();
            ConsumeOrReport(TokenType::RPAREN, "\")\"");
            return expression;
        }

        ReportExpected(Peek(), "expression");
    }

    std::shared_ptr<ast::expr::FunctionCallExpression> ParseFunctionCallExpressionFromName(
        std::string function_name) {
        ConsumeOrReport(TokenType::LPAREN, "\"(\"");

        std::vector<std::shared_ptr<ast::Expression>> arguments;
        if (!Check(TokenType::RPAREN)) {
            arguments.push_back(ParseExpression());
            while (Match(TokenType::COMMA)) {
                arguments.push_back(ParseExpression());
            }
        }

        ConsumeOrReport(TokenType::RPAREN, "\")\"");
        return std::make_shared<ast::expr::FunctionCallExpression>(
            std::move(function_name), std::move(arguments));
    }

private:
    const Tokens& tokens_;
    size_t pos_ = 0;
    Context& ctx_;
    const Stage& stage_;
};

}  // namespace impl::parser

template <lib::lang::ContextLike Context>
class RecursiveDescentParser : public lib::lang::frontend::Parser<TokenType, ast::Node, Context> {
public:
    std::shared_ptr<ast::Node> Run(impl::parser::Tokens tokens, Context& ctx) const override {
        return impl::parser::RecursiveDescentParser<Context>{tokens, ctx, *this}.Parse();
    }

    std::string Name() const override {
        return "RecursiveDescentParser";
    }
};

}  // namespace lang::frontend
