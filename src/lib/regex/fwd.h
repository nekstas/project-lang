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

namespace fa {

class State;
template <typename Derived, typename FaWrapperT>
class StateWrapper;
template <typename StateT>
class Fa;
template <typename Derived, typename StateT, typename FaT, typename StateWrapperT>
class FaWrapper;

}  // namespace fa

namespace dfa {

class State;
class StateWrapper;
class Dfa;
class DfaWrapper;

}  // namespace dfa

namespace nfa {

class State;
class StateWrapper;
class Nfa;
class NfaWrapper;

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

namespace dfa {

class Builder;
class Engine;
class Matcher;

}  // namespace dfa

class Matcher;

}  // namespace algo

class Parser;

}  // namespace lang::regex
