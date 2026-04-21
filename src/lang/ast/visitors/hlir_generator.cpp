#include "hlir_generator.h"

#include "../../../lib/errors/errors.h"
#include "../../../lib/utils/utils.h"
#include "../../hlir/expr/lit/int_literal.h"
#include "../expr/lit/int_literal.h"

namespace lang::ast::visitors {

std::unique_ptr<hlir::Node> HlirGenerator::Generate(const Node* ast) {
    result_ = nullptr;
    if (ast) {
        ast->Accept(*this);
    }
    return std::move(result_);
}

void HlirGenerator::Visit(const expr::lit::IntLiteral& lit) {
    auto maybe_number = ::utils::ParseInt64(lit.GetValue());
    TEMP_ASSERT(maybe_number.has_value());
    result_ = std::make_unique<hlir::expr::lit::IntLiteral>(*maybe_number);
}

}  // namespace lang::ast::visitors
