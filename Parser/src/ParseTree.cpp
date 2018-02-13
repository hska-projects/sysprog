/*
 * ParseTree.cpp
 *
 *  Created on: 02.11.2016
 *      Author: dominik
 */

using namespace std;

#include <cstddef>
#include <fstream>

#include "../includes/ParseTree.h"

ParseTree::ParseTree() {
	this->prog = NULL;
	marker = 0;

	popen = new myString("Left Bracket"); //{
	minus = new myString("Minus"); //-
	open = new myString("Left Paranthesis"); //(
	emark = new myString("Exclamation"); //!

	plus = new myString("Plus"); //+
	star = new myString("Star"); //*
	colon = new myString("Colon"); //:
	lt = new myString("Less than"); //<
	gt = new myString("Greater than"); //>
	equals = new myString("Equals"); //=
	sonder = new myString("=:=");
	andd = new myString("And"); //&&
}

Node* ParseTree::getRoot() {
	return prog;
}

void ParseTree::add_rootNode(Node* node) {
	this->prog = node;
}

void ParseTree::typeCheck(Node* node) {
	switch (node->getRuleType()) {
	case PROG:
		// DECLS
		typeCheck(node->getChild(0));
		// STATEMENTS
		typeCheck(node->getChild(1));
		node->setType(CheckTypes::NOTYPE);
		break;

	case DECLS:
		// DECL
		if (node->getChild(0))
			typeCheck(node->getChild(0));
		// DECLS
		if (node->getChild(2))
			typeCheck(node->getChild(2));
		node->setType(CheckTypes::NOTYPE);
		break;

	case DECL:
		// (DECL::= int ARRAY identifier)
		if (node->countChilds() == 3) {
			// ARRAY
			if (node->getChild(1))
				typeCheck(node->getChild(1));
			// IDENTIFIER
			if (getEntryType(node->getChild(2)) != CheckTypes::NOTYPE) {
				cerr << "identifier already defined" << endl;
				node->setType(CheckTypes::ERRORTYPE);
			} else if (node->getChild(1)->getType() == CheckTypes::ERRORTYPE) {
				node->setType(CheckTypes::ERRORTYPE);
			} else {
				node->setType(CheckTypes::NOTYPE);
				if (node->getChild(1)->getType() == CheckTypes::ARRAYTYPE) {
					node->getChild(2)->getToken()->getInfoKey()->setType(
							CheckTypes::INTARRAYTYPE);
				} else {
					node->getChild(2)->getToken()->getInfoKey()->setType(
							CheckTypes::INTTYPE);
				}
			}
		}
		break;

	case ARRAY:
		// (ARRAY::=[integer])
		if (node->countChilds() == 3) {
			if (node->getChild(1)->getToken()->getInfoKey()->getValue() > 0) {
				node->setType(CheckTypes::ARRAYTYPE);
			} else {
				cerr << "no valid dimension" << endl;
				node->setType(CheckTypes::ERRORTYPE);
			}
		} else {
			node->setType(CheckTypes::NOTYPE);
		}
		break;

	case STATEMENTS:
		// STATEMENT
		if (node->getChild(0))
			typeCheck(node->getChild(0));
		// STATEMENTS
		if (node->getChild(2))
			typeCheck(node->getChild(2));
		node->setType(CheckTypes::NOTYPE);
		break;

	case STATEMENT:
		// (STATEMENT ::= identifier INDEX := EXP)
		if (node->getChild(0)->getRuleType() == ID) {
			// EXP
			typeCheck(node->getChild(3));
			// INDEX
			typeCheck(node->getChild(1));

			if (getEntryType(node->getChild(0)) == CheckTypes::NOTYPE) {
				cerr << "identifier not defined" << endl;
				node->setType(CheckTypes::ERRORTYPE);
			} else if (node->getChild(3)->getType() == CheckTypes::INTTYPE
					&& ((getEntryType(node->getChild(0)) == CheckTypes::INTTYPE
							&& node->getChild(1)->getType()
									== CheckTypes::NOTYPE)
							|| (getEntryType(node->getChild(0))
									== CheckTypes::INTARRAYTYPE
									&& node->getChild(1)->getType()
											== CheckTypes::ARRAYTYPE))) {
				node->setType(CheckTypes::NOTYPE);
			} else {
				cerr << "incompatible types" << endl;
				node->setType(CheckTypes::ERRORTYPE);
			}
		} else {
			switch (node->getChild(0)->getToken()->getTT()) {
			case WriteToken:     // (STATEMENT ::= write( EXP ))
				// EXP
				typeCheck(node->getChild(2));
				node->setType(CheckTypes::NOTYPE);
				break;

			case ReadToken:     // (STATEMENT ::= read( identifier INDEX))
				typeCheck(node->getChild(3));

				if (getEntryType(node->getChild(2)) == CheckTypes::ERRORTYPE
						|| getEntryType(node->getChild(2))
								== CheckTypes::NOTYPE) {
					cerr << "identifier not defined" << endl;
					node->setType(CheckTypes::ERRORTYPE);
				} else if ((getEntryType(node->getChild(2))
						== CheckTypes::INTTYPE
						&& node->getChild(3)->getType() == CheckTypes::NOTYPE)
						|| (getEntryType(node->getChild(2))
								== CheckTypes::INTARRAYTYPE
								&& node->getChild(3)->getType()
										== CheckTypes::ARRAYTYPE)) {
					node->setType(CheckTypes::NOTYPE);
				} else {
					cerr << "incompatible types" << endl;
					node->setType(CheckTypes::ERRORTYPE);
				}

				break;

			case OtherToken:     // (STATEMENT ::= { STATEMENTS })
				// check if OtherToken is "{"
				if (node->getChild(0)->getToken()->getInfoKey()->getString()->compare(
						*popen) == 0) {
					typeCheck(node->getChild(1));
					node->setType(CheckTypes::NOTYPE);
				}
				break;

			case IfToken:        // (STATEMENT ::= if ( EXP ) STATEMENT else STATEMENT)
				typeCheck(node->getChild(2));
				typeCheck(node->getChild(4));
				typeCheck(node->getChild(6));
				if (node->getChild(2)->getType() == CheckTypes::ERRORTYPE) {
					node->setType(CheckTypes::ERRORTYPE);
				} else {
					node->setType(CheckTypes::NOTYPE);
				}
				break;

			case WhileToken:     // (STATEMENT ::= while ( EXP ) STATEMENT)
				typeCheck(node->getChild(2));
				typeCheck(node->getChild(4));
				if (node->getChild(2)->getType() == CheckTypes::ERRORTYPE) {
					node->setType(CheckTypes::ERRORTYPE);
				} else {
					node->setType(CheckTypes::NOTYPE);
				}
				break;

			default:
				node->setType(CheckTypes::NOTYPE);
				break;
			}
		}
		break;

	case INDEX:
		// (INDEX ::= [ EXP ])
		if (node->countChilds() > 1) {
			// EXP
			typeCheck(node->getChild(1));
			if (node->getChild(1)->getType() == CheckTypes::ERRORTYPE) {
				node->setType(CheckTypes::ERRORTYPE);
			} else {
				node->setType(CheckTypes::ARRAYTYPE);
			}
		} else {
			node->setType(CheckTypes::NOTYPE);
		}
		break;

	case EXP:
		// (EXP ::= EXP2 OP_EXP)
		// EXP2
		typeCheck(node->getChild(0));
		// OP_EXP
		typeCheck(node->getChild(1));
		if (node->getChild(1)->getType() == CheckTypes::NOTYPE) {
			node->setType(node->getChild(0)->getType());
		} else if (node->getChild(0)->getType()
				!= node->getChild(1)->getType()) {
			node->setType(CheckTypes::ERRORTYPE);
		} else {
			node->setType(node->getChild(0)->getType());
		}
		break;

	case EXP2:
		switch (node->getChild(0)->getToken()->getTT()) {

		case OtherToken:
			// (EXP2 ::= ( EXP ))
			// check if OtherToken is "("
			if (node->getChild(0)->getToken()->getInfoKey()->getString()->compare(
					*open) == 0) {
				typeCheck(node->getChild(1));
				// this.type = EXP.type;
				node->setType(node->getChild(1)->getType());
				break;
			} else
			// (EXP2 ::= - EXP2)
			// check if OtherToken is "-"
			if (node->getChild(0)->getToken()->getInfoKey()->getString()->compare(
					*minus) == 0) {
				typeCheck(node->getChild(1));
				node->setType(node->getChild(1)->getType());
				break;
			} else
			// (EXP2 ::= ! EXP2)
			// check if OtherToken is "!"
			if (node->getChild(0)->getToken()->getInfoKey()->getString()->compare(
					*emark) == 0) {
				typeCheck(node->getChild(1));
				if (node->getChild(1)->getType() != CheckTypes::INTTYPE) {
					node->setType(CheckTypes::ERRORTYPE);
				} else {
					node->setType(CheckTypes::INTTYPE);
				}
				break;
			}

			break;
		case IdentifierToken:
			// (EXP2 ::= identifier INDEX)
			typeCheck(node->getChild(1));

			if (getEntryType(node->getChild(0)) == CheckTypes::NOTYPE) {
				cerr << "identifier not defined" << endl;
				node->setType(CheckTypes::ERRORTYPE);
			} else if (getEntryType(node->getChild(0)) == CheckTypes::INTTYPE
					&& node->getChild(1)->getType() == CheckTypes::NOTYPE) {
				node->setType(getEntryType(node->getChild(0)));
			} else if (getEntryType(node->getChild(0))
					== CheckTypes::INTARRAYTYPE
					&& node->getChild(1)->getType() == CheckTypes::ARRAYTYPE) {
				node->setType(CheckTypes::INTTYPE);
			} else {
				cerr << "no primitive types" << endl;
				node->setType(CheckTypes::ERRORTYPE);
			}

			break;

		case IntegerToken:
			node->setType(CheckTypes::INTTYPE);
			break;

		default:
			break;
		}
		break;

	case OP_EXP:
		// (OP_EXP ::= OP EXP)
		if (node->countChilds() > 1) {
			typeCheck(node->getChild(0));
			typeCheck(node->getChild(1));
			// this.type = EXP.type;
			node->setType(node->getChild(1)->getType());
		} else {
			node->setType(CheckTypes::NOTYPE);
		}
		break;

	case OP:
		switch (node->getChild(0)->getToken()->getTT()) {
		case OtherToken:
			if (node->getChild(0)->getToken()->getInfoKey()->getString()->compare(
					*plus) == 0) {
				node->setType(CheckTypes::OPPLUS);
			} else if (node->getChild(0)->getToken()->getInfoKey()->getString()->compare(
					*minus) == 0) {
				node->setType(CheckTypes::OPMINUS);
			} else if (node->getChild(0)->getToken()->getInfoKey()->getString()->compare(
					*star) == 0) {
				node->setType(CheckTypes::OPMULT);
			} else if (node->getChild(0)->getToken()->getInfoKey()->getString()->compare(
					*colon) == 0) {
				node->setType(CheckTypes::OPDIV);
			} else if (node->getChild(0)->getToken()->getInfoKey()->getString()->compare(
					*lt) == 0) {
				node->setType(CheckTypes::OPLESS);
			} else if (node->getChild(0)->getToken()->getInfoKey()->getString()->compare(
					*gt) == 0) {
				node->setType(CheckTypes::OPGREATER);
			} else if (node->getChild(0)->getToken()->getInfoKey()->getString()->compare(
					*equals) == 0) {
				node->setType(CheckTypes::OPEQUAL);
			} else if (node->getChild(0)->getToken()->getInfoKey()->getString()->compare(
					*sonder) == 0) {
				node->setType(CheckTypes::OPUNEQUAL);
			} else if (node->getChild(0)->getToken()->getInfoKey()->getString()->compare(
					*andd) == 0) {
				node->setType(CheckTypes::OPAND);
			}
			break;

		default:
			node->setType(CheckTypes::ERRORTYPE);
			break;
		}
		break;
		default:
			break;
	}
}

CheckTypes::Type ParseTree::getEntryType(Node* node) {
	return node->getToken()->getInfoKey()->getType();
}

void ParseTree::makeCode(Node* node) {
	if (!node) {
		return;
	}
	switch (node->getRuleType()) {
	// PROG := DECLS STATEMENTS
	case PROG:
		makeCode(node->getChild(0));
		makeCode(node->getChild(1));
		writeCode((char*)"STP\n");
		break;

		// DECLS := DECL; DECLS
	case DECLS:
		makeCode(node->getChild(0));
		if (node->getChild(2)) {
			makeCode(node->getChild(2));
		}
		break;

		// DECL := int ARRAY identifier
	case DECL:
		writeCode((char*)"DS $");
		writeCode(
				node->getChild(2)->getToken()->getInfoKey()->getString()->getStr());
		writeCode((char*)" ");
		makeCode(node->getChild(1));
		break;

		// ARRAY ::= [ integer ]
	case ARRAY:
		if (node->countChilds() != 1) {
			writeCode(
					node->getChild(1)->getToken()->getInfoKey()->getString()->getStr());
			writeCode((char*)"\n");
		} else {
			writeCode((char*)"1\n");
		}
		break;

		// STATEMENTS ::= STATEMENT; STATEMENTS
	case STATEMENTS:
		makeCode(node->getChild(0));
		if (node->getChild(2)) {
			makeCode(node->getChild(2));
		} else {
			writeCode((char*)"NOP\n");
		}
		break;

		//STATEMENT
	case STATEMENT:
		int m1;
		int m2;
		switch (node->getChild(0)->getRuleType()) {
		// STATEMENT ::= identifier INDEX := EXP
		case ID:
			makeCode(node->getChild(3));
			writeCode((char*)"LA $");
			writeCode(
					node->getChild(0)->getToken()->getInfoKey()->getString()->getStr());
			writeCode((char*)"\n");
			makeCode(node->getChild(1));
			writeCode((char*)"STR\n");
			break;

			// STATEMENT ::= write ( EXP )
		case WRITE:
			makeCode(node->getChild(2));
			writeCode((char*)"PRI\n");
			break;

			// STATEMENT ::= read ( identifier INDEX )
		case READ:
			writeCode((char*)"REA\n");
			writeCode((char*)"LA $");
			writeCode(
					node->getChild(2)->getToken()->getInfoKey()->getString()->getStr());
			writeCode((char*)"\n");
			makeCode(node->getChild(3));
			writeCode((char*)"STR\n");
			break;

			// STATEMENT ::= { STATEMENTS }
		case POPEN:
			makeCode(node->getChild(1));
			break;

			// STATEMENT ::= if ( EXP ) STATEMENT else STATEMENT
		case IF:
			m1 = marker++;
			m2 = marker++;
			makeCode(node->getChild(2));
			writeCode((char*)"JIN #m");
			writeCode(m1);
			writeCode((char*)"\n");
			makeCode(node->getChild(4));
			writeCode((char*)"JMP #m");
			writeCode(m2);
			writeCode((char*)"\n");
			writeCode((char*)"#m");
			writeCode(m1);
			writeCode((char*)" NOP\n");
			makeCode(node->getChild(6));
			writeCode((char*)"#m");
			writeCode(m2);
			writeCode((char*)" NOP\n");
			break;

			// STATEMENT ::= while ( EXP ) STATEMENT
		case WHILE:
			m1 = marker + 1;
			m2 = marker + 1;
			writeCode((char*)"#m");
			writeCode(m1);
			writeCode((char*)" NOP\n");
			makeCode(node->getChild(2));
			writeCode((char*)"JIN #m");
			writeCode(m2);
			writeCode((char*)"\n");
			makeCode(node->getChild(4));
			writeCode((char*)"JMP #m");
			writeCode(m1);
			writeCode((char*)"\n");
			writeCode((char*)"#m");
			writeCode(m2);
			writeCode((char*)" NOP\n");
			break;

		default:
			break;
		}
		break;

		// EXP ::= EXP2 OP_EXP
	case EXP:
		if (node->getChild(1)->getType() == CheckTypes::NOTYPE) {
			makeCode(node->getChild(0));
		} else if (node->getChild(1)->getChild(0)->getType()
				== CheckTypes::OPGREATER) {
			makeCode(node->getChild(1));
			makeCode(node->getChild(0));
			writeCode((char*)"LES\n");
		} else if (node->getChild(1)->getChild(0)->getType()
				== CheckTypes::OPUNEQUAL) {
			makeCode(node->getChild(0));
			makeCode(node->getChild(1));
			writeCode((char*)"NOT\n");
		} else {
			makeCode(node->getChild(0));
			makeCode(node->getChild(1));
		}
		break;

		// INDEX ::= [ EXP ] | empty
	case INDEX:
		if (node->countChilds() > 1) {
			makeCode(node->getChild(1));
			writeCode((char*)"ADD\n");
		}
		break;

		// EXP2
	case EXP2:
		switch (node->getChild(0)->getRuleType()) {

		// EXP2 ::= ( EXP )
		case OPEN:
			makeCode(node->getChild(1));
			break;

			// EXP2 ::= identifier INDEX
		case ID:
			writeCode((char*)"LA $");
			writeCode(
					node->getChild(0)->getToken()->getInfoKey()->getString()->getStr());
			writeCode((char*)"\n");
			makeCode(node->getChild(1));
			writeCode((char*)"LV\n");
			break;

			// EXP2 ::= integer
		case INTEGER:
			writeCode((char*)"LC ");
			writeCode(
					node->getChild(0)->getToken()->getInfoKey()->getString()->getStr());
			writeCode((char*)"\n");
			break;

			// EXP2 ::= - EXP2
		case MINUS:
			writeCode((char*)"LC 0\n");
			makeCode(node->getChild(1));
			writeCode((char*)"SUB\n");
			break;

			// EXP2 ::= ! EXP2
		case EMARK:
			makeCode(node->getChild(1));
			writeCode((char*)"NOT\n");
			break;

		default:
			break;
		}
		break;

		// OP_EXP ::= OP EXP | empty
	case OP_EXP:
		if (node->countChilds() > 1) {
			makeCode(node->getChild(1));
			makeCode(node->getChild(0));
		}
		break;

		// OP
	case OP:
		switch (node->getChild(0)->getRuleType()) {

		// OP ::= +
		case PLUS:
			writeCode((char*)"ADD\n");
			break;

			// OP ::= -
		case MINUS:
			writeCode((char*)"SUB\n");
			break;

			// OP ::= *
		case STAR:
			writeCode((char*)"MUL\n");
			break;

			// OP ::= /
		case COLON:
			writeCode((char*)"DIV\n");
			break;

			// OP ::= <
		case LT:
			writeCode((char*)"LES\n");
			break;

			// OP ::= >
		case GT:

			break;

			// OP ::= =
		case EQUALS:
			writeCode((char*)"EQU\n");
			break;

			// OP ::= =:=
		case SONDER:
			writeCode((char*)"EQU\n");
			break;

			// OP ::= &&
		case AND:
			writeCode((char*)"AND\n");
			break;

		default:
			break;
		}
		break;
	default:
		break;
	}
}

void ParseTree::writeCode(char* c) {
	myString temp(c);
	output += temp;
}

void ParseTree::writeCode(int value) {
    char* buffer = new char[32];
    sprintf(buffer, "%i", value);
    writeCode(buffer);
    delete [] buffer;
}


void ParseTree::createCodeFile() {
	ofstream myfile("test.code");
	if (myfile.is_open()) {
		myfile << output.getStr();
	}
}

ParseTree::~ParseTree() {
}
