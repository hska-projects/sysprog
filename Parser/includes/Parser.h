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
#include "Node.h"
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
	myString* popen;
	myString* pclose;
	myString* assign;
	myString* open;
	myString* close;
	myString* sem;
	myString* suqareopen;
	myString* squareclose;
	myString* minus;
	myString* emark;
	myString* plus;
	myString* star;
	myString* colon;
	myString* lt;
	myString* gt;
	myString* equals;
	myString* sonder;
	myString* andd;
	bool wasEpsylon;

public:
	Parser(char* argv[]);
	virtual ~Parser();
	
	ParseTree* parse();
	bool getNextToken();
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
