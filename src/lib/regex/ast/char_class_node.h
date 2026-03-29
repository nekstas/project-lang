#pragma once

#include <string>

#include "../visitors/visitor.h"
#include "char_set_node.h"
#include "node.h"

namespace lib::regex::ast {

enum class CharClass { WORD, DIGIT, SPACE, NEWLINE };

std::string CharClassToRepr(CharClass repeat_type, bool negated);

class CharClassNode : public CharSetNode {
public:
    explicit CharClassNode(CharClass char_class, bool negated = false);

    bool Equals(const Node* another_node) const override;

    void Accept(visitors::Visitor& visitor) const override {
        visitor.Visit(*this);
    }

    CharClass GetCharClass() const {
        return char_class_;
    }

    static DetailedMask ConstructDetailedMask(CharClass char_class);

private:
    CharClass char_class_;
};

}  // namespace lib::regex::ast
