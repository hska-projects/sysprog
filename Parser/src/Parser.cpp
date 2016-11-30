/*
 * Parser.cpp
 *
 */

#include "../includes/Parser.h"
#include "../includes/ParseTree.h"
#include "../includes/Rule.h"
#include "../../Symboltable/includes/Symboltable.h"
#include "../../Scanner/includes/Scanner.h"
#include <cstddef>

Parser::Parser(char* argv) {
	tree = new ParseTree();
	rules = new Rule();
	stab = new Symboltable();
	scanner = new Scanner(argv, stab);
	stab = new Symboltable();
}

Parser::~Parser() {
}

ParseTree Parser::parse() {
	//TODO call initializiation
	tree->add_rootNode(prog());


	return *tree;
}
Token Parser::getNextToken() {
	current = scanner->nextToken();
	if (current != NULL) {
		int col;
		col = current.getColoumn()
														if (col > 1) {
															if (current.getTTnummer() != 5)
																col -= (current.getInfoKey()->getString()->getLen());
															else {
																myString as("Assign");
																myString son("=:=");

																if (current.getInfoKey()->getString()->compare(as) == 0)
																	col -= 2;
																else if (current.getInfoKey()->getString()->compare(son) == 0)
																	col -= 3;
																else
																	col -= 1;
															}
														}
		current.setColumn(col);
	}
	return current;
}

void Parser::unexpectedTType(int type) {
	cerr << "ERROR: Expected: " << TTdef::getTokenType(type) << ", Got: " << TTdef::getTokenType(current.getTTnummer()) << endl;
	cerr << "Stopping..." << endl;
	exit(1);
}

Node* Parser::prog() {
	Node* prog = new Node(PROG);
	prog->add_ChildNode(decls());
	prog->add_ChildNode(stmts());
	return prog;
}

Node* Parser::decls() {
	Node* decls = new Node(DECLS);
	if(getNextToken() && current.getTTnummer() == 9) {//IntToken
		//DECL
		decls->add_ChildNode(decl());
		//;
		if(getNextToken()) {
			if(current.getTTnummer() == 5 && current.getInfoKey()->getString()->getStr() == ';') { // Other Token
				Node* sem = new Node(SEMICOLON, current);
				decls->add_ChildNode(sem);
			} else {
				unexpectedTType(5);
			}
		}
		//DECLS
		decls->add_ChildNode(this->decls());
	} else {
		Node* emtpy = new Node(EPSYLON);
		//epsylon
		decls->add_ChildNode(emtpy);
	}
	return decls;
}

Node* Parser::stmts() {
	Node* stmts = new Node(STATEMENTS);

	//STMT
	stmts->add_ChildNode(stmt());
	if(getNextToken()) {
		if(current.getTTnummer() == 5 && current.getInfoKey()->getString()->getStr() == ';') { // Other Token
			Node* sem = new Node(SEMICOLON, current);
			stmts->add_ChildNode(sem);
		} else {
			unexpectedTType(0);
		}
	}
	if(getNextToken()) {
		//DECLS
		stmts->add_ChildNode(this->stmts());
	} else {
		Node* emtpy = new Node(EPSYLON);
		//epsylon
		stmts->add_ChildNode(emtpy);
	}
	return decls;
}

Node* Parser::decl() {
	return NULL;
}

Node* Parser::stmt() {
//	if(current.getTTnummer() == 0) { // IdentifierToken
//		Node* id = new Node(IdentifierToken, current);
//		stmts->add_ChildNode(id);
//	} else {
//		unexpectedTType(0);
//	}
	return NULL;
}

Node* Parser::array() {
	return NULL;
}

Node* Parser::exp() {
	return NULL;
}

Node* Parser::exp2() {
	return NULL;
}

Node* Parser::index() {
	return NULL;
}

Node* Parser::op() {
	return NULL;
}

Node* Parser::op_exp() {
	return NULL;
}


void Parser::evaluateRule(Token* token) {
}

