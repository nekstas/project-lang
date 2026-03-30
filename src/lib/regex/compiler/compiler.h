#pragma once

#include "../algo/dfa/builder.h"
#include "../parser/parser.h"
#include "../visitors/nfa_builder.h"

namespace lib::regex {

class Compiler {
public:
    void Clear();
    size_t AddRegex(const std::string& regex);
    nfa::Nfa CompileToNfa() const;
    dfa::Dfa CompileToDfa() const;

private:
    Parser parser_;
    visitors::NfaBuilder nfa_builder_;
    algo::dfa::Builder dfa_builder_;
};

}  // namespace lib::regex
