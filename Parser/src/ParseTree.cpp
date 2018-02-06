/*
 * ParseTree.cpp
 *
 *  Created on: 02.11.2016
 *      Author: dominik
 */

#include <cstddef>

#include "../includes/ParseTree.h"

ParseTree::ParseTree(Buffer* buffer) {
	this->prog = NULL;
	this->buffer = buffer;
	marker = 0;
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
		typeCheck(node->getChild(0));
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
		if (node->countChilds() == 3) {
			// ARRAY
			if (node->getChild(2))
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
/*
	case STATEMENT:
		// IDENTIFIER
		if (node->getChild(0)->getType() == CheckTypes::IDENTIFIER) {
			// EXP
			typeCheck(node->getChild(3));
			// INDEX
			typeCheck(node->getChild(1));
			if (get(node->getChild(0)) == CheckTypes::ERRORTYPE
					|| get(node->getChild(0)) == CheckTypes::NOTYPE) {
				cerr << "Identifier "
						<< node->getChild(0)->getToken()->getEntry()->getLexem()
						<< " not defined" << endl;
				node->setType(CheckTypes::ERRORTYPE);
			} else if (node->getChild(3)->getType() == CheckTypes::INTTYPE
					&& ((get(node->getChild(0)) == CheckTypes::INTTYPE
							&& node->getChild(1)->getType()
									== CheckTypes::NOTYPE)
							|| (get(node->getChild(0))
									== CheckTypes::INTARRAYTYPE
									&& node->getChild(1)->getType()
											== CheckTypes::ARRAYTYPE))) {
				node->setType(CheckTypes::NOTYPE);
			} else {
				cerr << "Identifier "
						<< node->getChild(0)->getToken()->getEntry()->getLexem()
						<< " incompatible types" << endl;
				node->setType(CheckTypes::ERRORTYPE);
			}
		} else {
			switch (node->getChild(0)->getToken()->getType()) {
			case PRINT:     // print ( EXP )
				typeCheck(node->getChild(2));
				node->setType(CheckTypes::NOTYPE);
				break;

			case T_READ:    // read ( identifier INDEX )
				typeCheck(node->getChild(3));

				if (get(node->getChild(2)) == CheckTypes::ERRORTYPE
						|| get(node->getChild(2)) == CheckTypes::NOTYPE) {
					cerr << "Identifier "
							<< node->getChild(2)->getToken()->getEntry()->getLexem()
							<< " not defined" << endl;
					node->setType(CheckTypes::ERRORTYPE);
				} else if ((get(node->getChild(2)) == CheckTypes::INTTYPE
						&& node->getChild(3)->getType() == CheckTypes::NOTYPE)
						|| (get(node->getChild(2)) == CheckTypes::INTARRAYTYPE
								&& node->getChild(3)->getType()
										== CheckTypes::ARRAYTYPE)) {
					node->setType(CheckTypes::NOTYPE);
				} else {
					cerr << "Identifier "
							<< node->getChild(2)->getToken()->getEntry()->getLexem()
							<< " incompatible types" << endl;
					node->setType(CheckTypes::ERRORTYPE);
				}

				break;

			case SIGN_LEFTANGLEBRACKET:     // { statements }
				typeCheck(node->getChild(1));
				node->setType(CheckTypes::NOTYPE);
				break;

			case IF:        // if ( EXP ) STATEMENT else STATEMENT
				typeCheck(node->getChild(2));
				typeCheck(node->getChild(4));
				typeCheck(node->getChild(6));
				if (node->getChild(2)->getType() == CheckTypes::ERRORTYPE) {
					node->setType(CheckTypes::ERRORTYPE);
				} else {
					node->setType(CheckTypes::NOTYPE);
				}
				break;

			case WHILE:     // while ( EXP ) STATEMENT
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
		if (node->countChilds() > 1) {
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
		typeCheck(node->getChild(0));
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
		switch (node->getChild(0)->getToken()->getType()) {
		case SIGN_LEFTBRACKET:
			typeCheck(node->getChild(1));
			node->setType(node->getChild(1)->getType());
			break;

		case IDENTIFIER:
			typeCheck(node->getChild(1));

			if (get(node->getChild(0)) == CheckTypes::NOTYPE) {
				cerr << "Identifier "
						<< node->getChild(0)->getToken()->getEntry()->getLexem()
						<< " not defined" << endl;
				node->setType(CheckTypes::ERRORTYPE);
			} else if (get(node->getChild(0)) == CheckTypes::INTTYPE
					&& node->getChild(1)->getType() == CheckTypes::NOTYPE) {
				node->setType(get(node->getChild(0)));
			} else if (get(node->getChild(0)) == CheckTypes::INTARRAYTYPE
					&& node->getChild(1)->getType() == CheckTypes::ARRAYTYPE) {
				node->setType(CheckTypes::INTTYPE);
			} else {
				cerr << "Identifier "
						<< node->getChild(0)->getToken()->getEntry()->getLexem()
						<< " no primitive types" << endl;
				node->setType(CheckTypes::ERRORTYPE);
			}

			break;

		case INTEGER:
			node->setType(CheckTypes::INTTYPE);
			break;

		case SIGN_SUBTRACTION:
			typeCheck(node->getChild(1));
			node->setType(node->getChild(1)->getType());
			break;

		case SIGN_EXCLAMATION:
			typeCheck(node->getChild(1));
			if (node->getChild(1)->getType() != CheckTypes::INTTYPE) {
				node->setType(CheckTypes::ERRORTYPE);
			} else {
				node->setType(CheckTypes::INTTYPE);
			}
			break;

		default:
			node->setType(CheckTypes::ERRORTYPE);
			break;
		}
		break;

	case OP_EXP:
		if (node->countChilds() > 1) {
			typeCheck(node->getChild(0));
			typeCheck(node->getChild(1));
			node->setType(node->getChild(1)->getType());
		} else {
			node->setType(CheckTypes::NOTYPE);
		}
		break;

	case OP:
		switch (node->getChild(0)->getToken()->getType()) {
		case SIGN_ADDITITON:
			node->setType(CheckTypes::OPPLUS);
			break;

		case SIGN_SUBTRACTION:
			node->setType(CheckTypes::OPMINUS);
			break;

		case SIGN_MULTIPLICATION:
			node->setType(CheckTypes::OPMULT);
			break;

		case SIGN_DIVISION:
			node->setType(CheckTypes::OPDIV);
			break;

		case SIGN_LT:
			node->setType(CheckTypes::OPLESS);
			break;

		case SIGN_GT:
			node->setType(CheckTypes::OPGREATER);
			break;

		case SIGN_ASSIGN:
			node->setType(CheckTypes::OPEQUAL);
			break;

		case SIGN_NE:
			node->setType(CheckTypes::OPUNEQUAL);
			break;

		case SIGN_AMPERSAND:
			node->setType(CheckTypes::OPAND);
			break;
*/
		default:
			node->setType(CheckTypes::ERRORTYPE);
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
		buffer->writeCode("STP\n");
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
		buffer->writeCode("DS $");
		buffer->writeCode(
				node->getChild(2)->getToken()->getInfoKey()->getString()->getStr());
		buffer->writeCode(" ");
		makeCode(node->getChild(1));
		break;

		// ARRAY ::= [ integer ]
	case ARRAY:
		if (node->countChilds() != 1) {
			buffer->writeCode(
					(char*) node->getChild(1)->getToken()->getInfoKey()->getValue());
			buffer->writeCode("\n");
		} else {
			buffer->writeCode("1\n");
		}
		break;

		// STATEMENTS ::= STATEMENT; STATEMENTS
	case STATEMENTS:
		makeCode(node->getChild(0));
		if (node->getChild(2)) {
			makeCode(node->getChild(2));
		} else {
			buffer->writeCode("NOP\n");
		}
		break;

		//STATEMENT
	case STATEMENT:
		int m1, m2;
		switch (node->getChild(0)->getRuleType()) {
		// STATEMENT ::= identifier INDEX := EXP
		case ID:
			makeCode(node->getChild(3));
			buffer->writeCode("LA $");
			buffer->writeCode(
					node->getChild(1)->getToken()->getInfoKey()->getString()->getStr());
			buffer->writeCode("\n");
			makeCode(node->getChild(1));
			buffer->writeCode("STR\n");
			break;

			// STATEMENT ::= write ( EXP )
		case WRITE:
			makeCode(node->getChild(2));
			buffer->writeCode("PRI\n");
			break;

			// STATEMENT ::= read ( identifier INDEX )
		case READ:
			buffer->writeCode("REA\n");
			buffer->writeCode("LA $");
			buffer->writeCode(
					node->getChild(2)->getToken()->getInfoKey()->getString()->getStr());
			buffer->writeCode("\n");
			makeCode(node->getChild(3));
			buffer->writeCode("STR\n");
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
			buffer->writeCode("JIN #m");
			buffer->writeCode((char*) m1);
			buffer->writeCode("\n");
			makeCode(node->getChild(4));
			buffer->writeCode("JMP #m");
			buffer->writeCode((char*) m2);
			buffer->writeCode("\n");
			buffer->writeCode("#m");
			buffer->writeCode((char*) m1);
			buffer->writeCode(" NOP\n");
			makeCode(node->getChild(6));
			buffer->writeCode("#m");
			buffer->writeCode((char*) m2);
			buffer->writeCode(" NOP\n");
			break;

			// STATEMENT ::= while ( EXP ) STATEMENT
		case WHILE:
			m1 = marker++;
			m2 = marker++;
			buffer->writeCode("#m");
			buffer->writeCode((char*) m1);
			buffer->writeCode(" NOP\n");
			makeCode(node->getChild(2));
			buffer->writeCode("JIN #m");
			buffer->writeCode((char*) m2);
			buffer->writeCode("\n");
			makeCode(node->getChild(4));
			buffer->writeCode("JMP #m");
			buffer->writeCode((char*) m1);
			buffer->writeCode("\n");
			buffer->writeCode("#m");
			buffer->writeCode((char*) m2);
			buffer->writeCode(" NOP\n");
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
			buffer->writeCode("LES\n");
		} else if (node->getChild(1)->getChild(0)->getType()
				== CheckTypes::OPUNEQUAL) {
			makeCode(node->getChild(0));
			makeCode(node->getChild(1));
			buffer->writeCode("NOT\n");
		} else {
			makeCode(node->getChild(0));
			makeCode(node->getChild(1));
		}
		break;

		// INDEX ::= [ EXP ] | empty
	case INDEX:
		if (node->countChilds() > 1) {
			makeCode(node->getChild(1));
			buffer->writeCode("ADD\n");
		}
		break;

		// EXP2
	case EXP2:
		switch (node->getChild(0)->getToken()->getTT()) {

		// EXP2 ::= ( EXP )
		case OPEN:
			makeCode(node->getChild(1));
			break;

			// EXP2 ::= identifier INDEX
		case ID:
			buffer->writeCode("LA $");
			buffer->writeCode(
					node->getChild(0)->getToken()->getInfoKey()->getString()->getStr());
			buffer->writeCode("\n");
			makeCode(node->getChild(1));
			buffer->writeCode("LV\n");
			break;

			// EXP2 ::= integer
		case INTEGER:
			buffer->writeCode("LC ");
			buffer->writeCode(
					(char*) node->getChild(0)->getToken()->getInfoKey()->getValue());
			buffer->writeCode("\n");
			break;

			// EXP2 ::= - EXP2
		case MINUS:
			buffer->writeCode("LC 0\n");
			makeCode(node->getChild(1));
			buffer->writeCode("SUB\n");
			break;

			// EXP2 ::= ! EXP2
		case EMARK:
			makeCode(node->getChild(1));
			buffer->writeCode("NOT\n");
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
			buffer->writeCode("ADD\n");
			break;

			// OP ::= -
		case MINUS:
			buffer->writeCode("SUB\n");
			break;

			// OP ::= *
		case STAR:
			buffer->writeCode("MUL\n");
			break;

			// OP ::= /
		case COLON:
			buffer->writeCode("DIV\n");
			break;

			// OP ::= <
		case LT:
			buffer->writeCode("LES\n");
			break;

			// OP ::= >
		case GT:

			break;

			// OP ::= =
		case EQUALS:
			buffer->writeCode("EQU\n");
			break;

			// OP ::= =:=
		case SONDER:
			buffer->writeCode("EQU\n");
			break;

			// OP ::= &&
		case AND:
			buffer->writeCode("AND\n");
			break;

		default:
			break;
		}
		break;
	default:
		break;
	}
}

ParseTree::~ParseTree() {
}
