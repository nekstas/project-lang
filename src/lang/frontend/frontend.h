#pragma once

#include "../../lib/lang/context/base_context.h"
#include "../../lib/lang/frontend/file_reader/file_reader.hpp"
#include "analyzer/static_constraints_stage.hpp"
#include "cli/command_line_args_stage.hpp"
#include "interpreter/interpreter_stage.hpp"
#include "lexer/regex_lexer.hpp"

namespace lang::frontend {

template <lib::lang::ContextLike Context>
using ReadFile = lib::lang::frontend::FileReader<Context>;

template <lib::lang::ContextLike Context>
using ParseCommandLineArgs = CommandLineArgsStage<Context>;

template <lib::lang::ContextLike Context>
using Lexer = RegexLexer<Context>;

template <lib::lang::ContextLike Context>
using Interpreter = InterpreterStage<Context>;

template <lib::lang::ContextLike Context>
using StaticConstraints = StaticConstraintsStage<Context>;

}  // namespace lang::frontend
