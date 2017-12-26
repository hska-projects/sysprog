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

class ParseTree {
private:
	Node* prog;

public:
	ParseTree();
	~ParseTree();

	Node* getRoot();
	void add_rootNode(Node* node);
	Node* getDecls();
	Node* getSTMTS();
};

#endif /* PARSER_INCLUDES_PARSETREE_H_ */
