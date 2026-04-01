#include <catch2/catch_test_macros.hpp>

#include <sstream>
#include <string>

#include "../../src/lang/frontend/frontend.h"
#include "../../src/lang/frontend/parser/recursive_descent_parser.hpp"
#include "../../src/lang/frontend/tokens_filter/tokens_filter.hpp"
#include "../../src/lib/flow/static_pipeline.hpp"
#include "../../src/lib/flow/stop_pipeline.hpp"
#include "../../src/lib/lang/context/base_context.h"
#include "../../src/lib/lang/source/program.h"

namespace {

struct Context : lib::lang::BaseContext {};

template <lib::lang::ContextLike Ctx>
class ReadProgram : public lib::flow::TypedStage<ReadProgram<Ctx>, Ctx, std::string, lib::lang::SourceDesc> {
public:
    lib::lang::SourceDesc Run(std::string code, Ctx& ctx) const {
        return ctx.src.template AddSource<lib::lang::source::Program>("test.lang", code);
    }

    std::string Name() const override {
        return "ReadProgram";
    }
};

struct RunResult {
    std::string output;
    std::string diagnostics;
    bool stopped = false;
};

RunResult RunProgram(const std::string& code, const std::string& input = "") {
    std::istringstream in(input);
    std::ostringstream out;

    auto pipeline = lib::flow::MakeStaticNamedPipeline<Context>("LangPipeline",
        ReadProgram<Context>{}, lang::frontend::Lexer<Context>{}, lang::frontend::TokensFilter<Context>{},
        lang::frontend::RecursiveDescentParser<Context>{}, lang::frontend::Interpreter<Context>{in, out});

    Context ctx;
    RunResult result;
    try {
        (void)pipeline.Run(code, ctx);
    } catch (const lib::flow::StopPipeline&) {
        result.stopped = true;
    }

    result.output = out.str();
    result.diagnostics = ctx.diag.GetDiagnosticsString(ctx);
    return result;
}

void RequireSuccess(const RunResult& result, const std::string& expected_output) {
    REQUIRE(result.output == expected_output);
    REQUIRE(result.diagnostics == "No diagnostics found.\n");
    REQUIRE_FALSE(result.stopped);
}

void RequireFatalContains(const RunResult& result, const std::string& needle) {
    REQUIRE(result.stopped);
    REQUIRE(result.diagnostics.find(needle) != std::string::npos);
}

TEST_CASE("Lang pipeline basic execution") {
    SECTION("Print literal") {
        const std::string code = R"(
fn main() {
  print(42);
}
)";
        auto result = RunProgram(code);
        RequireSuccess(result, "42\n");
    }

    SECTION("Input and arithmetic") {
        const std::string code = R"(
fn main() {
  let x: Int = input();
  print(x + 1);
}
)";
        auto result = RunProgram(code, "41");
        RequireSuccess(result, "42\n");
    }

    SECTION("If else") {
        const std::string code = R"(
fn main() {
  let x: Int = 7;
  if (x > 10) {
    print(1);
  } else {
    print(0);
  }
}
)";
        auto result = RunProgram(code);
        RequireSuccess(result, "0\n");
    }

    SECTION("While and assignment") {
        const std::string code = R"(
fn main() {
  mut i: Int = 1;
  mut sum: Int = 0;
  while (i <= 5) {
    sum = sum + i;
    i = i + 1;
  }
  print(sum);
}
)";
        auto result = RunProgram(code);
        RequireSuccess(result, "15\n");
    }

    SECTION("Function call and return") {
        const std::string code = R"(
fn add(a: Int, b: Int) -> Int {
  return a + b;
}

fn main() {
  print(add(2, 3));
}
)";
        auto result = RunProgram(code);
        RequireSuccess(result, "5\n");
    }

    SECTION("Unary minus and precedence") {
        const std::string code = R"(
fn main() {
  print(-2 * (3 + 4));
}
)";
        auto result = RunProgram(code);
        RequireSuccess(result, "-14\n");
    }

    SECTION("Comparison operators return 0 or 1") {
        const std::string code = R"(
fn main() {
  print(1 == 1);
  print(1 != 1);
  print(1 < 2);
  print(2 <= 2);
  print(3 > 2);
  print(3 >= 4);
}
)";
        auto result = RunProgram(code);
        RequireSuccess(result, "1\n0\n1\n1\n1\n0\n");
    }

    SECTION("Truthiness: non-zero is true, zero is false") {
        const std::string code = R"(
fn main() {
  if (-5) {
    print(1);
  } else {
    print(0);
  }
  if (0) {
    print(1);
  } else {
    print(0);
  }
}
)";
        auto result = RunProgram(code);
        RequireSuccess(result, "1\n0\n");
    }

    SECTION("Nested scopes and shadowing") {
        const std::string code = R"(
fn main() {
  let x: Int = 10;
  if (1) {
    let x: Int = 20;
    print(x);
  }
  print(x);
}
)";
        auto result = RunProgram(code);
        RequireSuccess(result, "20\n10\n");
    }

    SECTION("Uninitialized mutable variable defaults to zero") {
        const std::string code = R"(
fn main() {
  mut x: Int;
  print(x);
}
)";
        auto result = RunProgram(code);
        RequireSuccess(result, "0\n");
    }

    SECTION("Function without explicit return returns zero") {
        const std::string code = R"(
fn f() -> Int {
}

fn main() {
  print(f());
}
)";
        auto result = RunProgram(code);
        RequireSuccess(result, "0\n");
    }

    SECTION("Program from example.lang: positive n") {
        const std::string code = R"(
fn sum_range(mut a: Int, b: Int) -> Int {
  if (a > b) {
    return 0;
  }
  mut s = b;
  while (a != b) {
      s = s + a;
      a = a + 1;
  }
  return s;
}

fn main() {
  let n = input();
  mut result: Int;
  if (n >= 1) {
    result = sum_range(1, n);
  } else {
    result = -1;
  }
  print(result);
}
)";
        auto result = RunProgram(code, "5");
        RequireSuccess(result, "15\n");
    }

    SECTION("Program from example.lang: non-positive n") {
        const std::string code = R"(
fn sum_range(mut a: Int, b: Int) -> Int {
  if (a > b) {
    return 0;
  }
  mut s = b;
  while (a != b) {
      s = s + a;
      a = a + 1;
  }
  return s;
}

fn main() {
  let n = input();
  mut result: Int;
  if (n >= 1) {
    result = sum_range(1, n);
  } else {
    result = -1;
  }
  print(result);
}
)";
        auto result = RunProgram(code, "0");
        RequireSuccess(result, "-1\n");
    }

    SECTION("Runtime error is reported as fatal diagnostic") {
        const std::string code = R"(
fn main() {
  print(1 / 0);
}
)";
        auto result = RunProgram(code);
        REQUIRE(result.output.empty());
        RequireFatalContains(result, "Interpreter runtime error: Division by zero.");
    }

    SECTION("Runtime error: assignment to immutable variable") {
        const std::string code = R"(
fn main() {
  let x: Int = 1;
  x = 2;
}
)";
        auto result = RunProgram(code);
        RequireFatalContains(result, "Can't assign to immutable variable");
    }

    SECTION("Runtime error: unknown variable") {
        const std::string code = R"(
fn main() {
  print(x);
}
)";
        auto result = RunProgram(code);
        RequireFatalContains(result, "Unknown variable");
    }

    SECTION("Runtime error: unknown function") {
        const std::string code = R"(
fn main() {
  print(no_such_function());
}
)";
        auto result = RunProgram(code);
        RequireFatalContains(result, "Unknown function");
    }

    SECTION("Runtime error: wrong number of arguments") {
        const std::string code = R"(
fn add(a: Int, b: Int) -> Int {
  return a + b;
}

fn main() {
  print(add(1));
}
)";
        auto result = RunProgram(code);
        RequireFatalContains(result, "expects 2 arguments, got 1");
    }

    SECTION("Runtime error: duplicate function definition") {
        const std::string code = R"(
fn foo() {
}

fn foo() {
}

fn main() {
}
)";
        auto result = RunProgram(code);
        RequireFatalContains(result, "already defined");
    }

    SECTION("Runtime error: missing main") {
        const std::string code = R"(
fn foo() {
  print(1);
}
)";
        auto result = RunProgram(code);
        RequireFatalContains(result, "Function \"main\" is not defined.");
    }

    SECTION("Syntax fatal is still reported through diagnostics") {
        const std::string code = R"(
fn main() {
  let x = ;
}
)";
        auto result = RunProgram(code);
        REQUIRE(result.stopped);
        REQUIRE(result.diagnostics.find("Syntax error:") != std::string::npos);
    }
}

}  // namespace
