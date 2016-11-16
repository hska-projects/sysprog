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

void ParseTree::add_rootNode(Node* node){
	this->prog = node;
}

Node* ParseTree::getRoot() {
	return prog;
}
