#pragma once

#include <bitset>
#include <cassert>
#include <vector>

#include "../consts.h"
#include "../visitors/visitor.h"
#include "node.h"

namespace lib::regex::ast {

class CharSetNode : public Node {
public:
    class Range {
    public:
        explicit Range(uint8_t ch);
        Range(uint8_t from, uint8_t to);

        bool IsDot() const {
            return from_ == to_;
        }

        size_t Length() const {
            return to_ - from_ + 1;
        }

        uint8_t GetDot() const {
            assert(from_ == to_);
            return from_;
        }

        uint8_t GetFrom() const {
            return from_;
        }

        uint8_t GetTo() const {
            return to_;
        }

    private:
        uint8_t from_;
        uint8_t to_;
    };

public:
    class DetailedMask {
    private:
        using MaskType = std::bitset<consts::kStateEdgesCount>;

    public:
        DetailedMask() = default;
        explicit DetailedMask(const MaskType& mask);

    public:
        static DetailedMask FromRanges(const std::vector<Range>& ranges);
        static DetailedMask FromString(const std::string& symbols);

    public:
        void ExtendFrom(uint8_t code);
        void ExtendFrom(const Range& range);
        void ExtendFrom(const DetailedMask& detailed_mask);

        bool Exclude(uint8_t code);
        std::vector<Range> ToOptimalRanges() const;
        size_t Count() const;

    public:
        MaskType GetMask() const {
            return mask_;
        }

        bool Is(uint8_t ch) const;

        bool operator==(const DetailedMask& another) const {
            return mask_ == another.mask_;
        }

        DetailedMask operator~() const {
            return DetailedMask{~mask_};
        }

    private:
        MaskType mask_;
    };

public:
    explicit CharSetNode(const DetailedMask& detailed_mask, bool negated = false);

    bool Equals(const Node* another_node) const override;

    void Accept(visitors::Visitor& visitor) const override {
        visitor.Visit(*this);
    }

    const DetailedMask& GetMask() const {
        return detailed_mask_;
    }

    bool GetNegated() const {
        return negated_;
    }

    size_t CountEdges() const {
        if (negated_) {
            return consts::kStateEdgesCount - detailed_mask_.Count();
        }
        return detailed_mask_.Count();
    }

    bool HasEdge(uint8_t ch) const {
        return detailed_mask_.Is(ch) != negated_;
    }

private:
    void EnsureInvariants() const;

private:
    DetailedMask detailed_mask_;
    bool negated_;
};

std::vector<CharSetNode::Range> ToSpecialRanges(CharSetNode::DetailedMask detailed_mask);

}  // namespace lib::regex::ast
