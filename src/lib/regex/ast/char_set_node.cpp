#include "char_set_node.h"

#include "../../errors/errors.h"

namespace lib::regex::ast {

CharSetNode::Range::Range(uint8_t ch) : Range(ch, ch) {}

CharSetNode::Range::Range(uint8_t from, uint8_t to) : from_(from), to_(to) {
    THROW_IF(from_ > to_, ::errors::LogicError,
        "For range `from` should be less or equal than `to`. (from="
            << static_cast<size_t>(from_) << ", to=" << static_cast<size_t>(to_) << ")");
}

CharSetNode::DetailedMask::DetailedMask(const std::bitset<consts::kStateEdgesCount>& mask)
    : mask_(mask) {}

CharSetNode::DetailedMask CharSetNode::DetailedMask::FromRanges(const std::vector<Range>& ranges) {
    DetailedMask detailed_mask;
    for (const auto& range : ranges) {
        detailed_mask.ExtendFrom(range);
    }
    return detailed_mask;
}

CharSetNode::DetailedMask CharSetNode::DetailedMask::FromString(const std::string& symbols) {
    DetailedMask detailed_mask;
    for (uint8_t ch : symbols) {
        detailed_mask.mask_.set(ch, true);
    }
    return detailed_mask;
}

void CharSetNode::DetailedMask::ExtendFrom(uint8_t code) {
    mask_.set(code, true);
}

void CharSetNode::DetailedMask::ExtendFrom(const Range& range) {
    for (size_t ch = range.GetFrom(); ch <= range.GetTo(); ++ch) {
        mask_.set(ch, true);
    }
}

void CharSetNode::DetailedMask::ExtendFrom(const DetailedMask& detailed_mask) {
    mask_ |= detailed_mask.GetMask();
}

bool CharSetNode::DetailedMask::Exclude(uint8_t code) {
    bool old_value = mask_.test(code);
    mask_.reset(code);
    return old_value;
}

std::vector<CharSetNode::Range> CharSetNode::DetailedMask::ToOptimalRanges() const {
    std::vector<Range> result;
    for (size_t i = 0; i < consts::kStateEdgesCount; ++i) {
        size_t j = i, old_i = i;
        while (j < consts::kStateEdgesCount && mask_.test(j)) {
            ++j, ++i;
        }
        if (j > old_i) {
            result.emplace_back(old_i, j - 1);
        }
    }
    return result;
}

size_t CharSetNode::DetailedMask::Count() const {
    return mask_.count();
}

bool CharSetNode::DetailedMask::Is(uint8_t ch) const {
    return mask_.test(ch);
}

CharSetNode::CharSetNode(const DetailedMask& detailed_mask, bool negated)
    : detailed_mask_(detailed_mask), negated_(negated) {
    EnsureInvariants();
}

bool CharSetNode::Equals(const Node* another_node) const {
    const auto char_set_node = CastNode<CharSetNode>(another_node);
    return char_set_node && GetMask() == char_set_node->GetMask() &&
           GetNegated() == char_set_node->GetNegated();
}

void CharSetNode::EnsureInvariants() const {
    THROW_IF(CountEdges() == 0, ::errors::LogicError, "Char set should contain at least one edge.");
}

std::vector<CharSetNode::Range> ToSpecialRanges(CharSetNode::DetailedMask detailed_mask) {
    bool has_dash = detailed_mask.Exclude('-');
    auto result = detailed_mask.ToOptimalRanges();
    if (has_dash) {
        result.push_back(CharSetNode::Range{'-'});
    }
    return result;
}

}  // namespace lib::regex::ast
