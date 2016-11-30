/*
 * Parser.h
 *
 *  Created on: 26 Oct., 2016
 *      Author: eido1011
 */

#ifndef Parser_H_
#define Parser_H_

#include "ParseTree.h"
#include "Rule.h"
#include "../../Scanner/includes/Scanner.h"
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
	ParseTree* tree;
	Rule* rules;
	Scanner* scanner;
	Symboltable* stab;
	Token* current;

public:
	Parser(char* argv);
	virtual ~Parser();
	
	ParseTree parse();
	Node* createNode(RuleType rule, Token* token);
	bool getNextToken();
	void evaluateRule(Token* token);
	Node* prog();
	Node* decls();
	Node* decl();
	Node* array();
	Node* stmt();
	Node* stmts();
	Node* exp();
	Node* exp2();
	Node* index();
	Node* op_exp();
	Node* op();
	void unexpectedTType(int type);
};

#endif /* Parser_H_ */
