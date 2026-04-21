#pragma once

namespace lib::lang {

namespace symbols {

class Descriptor;
class Scope;
class SymbolTable;

class ValueDescriptor;
class StackValueDescriptor;
class LocalValueDescriptor;
class TempVariableDescriptor;
class FunctionDescriptor;

class FunctionScope;
class GlobalScope;

}  // namespace symbols

namespace llir {

class Instruction;
class Visitor;

namespace instr {

class LoadInt64;

}

}  // namespace llir

namespace engines {

class Sources;
class Diagnostics;
class Symbols;

}  // namespace engines

}  // namespace lib::lang

// TODO
