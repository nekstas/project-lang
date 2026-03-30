#include "compiler.h"

namespace lib::regex {

void Compiler::Clear() {
    nfa_builder_.Clear();
}

size_t Compiler::AddRegex(const std::string& regex) {
    THROW_IF(regex.empty(), ::errors::LogicError, "Can't compile empty regex.");
    auto ast_ptr = parser_.Parse(regex);
    ASSERT_NOT_NULL(ast_ptr);
    return nfa_builder_.ExtendFromAst(*ast_ptr);
}

nfa::Nfa Compiler::CompileToNfa() const {
    return nfa_builder_.GetNfa();
}

dfa::Dfa Compiler::CompileToDfa() const {
    return dfa_builder_.Build(CompileToNfa());
}

}  // namespace lib::regex
