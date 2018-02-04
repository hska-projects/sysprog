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

void ParseTree::add_rootNode(Node* node){
	this->prog = node;
}

bool ParseTree::typeCheck(Node* node){
	if(node->getRuleType() == PROG){
		typeCheck(node->getChild(0));
		typeCheck(node->getChild(1));
		/*if(node->getChild(3) != NULL) {
			return false;
		}*/
	} else if (node->getRuleType() == DECLS || node->getRuleType() == STATEMENTS) {
		if (node->countChilds() > 0) {
			typeCheck(node->getChild(0));
			typeCheck(node->getChild(1));
			typeCheck(node->getChild(2));
		}
	} else if (node->getRuleType() == DECL) {
		if (node->getChild(0)->getRuleType() != INT
				|| node->getChild(1)->getRuleType() != ARRAY
				|| node->getChild(2)->getRuleType() != ID) {
			return false;
		}
	}
	return true;
}

void ParseTree::makeCode(){
	// TODO
}

ParseTree::~ParseTree() {
}
