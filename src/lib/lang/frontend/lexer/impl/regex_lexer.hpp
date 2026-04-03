#pragma once

#include "../../../../regex/algo/dfa/matcher.h"
#include "../../../../regex/compiler/compiler.h"
#include "../../../../regex/dfa/dfa.h"
#include "../../../../utils/better_stack.hpp"
#include "../../../context/base_context.h"
#include "../../../src/token.hpp"
#include "../lexer.hpp"

namespace lib::lang::frontend::impl {

template <typename TokenType, ContextLike Context>
class RegexLexer : public Lexer<TokenType, Context> {
private:
    static constexpr size_t kNoState = -1;
    static constexpr size_t kNoFinalId = -1;
    static constexpr size_t kNoPos = -1;

protected:
    enum class HasValue { FALSE, TRUE };

    struct TokenDesc {
        TokenType type;
        bool has_value;
    };

private:
    struct LexerState {
        std::size_t pos;
        std::size_t state;

        bool operator==(const LexerState& another) const {
            return std::tie(state, pos) == std::tie(another.state, another.pos);
        }
    };

    class PreviouslyFailed {
    public:
        const bool& operator[](const LexerState& state) const {
            return table_.at(state.pos).at(state.state);
        }

        bool& operator[](const LexerState& state) {
            return table_[state.pos][state.state];
        }

        std::unordered_map<size_t, std::unordered_map<size_t, bool>> table_;
    };

public:
    t::Tokens<TokenType> Run(SourceDesc desc, Context& ctx) const override {
        THROW_IF(!ready_, ::errors::LogicError, "Lexer is not ready.");
        const std::string& code = ctx.src.GetSource(desc).GetContent();
        size_t initial_state = dfa_.GetRootId();

        PreviouslyFailed previously_failed;
        LexerState current = {.pos = 0, .state = initial_state};
        t::Tokens<TokenType> result;

        auto get_next_state = [&] {
            if (current.pos < code.size()) {
                return dfa_.GetState(current.state).GetEdge(code[current.pos]);
            }
            return kNoState;
        };
        auto get_final_id = [&] {
            if (current.state != kNoState) {
                return dfa_.GetState(current.state).GetFinalId();
            }
            return kNoFinalId;
        };

        while (current.pos < code.size()) {
            current.state = initial_state;

            size_t begin_pos = current.pos;
            ::utils::BetterStack<LexerState> stack{{.pos = kNoPos, .state = kNoState}};

            size_t next_state;
            for (; (next_state = get_next_state()) != kNoState; ++current.pos) {
                if (previously_failed[current]) {
                    break;
                }
                auto final_id = get_final_id();
                if (final_id != kNoFinalId) {
                    stack.Clear();
                }
                stack.push(current);
                current.state = next_state;
            }

            while (get_final_id() == kNoFinalId) {
                previously_failed[current] = true;
                if (stack.top().state == kNoState) {
                    current = {.pos = begin_pos + 1, .state = kNoState};
                    break;
                }
                current = stack.Extract();
            }

            src::Span span = src::Span::FromRange(desc, begin_pos, current.pos);
            size_t final_id = get_final_id();
            if (final_id == kNoFinalId) {
                DIAG_REPORT(ctx, diag::UnexpectedSymbolError, span);
            } else {
                result.push_back(ConstructToken(code, final_id, span));
            }
        }

        result.push_back(ConstructEofToken(desc, ctx));
        return result;
    }

    std::string Name() const override {
        return "RegexLexer";
    }

protected:
    void Init() {
        regex_compiler_.Clear();
        dfa_ = {};
        token_descriptors_.clear();
        ready_ = false;
    }

    void AddToken(
        TokenType token_type, const std::string& regex, HasValue has_value = HasValue::FALSE) {
        THROW_IF(ready_, ::errors::LogicError, "Can't modify lexer if it is ready.");
        TokenDesc desc{token_type, has_value == HasValue::TRUE};
        auto final_id = regex_compiler_.AddRegex(regex);
        THROW_IF(
            final_id != token_descriptors_.size(), ::errors::LogicError, "Unexpected final_id.");
        token_descriptors_.push_back(desc);
    }

    void Build(TokenType eof_token) {
        THROW_IF(ready_, ::errors::LogicError, "Can't build lexer because it's already done.");
        token_descriptors_.push_back({.type = eof_token, .has_value = false});
        dfa_ = regex_compiler_.CompileToDfa();
        ready_ = true;
    }

    TokenType GetEofType() {
        THROW_IF(!ready_, ::errors::LogicError, "Can't get Eof type because lexer is not ready.");
        return token_descriptors_.back().type;
    }

private:
    src::Token<TokenType> ConstructToken(
        const std::string& code, size_t final_id, const src::Span& span) const {
        const auto& desc = token_descriptors_[final_id];
        std::string value = code.substr(span.GetOffset(), span.GetLength());

        if (desc.has_value) {
            return src::Token<TokenType>(desc.type, value, span);
        }
        return src::Token<TokenType>(desc.type, span);
    }

    src::Token<TokenType> ConstructEofToken(SourceDesc desc, const Context& ctx) const {
        const std::string& code = GetCode(desc, ctx);
        src::Span span{desc, code.size(), code.size()};
        return ConstructToken(code, GetEofFinalId(), span);
    }

    static const std::string& GetCode(SourceDesc desc, const Context& ctx) {
        return ctx.src.GetSource(desc).GetContent();
    }

    size_t GetEofFinalId() const {
        THROW_IF(
            !ready_, ::errors::LogicError, "Can't get Eof final_id because lexer is not ready.");
        return token_descriptors_.size() - 1;
    }

private:
    regex::Compiler regex_compiler_;
    regex::dfa::Dfa dfa_;
    std::vector<TokenDesc> token_descriptors_;
    bool ready_ = false;
};

}  // namespace lib::lang::frontend::impl
