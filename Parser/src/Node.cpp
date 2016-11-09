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

void Node::add_Note(Node child){
	int i = 0;
	while(childs[i] != NULL) {
		i++;
	}
	childs[i] = child;
}
Token Node::getToken() {
	return token;

}
void Node::setToken(Token token) {
	this->token = token;
}
