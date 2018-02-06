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
#include "../../Buffer/includes/Buffer.h"

#include <cstddef>
#include <iostream>

using namespace std;

class ParseTree {
private:
	Buffer* buffer;
	Node* prog;
	int marker;

public:
	ParseTree(Buffer* buffer);
	virtual ~ParseTree();

	Node* getRoot();
	void add_rootNode(Node* node);
	void typeCheck(Node* node);
	CheckTypes::Type getEntryType(Node* node);
	void makeCode(Node* node);
};

#endif /* PARSER_INCLUDES_PARSETREE_H_ */
