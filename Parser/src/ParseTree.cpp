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
		break;

	case DECLS:
		// DECL
		if (node->getChild(0))
			typeCheck(node->getChild(0));
		// DECLS
		if (node->getChild(2))
			typeCheck(node->getChild(2));
		break;

	case DECL:
		if (node->countChilds() == 3) {
			// ARRAY
			if (node->getChild(2))
				typeCheck(node->getChild(1));
			// IDENTIFIER
			if (node->getChild(2)->getType() != CheckTypes::NOTYPE) {
				cerr << "identifier already defined" << endl;
				node->setType(CheckTypes::ERRORTYPE);
			} else if (node->getChild(1)->getType() == CheckTypes::ERRORTYPE) {
				node->setType(CheckTypes::ERRORTYPE);
			} else {
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
		}
		break;

	case STATEMENTS:
		break;

	case STATEMENT:
		break;
	}
}

void ParseTree::makeCode(Node* node) {
	if (!node){
	        return;
	}
	switch (node->getRuleType()) {
	    // PROG := DECLS STATEMENTS
	    case RuleType::PROG:
	    	makeCode(node->getChild(0));
	    	makeCode(node->getChild(1));
	        buffer->writeCode("STP\n");
	        break;

	    // DECLS := DECL; DECLS
	    case RuleType::DECLS:
	    	makeCode(node->getChild(0));
	    	if (node->getChild(2)){
	    		makeCode(node->getChild(2));
	    	}
	    	break;

	    // DECL := int ARRAY identifier
	    case RuleType::DECL:
	    	buffer->writeCode("DS $");
	    	buffer->writeCode(node->getChild(2)->getToken()->getInfoKey()->getString()->getStr());
	    	buffer->writeCode(" ");
	    	makeCode(node->getChild(1));
	    	break;

	   	// ARRAY ::= [ integer ]
	    case RuleType::ARRAY:
	    	if (node->countChilds() != 1) {
	    		buffer->writeCode((char*)node->getChild(1)->getToken()->getInfoKey()->getValue());
	    		buffer->writeCode("\n");
	    	} else {
	    		buffer->writeCode("1\n");
	    	}
	    	break;

	    // STATEMENTS ::= STATEMENT; STATEMENTS
	    case RuleType::STATEMENTS:
	    	makeCode(node->getChild(0));
	    	if (node->getChild(2))
	    		makeCode(node->getChild(2));
	    	else
	    		buffer->writeCode("NOP\n");
	    	break;

	    //STATEMENT
	    case RuleType::STATEMENT:
	    	int m1, m2;
	    	switch (node->getChild(0)->getRuleType()) {
	    		case ID:
	    			makeCode(node->getChild(3));
	    			buffer->writeCode("LA $");
	    			buffer->writeCode(node->getChild(1)->getToken()->getInfoKey()->getString()->getStr());
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
	    			buffer->writeCode(node->getChild(2)->getToken()->getInfoKey()->getString()->getStr());
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
	    			buffer->writeCode((char*)m1);
	    			buffer->writeCode("\n");
	    			makeCode(node->getChild(4));
	    			buffer->writeCode("JMP #m");
	    			buffer->writeCode((char*)m2);
	    			buffer->writeCode("\n");
	    			buffer->writeCode("#m");
	    			buffer->writeCode((char*)m1);
	    			buffer->writeCode(" NOP\n");
	    			makeCode(node->getChild(6));
	    			buffer->writeCode("#m");
	    			buffer->writeCode((char*)m2);
	    			buffer->writeCode(" NOP\n");
	    			break;

	    			// STATEMENT ::= while ( EXP ) STATEMENT
	    		case WHILE:
	    			m1 = marker++;
	    			m2 = marker++;
	    			buffer->writeCode("#m");
	    			buffer->writeCode((char*)m1);
	    			buffer->writeCode(" NOP\n");
	    			makeCode(node->getChild(2));
	    			buffer->writeCode("JIN #m");
	    			buffer->writeCode((char*)m2);
	    			buffer->writeCode("\n");
	    			makeCode(node->getChild(4));
	    			buffer->writeCode("JMP #m");
	    			buffer->writeCode((char*)m1);
	    			buffer->writeCode("\n");
	    			buffer->writeCode("#m");
	    			buffer->writeCode((char*)m2);
	    			buffer->writeCode(" NOP\n");
	    			break;

	    		default:
	    			break;
	    	}
	    	break;

	    	// EXP ::= EXP2 OP_EXP
	    	case RuleType::EXP:
	    		if(node->getChild(1)->getType() == CheckTypes::NOTYPE) {
	    			makeCode(node->getChild(0));
	    		} else if (node->getChild(1)->getChild(0)->getType() == CheckTypes::OPGREATER) {
	    			makeCode(node->getChild(1));
	    			makeCode(node->getChild(0));
	    			buffer->writeCode("LES\n");
	    		} else if (node->getChild(1)->getChild(0)->getType() == CheckTypes::OPUNEQUAL) {
	    			makeCode(node->getChild(0));
	    			makeCode(node->getChild(1));
	    			buffer->writeCode("NOT\n");
	    		} else {
	    			makeCode(node->getChild(0));
	    			makeCode(node->getChild(1));
	    		}
	    		break;
	    	/*

	        // EXP ::= EXP2 OP_EXP
	        case RuleType::EXP:
	            if(node->getChildNode(1)->getType() == RuleType::NOTYPE) {
	                makeCode(node->getChildNode(0));
	            } else if (node->getChildNode(1)->getChildNode(0)->getType() == RuleType::OPGREATER) {
	                makeCode(node->getChildNode(1));
	                makeCode(node->getChildNode(0));
	                buffer->writeCode("LES\n");
	            } else if (node->getChildNode(1)->getChildNode(0)->getType() == RuleType::OPUNEQUAL) {
	                makeCode(node->getChildNode(0));
	                makeCode(node->getChildNode(1));
	                buffer->writeCode("NOT\n");
	            } else {
	                makeCode(node->getChildNode(0));
	                makeCode(node->getChildNode(1));
	            }
	            break;

	        // INDEX ::= [ EXP ] | empty
	        case RuleType::INDEX:
	            if (node->getChildNodesCount() > 1) {
	                makeCode(node->getChildNode(1));
	                buffer->writeCode("ADD\n");
	            }
	            break;

	        // EXP2
	        case RuleType::EXP2:
	            switch (node->getChildNode(0)->getToken()->getType()) {

	                // EXP2 ::= ( EXP )
	                case SIGN_LEFTBRACKET:
	                    makeCode(node->getChildNode(1));
	                    break;

	                // EXP2 ::= identifier INDEX
	                case IDENTIFIER:
	                    buffer->writeCode("LA $");
	                    buffer->writeCode(node->getChildNode(0)->getToken()->getEntry()->getLexem());
	                    buffer->writeCode("\n");
	                    makeCode(node->getChildNode(1));
	                    buffer->writeCode("LV\n");
	                    break;

	                // EXP2 ::= integer
	                case INTEGER:
	                    buffer->writeCode("LC ");
	                    buffer->writeCode(node->getChildNode(0)->getToken()->getValue());
	                    buffer->writeCode("\n");
	                    break;

	                // EXP2 ::= - EXP2
	                case SIGN_SUBTRACTION:
	                    buffer->writeCode("LC 0\n");
	                    makeCode(node->getChildNode(1));
	                    buffer->writeCode("SUB\n");
	                    break;

	                // EXP2 ::= ! EXP2
	                case SIGN_EXCLAMATION:
	                    makeCode(node->getChildNode(1));
	                    buffer->writeCode("NOT\n");
	                    break;

	                default:
	                    break;
	            }
	            break;

	        // OP_EXP ::= OP EXP | empty
	        case RuleType::OP_EXP:
	            if (node->getChildNodesCount() > 1) {
	                makeCode(node->getChildNode(1));
	                makeCode(node->getChildNode(0));
	            }
	            break;

	        // OP
	        case RuleType::OP:
	            switch (node->getChildNode(0)->getToken()->getType()) {

	                // OP ::= +
	                case SIGN_ADDITITON:
	                    buffer->writeCode("ADD\n");
	                    break;

	                // OP ::= -
	                case SIGN_SUBTRACTION:
	                    buffer->writeCode("SUB\n");
	                    break;

	                // OP ::= *
	                case SIGN_MULTIPLICATION:
	                    buffer->writeCode("MUL\n");
	                    break;

	                // OP ::= /
	                case SIGN_DIVISION:
	                    buffer->writeCode("DIV\n");
	                    break;

	                // OP ::= <
	                case SIGN_LT:
	                    buffer->writeCode("LES\n");
	                    break;

	                // OP ::= >
	                case SIGN_GT:

	                    break;

	                // OP ::= =
	                case SIGN_ASSIGN:
	                    buffer->writeCode("EQU\n");
	                    break;

	                // OP ::= <=>
	                case SIGN_NE:
	                    buffer->writeCode("EQU\n");
	                    break;

	                // OP ::= &
	                case SIGN_AMPERSAND:
	                    buffer->writeCode("AND\n");
	                    break;

	                default:
	                    break;
	            }
	            break;
*/
	        default:
	            break;
	    }
}

ParseTree::~ParseTree() {
}
