#include "char_class_node.h"

#include "../../errors/errors.h"

namespace lib::regex::ast {

std::string CharClassToRepr(CharClass repeat_type, bool negated) {
    switch (repeat_type) {
        case CharClass::WORD:
            return negated ? "\\W" : "\\w";
        case CharClass::DIGIT:
            return negated ? "\\D" : "\\d";
        case CharClass::SPACE:
            return negated ? "\\S" : "\\s";
        case CharClass::NEWLINE:
            return negated ? "." : "\\n";
        default:
            UNREACHABLE;
    }
}

CharClassNode::CharClassNode(CharClass char_class, bool negated)
    : CharSetNode(ConstructDetailedMask(char_class), negated), char_class_(char_class) {}

bool CharClassNode::Equals(const Node* another_node) const {
    const auto char_class_node = CastNode<CharClassNode>(another_node);
    return char_class_node && GetCharClass() == char_class_node->GetCharClass() &&
           CharSetNode::Equals(another_node);
}

CharSetNode::DetailedMask CharClassNode::ConstructDetailedMask(CharClass char_class) {
    switch (char_class) {
        case CharClass::WORD:
            return DetailedMask::FromRanges(
                {Range{'a', 'z'}, Range{'A', 'Z'}, Range{'0', '9'}, Range{'_'}});
        case CharClass::DIGIT:
            return DetailedMask::FromRanges({Range{'0', '9'}});
        case CharClass::SPACE:
            return DetailedMask::FromString(" \t\n\r\f\v");
        case CharClass::NEWLINE:
            return DetailedMask::FromRanges({Range{'\n'}});
        default:
            UNREACHABLE;
    }
}

}  // namespace lib::regex::ast
