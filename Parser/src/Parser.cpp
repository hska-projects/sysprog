/*
 * Parser.cpp
 *
 */

#include "../includes/Parser.h"
#include "../includes/ParseTree.h"
#include "../includes/Rule.h"
#include "../../Symboltable/includes/Symboltable.h"
#include "../../Scanner/includes/Scanner.h"
#include <cstddef>

Parser::Parser(char* argv) {
	tree = new ParseTree();
	rules = new Rule();
	stab = new Symboltable();
	scanner = new Scanner(argv, stab);
	stab = new Symboltable();
}

Parser::~Parser() {
}

ParseTree Parser::parse() {
	//TODO call initializiation
	tree->add_rootNode(prog());


	return *tree;
}

Node* Parser::prog() {
	Node* prog = new Node(PROG);
	prog->add_ChildNode(decls());
	prog->add_ChildNode(stmts());
	return prog;
}

Node* Parser::decls() {
	return NULL;
}

Node* Parser::stmts() {
	return NULL;
}

Node* Parser::decl() {
	return NULL;
}

Node* Parser::stmt() {
	return NULL;
}

Node* Parser::array() {
	return NULL;
}

Node* Parser::exp() {
	return NULL;
}

Node* Parser::exp2() {
	return NULL;
}

Node* Parser::index() {
	return NULL;
}

Node* Parser::op() {
	return NULL;
}

Node* Parser::op_exp() {
	return NULL;
}

Token* Parser::getNextToken(RuleType rule) {
	return NULL;
}


void Parser::evaluateRule(Token* token) {
}

