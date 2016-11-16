/*
 * Node.h
 *
 *  Created on: 02.11.2016
 *      Author: dominik
 */

#ifndef PARSER_INCLUDES_NODE_H_
#define PARSER_INCLUDES_NODE_H_

#include "../Scanner/includes/Token.h"
#include "Rule.h"

class Node : public ParseTree {
public:
	Rule rule;
	Token token;
	Node childs[7];
	Node(Rule rule);
	~Node();
	void setToken(Token token);
	bool add_Note(Node child);
	Token getToken();
};


#endif /* PARSER_INCLUDES_NODE_H_ */
