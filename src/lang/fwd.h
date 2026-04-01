#pragma once

namespace lang {

namespace ast {

class Node;
class Program;

class Expression;
class Statement;

namespace expr {

class Literal;

namespace lit {

class IntLiteral;

}

class BinaryExpression;
class UnaryExpression;
class FunctionCallExpression;
class VariableExpression;

}  // namespace expr

namespace stmt {

class FunctionDefineNode;
class IfStatement;
class IfElseStatement;
class WhileStatement;
class BlockStatement;
class VariableDeclareStatement;
class AssignmentStatement;
class ReturnStatement;
class FunctionCallStatement;

}  // namespace stmt

class Visitor;

namespace visitors {

class AstPrinter;

}

}  // namespace ast

}  // namespace lang
