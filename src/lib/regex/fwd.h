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

namespace nfa {

class State;
class StateWrapper;
class NfaWrapper;
class Nfa;

}  // namespace nfa

namespace visitors {

class Visitor;
class AstPrinter;
class Formatter;
class NfaBuilder;

}  // namespace visitors

namespace algo {

namespace nfa {

class Engine;
class Matcher;

}  // namespace nfa

class Matcher;

}  // namespace algo

class Parser;

}  // namespace lang::regex
