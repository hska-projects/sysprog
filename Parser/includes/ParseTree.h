/*
 * ParseTree.h
 *
 *  Created on: 02.11.2016
 *      Author: dominik
 */

#ifndef PARSER_INCLUDES_PARSETREE_H_
#define PARSER_INCLUDES_PARSETREE_H_

#include "Node.h"
#include "Rule.h"
#include <cstddef>
#include <iostream>

using namespace std;

class ParseTree {
private:
	Node* prog;
	Buffer* buffer;
	int marker;

public:
	ParseTree(Buffer* buffer);
	~ParseTree();

	Node* getRoot();
	void add_rootNode(Node* node);
	void typeCheck(Node* node);
	void makeCode(Node* node);
};

#endif /* PARSER_INCLUDES_PARSETREE_H_ */
