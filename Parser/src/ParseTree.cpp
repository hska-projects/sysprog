/*
 * ParseTree.cpp
 *
 *  Created on: 02.11.2016
 *      Author: dominik
 */

#include <cstddef>

#include "../includes/ParseTree.h"

ParseTree::ParseTree() {
	this->prog = NULL;
}

Node* ParseTree::getRoot() {
	return prog;
}

void ParseTree::add_rootNode(Node* node) {
	this->prog = node;
}

bool ParseTree::typeCheck(Node* node) {
	if (node->getRuleType() == PROG) {
		if (typeCheck(node->getChild(0)) && typeCheck(node->getChild(1)))
			return true;
	} else if (node->getRuleType() == DECLS) {
		// EPSYLON
		if (node->countChilds() == 1
				&& node->getChild(0)->getRuleType() == EPSYLON)
			return true;
		if (node->countChilds() == 3
		// DECL
				&& typeCheck(node->getChild(0))
				// SEMICOLON [;]
				&& node->getChild(1)->getRuleType() == SEMICOLON
				// DECLS
				&& typeCheck(node->getChild(2)))
			return true;
	} else if (node->getRuleType() == STATEMENTS) {
		// EPSYLON
		if (node->countChilds() == 1
				&& node->getChild(0)->getRuleType() == EPSYLON)
			return true;
		if (node->countChilds() == 3
		// STATEMENT
				&& typeCheck(node->getChild(0))
				// SEMICOLON [;]
				&& node->getChild(1)->getRuleType() == SEMICOLON
				// STATEMENTS
				&& typeCheck(node->getChild(2)))
			return true;
	} else if (node->getRuleType() == DECL) {
		if (node->getChild(0)->getRuleType() != INT
				|| node->getChild(1)->getRuleType() != ARRAY
				|| node->getChild(2)->getRuleType() != ID) {
			return false;
		}
	} else if (node->getRuleType() == ARRAY) {
		// EPSYLON
		if (node->countChilds() == 1
				&& node->getChild(0)->getRuleType() == EPSYLON)
			return true;
		// ARRAY
		if (node->countChilds() == 3
				&& node->getChild(0)->getRuleType() == SQUAREOPEN
				&& node->getChild(0)->getRuleType() == INT
				&& node->getChild(0)->getRuleType() == SQUARECLOSE)
			return true;
	} else if (node->getRuleType() == EXP) {
		// TODO
	}
	// TODO EXP2, rest..
	return false;
}

void ParseTree::makeCode() {
	// TODO
}

ParseTree::~ParseTree() {
}
