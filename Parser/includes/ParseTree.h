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
	Node* prog;
	int marker;
	myString* popen;
	myString* minus;
	myString* open;
	myString* emark;

	myString* plus;
	myString* star;
	myString* colon;
	myString* lt;
	myString* gt;
	myString* equals;
	myString* sonder;
	myString* andd;

public:
	ParseTree();
	virtual ~ParseTree();

	Node* getRoot();
	void add_rootNode(Node* node);
	void typeCheck(Node* node);
	CheckTypes::Type getEntryType(Node* node);
	void makeCode(Node* node);
	void writeCode(char* c);
};

#endif /* PARSER_INCLUDES_PARSETREE_H_ */
