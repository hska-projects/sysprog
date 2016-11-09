/*
 * Parser.cpp
 *
 */

#include "../includes/Parser.h"
#include "../../Symboltable/includes/Symboltable.h"
#include <cstddef>


Parser::Parser(char* argv) {
	tree = new ParseTree();
	rules = new Rule();
	stab = new Symboltable();
	scanner = new Scanner(*argv, stab);
}

Parser::~Parser() {
}

ParseTree Parser::parse() {
	//TODO call initializiation
	return tree;
}

Node Parser::createNode(Rule rule, Token token){
	Node child = new Node(rule);
	if (token != NULL) {
		child.setToken(token);
	}
	//eventuell auslagern
	current.add_Note(child);
	return child;
}

void Parser::evaluateRule(Token* token) {
}

