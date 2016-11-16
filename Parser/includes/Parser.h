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
#include "../../Symboltable/includes/Symboltable.h"

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
using std::cerr;
using std::cout;

class Parser {
private:
	ParseTree tree;
	Rule rules;
	Scanner scanner;
	Symboltable* stab;
	Node* current;

public:
	Parser(char* argv);
	virtual ~Parser();
	
	ParseTree parse();
	Node* createNode(Rule rule, Token* token);
	void evaluateRule(Token* token);
};

#endif /* Parser_H_ */
