/*
 * Node.cpp
 *
 *  Created on: 02.11.2016
 *      Author: dominik
 */

#include <cstddef>

#include "../includes/Node.h"

Node::Node(RuleType rule) {
	token = NULL;
	this->rule = rule;
	Leaf = true;
	childCounter = 0;
}

Node::Node(RuleType rule, Token* token) {
	this->token = token;
	this->rule = rule;
	Leaf = true;
	childCounter = 0;
}

Node::~Node() {
}

RuleType Node::getRuleType() {
	return rule;
}


int Node::countChilds() {
	return childCounter;
}

Node* Node::getChild(int i){
	return childs[i];
}

bool Node::add_ChildNode(Node* child) {
	int i = 0;
	while(this->childs[i] != NULL) {
		if (i > 6) {
			return false;
		}
		i++;
	}
	this->childs[i] = child;
	childCounter++;
	Leaf = false;
	return true;
}

Token* Node::getToken() {
	return this->token;
}

bool Node::isLeaf() {
	return Leaf;
}

void Node::setToken(Token* token) {
	this->token = token;
}
