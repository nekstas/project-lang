#pragma once

namespace lang {

namespace ast {

class Node;

class Expression;
class Statement;

namespace expr {

class Literal;

namespace lit {

class IntLiteral;

}

class BinaryExpression;

}  // namespace expr

class Visitor;

namespace visitors {

class AstPrinter;

}

}  // namespace ast

}  // namespace lang
