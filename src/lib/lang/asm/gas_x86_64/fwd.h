#pragma once

namespace lib::lang::asm_::gas_x86_64 {

class Operand;

class Line;
class Instruction;
class Directive;
class Label;

class OpDstSrc;

namespace dir {

class IntelSyntax;
class Global;
class Section;

}  // namespace dir

namespace instr {

class Push;
class Pop;
class Mov;
class Sub;
class Ret;

}  // namespace instr

class Visitor;

}  // namespace lib::lang::asm_::gas_x86_64
