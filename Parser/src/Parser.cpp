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
		col = current.getColoumn();
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
		//STMTS
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
	Node* stmt = new Node(STATEMENT);
	if(current.getTTnummer() == 0) { // IdentifierToken
		Node* id = new Node(ID, current);
		stmt->add_ChildNode(id);
		if(getNextToken()) {
			stmt->add_ChildNode(index());
		}
		if(getNextToken()) {
			if(current.getTTnummer() == 5 && current.getInfoKey()->getString()->getStr() == ':=') { // Other
				Node* id = new Node(ASSIGN, current);
				stmt->add_ChildNode(id);
			} else {
				unexpectedTType(0);
			}
		}
		if(getNextToken()) {
			stmt->add_ChildNode(exp());
		}
	} else if (current.getTTnummer() == 6) { //Write
		Node* write = new Node(WRITE, current);
		stmt->add_ChildNode(write);
		if(getNextToken()) {
			if(current.getTTnummer() == 5 && current.getInfoKey()->getString()->getStr() == '(') {
				Node* klammer = new Node(OPEN, current);
				stmt->add_ChildNode(klammer);
			}
		}
		if(getNextToken()) {
			stmt->add_ChildNode(exp());
		}
		if(getNextToken()) {
			if(current.getTTnummer() == 5 && current.getInfoKey()->getString()->getStr() == ')') {
				Node* klammer = new Node(CLOSE, current);
				stmt->add_ChildNode(klammer);
			}
		}
	} else if (current.getTTnummer() == 7) {//Read
		Node* read = new Node(READ, current);
		stmt->add_ChildNode(read);
		if(getNextToken()) {
			if(current.getTTnummer() == 5 && current.getInfoKey()->getString()->getStr() == '(') {
				Node* klammer = new Node(OPEN, current);
				stmt->add_ChildNode(klammer);
			}
		}
		if(getNextToken()) {
			if(current.getTTnummer() == 0) {//identifier
				Node* id = new Node(ID, current);
				stmt->add_ChildNode(id);
			}
		}
		if(getNextToken()) {
			stmt->add_ChildNode(index());
		}
		if(getNextToken()) {
			if(current.getTTnummer() == 5 && current.getInfoKey()->getString()->getStr() == ')') {
				Node* klammer = new Node(CLOSE, current);
				stmt->add_ChildNode(klammer);
			}
		}
	} else if (current.getTTnummer() == 5 && current.getInfoKey()->getString()->getStr() == '{') {//{
		Node* popen = new Node(POPEN, current);
		stmt->add_ChildNode(popen);
		if(getNextToken()) {
			stmt->add_ChildNode(stmts());
		}
		if(getNextToken()) {
			if(current.getTTnummer() == 5 && current.getInfoKey()->getString()->getStr() == '}') {
				Node* pClose = new Node(PCLOSE, current);
				stmt->add_ChildNode(pClose);
			}
		}
	} else if (current.getTTnummer() == 1) {//If
		Node* ifT = new Node(IF, current);
		stmt->add_ChildNode(ifT);

	} else if (current.getTTnummer() == 2) {//While
	} else {
		unexpectedTType(0);
	}

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

