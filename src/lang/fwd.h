#pragma once

namespace lang {

namespace ast {

class Node;

class Expression;

// class Statement;

namespace expr {

class Literal;

namespace lit {

class IntLiteral;

}

// class BinaryExpression;

}  // namespace expr

class Visitor;

namespace visitors {

class AstPrinter;
class HlirGenerator;

}  // namespace visitors

}  // namespace ast

namespace hlir {

class Node;

class Expression;

namespace expr {

class Literal;

namespace lit {

class IntLiteral;

}

}  // namespace expr

class Visitor;

namespace visitors {

class HlirPrinter;

}

}  // namespace hlir

}  // namespace lang
