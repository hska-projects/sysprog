/*
 * Node.h
 *
 *  Created on: 02.11.2016
 *      Author: dominik
 */

#ifndef PARSER_INCLUDES_NODE_H_
#define PARSER_INCLUDES_NODE_H_

#include "../../Scanner/includes/Token.h"
#include "../includes/Rule.h"

class Node {

private:
	RuleType rule;
	Token* token;
	Node* childs[7];
	bool Leaf;

public:
	Node(RuleType rule);
	Node(RuleType rule, Token* token);
	~Node();

	bool isLeaf();
	void setToken(Token* token);
	bool add_ChildNode(Node* child);
	Token* getToken();
};

#endif /* PARSER_INCLUDES_NODE_H_ */
