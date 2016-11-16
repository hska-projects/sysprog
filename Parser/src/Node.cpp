/*
 * Node.cpp
 *
 *  Created on: 02.11.2016
 *      Author: dominik
 */

#include <cstddef>


Node::Node(Rule rule) {
	this->rule = rule;
}

Node::~Node() {

}

bool Node::add_Note(Node child){
	int i = 0;
	while(childs[i] != NULL) {
		if (i > 6) {
			return false;
		}
		i++;
	}
	childs[i] = child;
	return true;
}
Token Node::getToken() {
	return token;

}
void Node::setToken(Token token) {
	this->token = token;
}
