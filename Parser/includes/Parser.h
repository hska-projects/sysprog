/*
 * Parser.h
 *
 *  Created on: 26 Oct., 2016
 *      Author: eido1011
 */

#ifndef Parser_H_
#define Parser_H_

#include "ParseTree.h"
#include "../Scanner/includes/Scanner.h"

class Parser {
public:
	ParseTree tree;
	Rule rules;
	Scanner scanner;

	Parser();
	virtual ~Parser();
	
	ParseTree parse();
	Node createNode(Rule rule, Token token);
	void evaluateRule(Token* token);
};

#endif /* Parser_H_ */
