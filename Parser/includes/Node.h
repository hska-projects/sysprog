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
#include "../includes/CheckTypes.h"

class Node {

private:
	RuleType rule;
	enum CheckTypes::Type type;
	Token* token;
	Node* childs[7];
	int childCounter;
	bool Leaf;

public:
	Node(RuleType rule);
	Node(RuleType rule, Token* token);
	~Node();

	Node* getChild(int i);
	RuleType getRuleType();
	int countChilds();
	bool isLeaf();
	void setToken(Token* token);
	bool add_ChildNode(Node* child);
	Token* getToken();
	CheckTypes::Type getType();
	void setType(CheckTypes::Type type);
};

#endif /* PARSER_INCLUDES_NODE_H_ */
