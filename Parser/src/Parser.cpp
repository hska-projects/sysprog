/*
 * Parser.cpp
 *
 */

#include "../includes/Parser.h"
#include "../includes/ParseTree.h"
#include "../includes/Rule.h"
#include "../../Symboltable/includes/Symboltable.h"
#include "../../Scanner/includes/Scanner.h"
#include "../includes/Node.h"
#include <cstddef>
#include <stddef.h>

Parser::Parser(char* argv[]) {
	current = NULL;
	tree = new ParseTree();
	rules = new Rule();
	stab = new Symboltable();
	scanner = new Scanner(argv[1], stab);
	popen = new myString("Left Bracket");//{
	pclose = new myString("Right Bracket");//}
	assign = new myString(":=");
	open = new myString("Left Paranthesis");//(
	close = new myString("Right Paranthesis");//)
	sem = new myString("Semicolon");//;
	suqareopen = new myString("Left Square Bracket");//[
	squareclose = new myString("Right Square Bracket");//]
	minus = new myString("Minus");//-
	emark = new myString("Exclamation");//!
	plus = new myString("Plus");//+
	star = new myString("Star");//*
	colon = new myString("Colon");//:
	lt = new myString("Less than");//<
	gt = new myString("Greater than");//>
	equals = new myString("Equals");//=
	sonder = new myString("=:=");
	andd = new myString("And");//&&
}

Parser::~Parser() {
}

ParseTree* Parser::parse() {
	cout << "Parsing started.." << endl;
	tree->add_rootNode(prog());
	cout << "Parsing done." << endl;
	return tree;
}

bool Parser::getNextToken() {
	current = scanner->nextToken();
	if (current != NULL) {
		int col;
		col = current->getColoumn();
		if (col > 1) {
			if (current->getTTnummer() != 5)
				col -= (current->getInfoKey()->getString()->getLen());
			else {
				if (current->getInfoKey()->getString()->compare(*assign) == 0 || current->getInfoKey()->getString()->compare(*andd) == 0)
					col -= 2;
				else if (current->getInfoKey()->getString()->compare(*sonder) == 0)
					col -= 3;
				else
					col -= 1;
			}
		}
		current->setColumn(col);
		return true;
	} else {
		current = NULL;
	}
	return false;
}

void Parser::unexpectedTType(int type) {
	if (current == NULL)
		cerr << "ERROR: Expected: " << TTdef::getTokenType(type) << ", current is NULL" << endl;
	else {
		cerr << "ERROR: Expected: " << TTdef::getTokenType(type) << ", Got: " << TTdef::getTokenType(current->getTTnummer()) << endl;
	}
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
	if(getNextToken()) {
		if (current->getTTnummer() == 9) {//IntToken
			//DECL
			decls->add_ChildNode(decl());
			//;
			getNextToken();
			if((current != NULL) && (current->getTTnummer() == 5 && current->getInfoKey()->getString()->compare(*sem) == 0)) { // Other Token
				Node* sem = new Node(SEMICOLON, current);
				decls->add_ChildNode(sem);

				//DECLS
				decls->add_ChildNode(this->decls());
			} else {
				unexpectedTType(5);
			}
		} else {
			Node* emtpy = new Node(EPSYLON);
			//epsylon
			decls->add_ChildNode(emtpy);
		}
	} else {
		Node* emtpy = new Node(EPSYLON);
		//epsylon
		decls->add_ChildNode(emtpy);
		current = NULL;
	}
	return decls;
}

Node* Parser::stmts() {
	Node* stmts = new Node(STATEMENTS);
	if(!(current == NULL) && (current->getTTnummer() == 0 || current->getTTnummer() == 6 || current->getTTnummer() == 7
			|| (current->getTTnummer() == 5 && current->getInfoKey()->getString()->compare(*popen) == 0)
			|| current->getTTnummer() == 1 || current->getTTnummer() == 2)) {
		//STMT
		stmts->add_ChildNode(stmt());
		getNextToken();
		if(current->getTTnummer() == 5 && current->getInfoKey()->getString()->compare(*sem) == 0) { // Other Token
			Node* sem = new Node(SEMICOLON, current);
			stmts->add_ChildNode(sem);


			getNextToken();
			//STMTS
			stmts->add_ChildNode(this->stmts());
		} else {
			unexpectedTType(0);
		}
	} else {
		Node* emtpy = new Node(EPSYLON);
		//epsylon
		stmts->add_ChildNode(emtpy);
	}
	return stmts;
}

Node* Parser::decl() {
	Node* decl = new Node(DECL);
	decl->add_ChildNode(new Node(INT, current));
	decl->add_ChildNode(array());
	if (current->getTTnummer() == 0) {
		decl->add_ChildNode(new Node(ID, current));
	}
	else {
		unexpectedTType(0);
	}
	return decl;
}

Node* Parser::stmt() {
	Node* stmt = new Node(STATEMENT);
	if(current->getTTnummer() == 0) { // IdentifierToken
		Node* id = new Node(ID, current);
		stmt->add_ChildNode(id);
		getNextToken();
		stmt->add_ChildNode(index());
		getNextToken();
		if(current->getTTnummer() == 5 && current->getInfoKey()->getString()->compare(*assign) == 0) { // Other
			Node* id = new Node(ASSIGN, current);
			stmt->add_ChildNode(id);

			getNextToken();
			stmt->add_ChildNode(exp());
		} else {
			unexpectedTType(0);
		}
	} else if (current->getTTnummer() == 6) { //Write
		Node* write = new Node(WRITE, current);
		stmt->add_ChildNode(write);
		getNextToken();
		if(current->getTTnummer() == 5 && current->getInfoKey()->getString()->compare(*open) == 0) {
			Node* klammer = new Node(OPEN, current);
			stmt->add_ChildNode(klammer);

			getNextToken();
			stmt->add_ChildNode(exp());
			getNextToken();
			if(current->getTTnummer() == 5 && current->getInfoKey()->getString()->compare(*close) == 0) {
				Node* klammer = new Node(CLOSE, current);
				stmt->add_ChildNode(klammer);
			}else {
				unexpectedTType(5);
			}
		}else {
			unexpectedTType(5);
		}
	} else if (current->getTTnummer() == 7) {//Read
		Node* read = new Node(READ, current);
		stmt->add_ChildNode(read);
		getNextToken();
		if(current->getTTnummer() == 5 && current->getInfoKey()->getString()->compare(*open) == 0) {
			Node* klammer = new Node(OPEN, current);
			stmt->add_ChildNode(klammer);

			getNextToken();
			if(current->getTTnummer() == 0) {//identifier
				Node* id = new Node(ID, current);
				stmt->add_ChildNode(id);

				getNextToken();
				stmt->add_ChildNode(index());
				getNextToken();
				if(current->getTTnummer() == 5 && current->getInfoKey()->getString()->compare(*close) == 0) {
					Node* klammer = new Node(CLOSE, current);
					stmt->add_ChildNode(klammer);
				} else {
					unexpectedTType(0);
				}
			}else {
				unexpectedTType(0);
			}
		} else {
			unexpectedTType(5);
		}
	} else if (current->getTTnummer() == 5 && current->getInfoKey()->getString()->compare(*popen) == 0) {//{
		Node* popen = new Node(POPEN, current);
		stmt->add_ChildNode(popen);
		getNextToken();
		stmt->add_ChildNode(stmts());
		getNextToken();
		if(current->getTTnummer() == 5 && current->getInfoKey()->getString()->compare(*pclose) == 0) {
			Node* pClose = new Node(PCLOSE, current);
			stmt->add_ChildNode(pClose);
		} else {
			unexpectedTType(5);
		}
	} else if (current->getTTnummer() == 1) {//If
		Node* ifT = new Node(IF, current);
		stmt->add_ChildNode(ifT);
		getNextToken();
		if(current->getTTnummer() == 5 && current->getInfoKey()->getString()->compare(*open) == 0) {
			Node* klammer = new Node(OPEN, current);
			stmt->add_ChildNode(klammer);

			getNextToken();
			stmt->add_ChildNode(exp());
			getNextToken();
			if(current->getTTnummer() == 5 && current->getInfoKey()->getString()->compare(*close) == 0) {
				Node* klammer = new Node(CLOSE, current);
				stmt->add_ChildNode(klammer);

				getNextToken();
				stmt->add_ChildNode(this->stmt());
				getNextToken();
				if(current->getTTnummer() == 8) {
					Node* elseT = new Node(ELSE, current);
					stmt->add_ChildNode(elseT);

					getNextToken();
					stmt->add_ChildNode(this->stmt());
				} else {
					unexpectedTType(8);
				}
			} else {
				unexpectedTType(5);
			}
		} else {
			unexpectedTType(5);
		}
	} else if (current->getTTnummer() == 2) {//While
		Node* whileT = new Node(WHILE, current);
		stmt->add_ChildNode(whileT);
		getNextToken();
		if(current->getTTnummer() == 5 && current->getInfoKey()->getString()->compare(*open) == 0) {
			Node* klammer = new Node(OPEN, current);
			stmt->add_ChildNode(klammer);

			getNextToken();
			stmt->add_ChildNode(exp());
			getNextToken();
			if(current->getTTnummer() == 5 && current->getInfoKey()->getString()->compare(*close) == 0) {
				Node* klammer = new Node(CLOSE, current);
				stmt->add_ChildNode(klammer);

				getNextToken();
				stmt->add_ChildNode(this->stmt());
			} else {
				unexpectedTType(5);
			}
		} else {
			unexpectedTType(5);
		}
	} else {
		unexpectedTType(0);
	}

	return stmt;
}

Node* Parser::array() {
	Node* arr = new Node(ARRAY);
	getNextToken();
	if(current->getTTnummer() == 0) { // IdentifierToken
		// EPSYLON
		arr->add_ChildNode(new Node(EPSYLON));
	}
	else {
		if(current->getTTnummer() == 5 && current->getInfoKey()->getString()->compare(*suqareopen) == 0) { // Other Token
			arr->add_ChildNode(new Node(SQUAREOPEN, current));
			getNextToken();
			if(current->getTTnummer() == 3) { // Integer Token
				arr->add_ChildNode(new Node(INTEGER, current));
				getNextToken();
				if(current->getTTnummer() == 5 && current->getInfoKey()->getString()->compare(*squareclose) == 0) { // Other Token
					arr->add_ChildNode(new Node(SQUARECLOSE, current));
					getNextToken();
				}
				else {
					unexpectedTType(5);
				}
			}
			else {
				unexpectedTType(3);
			}
		}
		else {
			unexpectedTType(5);
		}
	}
	return arr;
}

Node* Parser::exp() {
	Node* exp = new Node(EXP);
	exp->add_ChildNode(exp2());
	getNextToken();
	exp->add_ChildNode(op_exp());
	return exp;
}

Node* Parser::exp2() {
	Node* exp2 = new Node(EXP2);
	if(current->getTTnummer() == 5 && current->getInfoKey()->getString()->compare(*open) == 0) {
		Node* klammer = new Node(OPEN, current);
		exp2->add_ChildNode(klammer);
		getNextToken();
		exp2->add_ChildNode(exp());
		getNextToken();
		if(current->getTTnummer() == 5 && current->getInfoKey()->getString()->compare(*close) == 0) {
			Node* klammer = new Node(CLOSE, current);
			exp2->add_ChildNode(klammer);
		} else {
			unexpectedTType(5);
		}
	} else if (current->getTTnummer() == 0) {//identifier
		Node* id = new Node(ID, current);
		exp2->add_ChildNode(id);
		getNextToken();
		exp2->add_ChildNode(index());
	} else if (current->getTTnummer() == 3) {//integer
		exp2->add_ChildNode(new Node(INTEGER, current));
	} else if (current->getTTnummer() == 5 && current->getInfoKey()->getString()->compare(*minus) == 0) {
		exp2->add_ChildNode(new Node(MINUS, current));
		getNextToken();
		exp2->add_ChildNode(this->exp2());
	} else if (current->getTTnummer() == 5 && current->getInfoKey()->getString()->compare(*emark) == 0) {
		exp2->add_ChildNode(new Node(EMARK, current));
		getNextToken();
		exp2->add_ChildNode(this->exp2());
	} else {
		unexpectedTType(400); //Too many, "Error"
	}
	return exp2;
}

Node* Parser::index() {
	Node* index = new Node(INDEX);
	if(current->getTTnummer() == 5 && current->getInfoKey()->getString()->compare(*suqareopen) == 0) {
		Node* klammer = new Node(SQUAREOPEN, current);
		index->add_ChildNode(klammer);
		getNextToken();
		index->add_ChildNode(exp());
		getNextToken();
		if(current->getTTnummer() == 5 && current->getInfoKey()->getString()->compare(*pclose) == 0) {
			Node* klammer = new Node(SQUARECLOSE, current);
			index->add_ChildNode(klammer);
		} else {
			unexpectedTType(5);
		}
	} else {
		unexpectedTType(5);
	}
	return NULL;
}

Node* Parser::op() {
	Node* op = new Node(OP);
	if(current->getInfoKey()->getString()->compare(*plus) == 0) {
		op->add_ChildNode(new Node(PLUS, current));
	} else if (current->getInfoKey()->getString()->compare(*minus) == 0) {
		op->add_ChildNode(new Node(MINUS, current));
	} else if (current->getInfoKey()->getString()->compare(*star) == 0 ) {
		op->add_ChildNode(new Node(STAR, current));
	} else if (current->getInfoKey()->getString()->compare(*colon) == 0) {
		op->add_ChildNode(new Node(COLON, current));
	} else if (current->getInfoKey()->getString()->compare(*lt) == 0) {
		op->add_ChildNode(new Node(LT, current));
	} else if (current->getInfoKey()->getString()->compare(*gt) == 0) {
		op->add_ChildNode(new Node(GT, current));
	} else if (current->getInfoKey()->getString()->compare(*equals) == 0) {
		op->add_ChildNode(new Node(EQUALS, current));
	} else if (current->getInfoKey()->getString()->compare(*sonder) == 0) {
		op->add_ChildNode(new Node(SONDER, current));
	} else if (current->getInfoKey()->getString()->compare(*andd) == 0) {
		op->add_ChildNode(new Node(AND, current));
	} else {
		unexpectedTType(5);
	}
	return op;
}

Node* Parser::op_exp() {
	Node* op_exp = new Node(EXP);
	if(current->getTTnummer() == 5
			&& (current->getInfoKey()->getString()->compare(*plus) == 0
					|| current->getInfoKey()->getString()->compare(*minus) == 0
					|| current->getInfoKey()->getString()->compare(*star) == 0
					|| current->getInfoKey()->getString()->compare(*colon) == 0
					|| current->getInfoKey()->getString()->compare(*lt) == 0
					|| current->getInfoKey()->getString()->compare(*gt) == 0
					|| current->getInfoKey()->getString()->compare(*equals) == 0
					|| current->getInfoKey()->getString()->compare(*sonder) == 0
					|| current->getInfoKey()->getString()->compare(*andd) == 0)) {
		op_exp->add_ChildNode(op());
		getNextToken();
		op_exp->add_ChildNode(exp());
	} else {
		op_exp->add_ChildNode(new Node(EPSYLON));
	}
	return op_exp;
}
