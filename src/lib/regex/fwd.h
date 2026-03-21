#pragma once

namespace lang::regex {

namespace errors {

class ParserError;

}  // namespace errors

namespace ast {

class Node;
class CharNode;
class WideCharNode;
class NodesBaseNode;
class ChoiceNode;
class SequenceNode;
class RepeatNode;

}  // namespace ast

namespace visitors {

class Visitor;
class AstPrinter;
class Formatter;

}  // namespace visitors

class Parser;

}  // namespace lang::regex
