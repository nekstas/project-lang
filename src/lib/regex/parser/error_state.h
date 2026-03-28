#pragma once

#include <cstdint>

namespace lib::regex::parser {

// TODO: возможно в будущем стоит расширить здесь информацию,
//  добавить поддержку UTF-8, контекст и подобное...

class ErrorState {
public:
    ErrorState(size_t pos, uint8_t ch, bool is_eof) : pos_(pos), char_(ch), is_eof_(is_eof) {}

    size_t GetPos() const {
        return pos_;
    }

    uint8_t GetChar() const {
        return char_;
    }

    bool IsEof() const {
        return is_eof_;
    }

private:
    size_t pos_;
    uint8_t char_;
    bool is_eof_;
};

}  // namespace lib::regex::parser
