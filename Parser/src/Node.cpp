/*
 * Node.cpp
 *
 *  Created on: 02.11.2016
 *      Author: dominik
 */

#include <cstddef>


Node::Node(RuleType rule) {
	token = NULL;
	this->rule = rule;
	Leaf = false;
}

Node::Node(RuleType rule, Token* token) {
	this->token = *token;
	this->rule = rule;
	Leaf = true;
}

Node::~Node() {
}

bool Node::add_ChildNode(Node* child) {
	int i = 0;
	while(this->childs[i] != NULL) {
		if (i > 6) {
			return false;
		}
		i++;
	}
	this->childs[i] = *child;
	return true;
}

Token* Node::getToken() {
	return this->token;
}

bool Node::isLeaf() {
	return Leaf;
}

void Node::setToken(Token token) {
	this->token = token;
	Leaf = true;
}
