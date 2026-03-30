#pragma once

#include <cassert>
#include <set>

#include "../../utils/utils.h"
#include "../errors/errors.h"
#include "error_state.h"

#define THROW_REGEX_PARSER_ERROR_IF(condition, format_expr) \
    THROW_IF(condition, lib::regex::errors::ParserError, format_expr, GetErrorState())
#define THROW_REGEX_PARSER_ERROR(format_expr) THROW_REGEX_PARSER_ERROR_IF(true, format_expr)

namespace lib::regex::parser {

class Base {

protected:
    void SetCodeAndReset(const std::string& code) {
        code_ = code;
        pos_ = 0;
    }

    bool IsEof() const {
        return pos_ >= code_.size();
    }

    ErrorState GetErrorState() const {
        return {pos_, Peek(), IsEof()};
    }

    uint8_t Peek() const {
        if (IsEof()) {
            return '\0';
        }
        return code_[pos_];
    }

    void Advance() {
        assert(!IsEof());
        ++pos_;
    }

    uint8_t Consume() {
        THROW_REGEX_PARSER_ERROR_IF(IsEof(), "Unexpected eof.");
        assert(!IsEof());
        return code_[pos_++];
    }

    bool AdvanceIf(uint8_t ch) {
        if (!IsEof() && code_[pos_] == ch) {
            ++pos_;
            return true;
        }
        return false;
    }

    void Match(uint8_t ch) {
        THROW_REGEX_PARSER_ERROR_IF(IsEof() || code_[pos_] != ch, "Expected: " << ch << ".");
        ++pos_;
    }

    void Match(const std::set<uint8_t>& options) {
        THROW_REGEX_PARSER_ERROR_IF(IsEof() || !options.contains(code_[pos_]),
            "Expected one of: " << GenerateExpected(options));
        ++pos_;
    }

    uint8_t ConsumeAsciiChar() {
        uint8_t code = Consume();
        THROW_REGEX_PARSER_ERROR_IF(!::utils::IsAsciiChar(code), "Expected ASCII char.");
        return code;
    }

private:
    static std::string GenerateExpected(const std::set<uint8_t>& options) {
        ::utils::FormatStream out;
        bool is_first = true;
        for (const uint8_t& option : options) {
            if (!is_first) {
                out << " | ";
            }
            out << "'" << option << "'";
            is_first = false;
        }
        return out;
    }

private:
    std::string code_;
    size_t pos_ = 0;
};

}  // namespace lib::regex::parser
