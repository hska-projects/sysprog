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

void ParseTree::typeCheck(Node* node) {
	switch (node->getRuleType()) {
	case PROG:
		typeCheck(node->getChild(0));
		typeCheck(node->getChild(1));
		// TODO node.setType
		break;

	case DECLS:
		// DECL
		if (node->getChild(0))
			typeCheck(node->getChild(0));
		// DECLS
		if (node->getChild(2))
			typeCheck(node->getChild(2));
		// TODO node.setType
		break;

	case DECL:
		break;

	case ARRAY:
		break;

	case STATEMENTS:
		break;

	case STATEMENT:
		break;

		// TODO EXP, rest..
	}
}

void ParseTree::makeCode() {
	// TODO
}

ParseTree::~ParseTree() {
}
