/*
 * Parser.cpp
 *
 */

#include "../includes/Parser.h"
#include "../../Symboltable/includes/Symboltable.h"
#include <cstddef>

Parser::Parser(char* argv) {
	this->tree = new ParseTree();
	this->rules = new Rule();
	this->stab = new Symboltable();
	this->scanner = new Scanner(*argv, stab);
}

Parser::~Parser() {
}

ParseTree Parser::parse() {
	//TODO call initializiation
	current = tree.getRoot();

	Token* t;
	myString nl("\n");
	myString tb("\t");
	ofstream myfile("out.txt");
	if (myfile.is_open()) {
		t = scanner.nextToken();
		int col;
		while (t != NULL) {
			col = t->getColoumn();
			if (col > 1) {
				if (t->getTTnummer() != 5)
					col -= (t->getInfoKey()->getString()->getLen());
				else {
					myString as("Assign");
					myString son("=:=");

					if (t->getInfoKey()->getString()->compare(as) == 0)
						col -= 2;
					else if (t->getInfoKey()->getString()->compare(son) == 0)
						col -= 3;
					else
						col -= 1;
				}
			}
			switch (t->getTTnummer()) {
			case 0:
				// Identifier Token
				myfile << left << setw(10) << "Token " << setw(20)
						<< t->getTokenType() << "Line: " << setw(4)
						<< t->getLine() << setw(10) << " Coloumn: " << setw(5)
						<< col << " Lexem: "
						<< t->getInfoKey()->getString()->getStr() << "\n";
				break;
			case 1:
				// IfToken
				myfile << left << setw(10) << "Token " << setw(20)
						<< t->getTokenType() << "Line: " << setw(4)
						<< t->getLine() << setw(10) << " Coloumn: " << setw(5)
						<< col << "\n";
				break;
			case 2:
				// WhileToken
				myfile << left << setw(10) << "Token " << setw(20)
						<< t->getTokenType() << setw(20) << "Line: " << setw(4)
						<< t->getLine() << setw(10) << " Coloumn: " << setw(5)
						<< col << "\n";
				break;
			case 3:
				// Integer Token
				myfile << left << setw(10) << "Token " << setw(20)
						<< t->getTokenType() << setw(5) << "Line: " << setw(4)
						<< t->getLine() << setw(10) << " Coloumn: " << setw(5)
						<< col << " Value: "
						<< t->getInfoKey()->getString()->getStr() << "\n";
				break;
			case 4:
				// Unknown Token
				int z1 = t->getInfoKey()->getString()->compare(nl);
				int z2 = t->getInfoKey()->getString()->compare(tb);
				if (z1 != 0 && z2 != 0) {
					cerr << "Unknown Token Line: " << t->getLine()
							<< " Coloumn: " << col << " Symbol: "
							<< t->getInfoKey()->getString()->getStr() << "\n";
				}
				break;
			case 5: // Other Token
				myfile << left << setw(10) << "Token " << setw(20)
						<< t->getInfoKey()->getString()->getStr() << setw(5)
						<< "Line: " << setw(4) << t->getLine() << setw(10)
						<< " Coloumn: " << setw(5) << col << "\n";
				break;
			case 6: //WriteToken
				myfile << left << setw(10) << "Token " << setw(20)
						<< t->getInfoKey()->getString()->getStr() << setw(5)
						<< "Line: " << setw(4) << t->getLine() << setw(10)
						<< " Coloumn: " << setw(5) << col << "\n";
				break;
			case 7: //ReadToken
				myfile << left << setw(10) << "Token " << setw(20)
						<< t->getInfoKey()->getString()->getStr() << setw(5)
						<< "Line: " << setw(4) << t->getLine() << setw(10)
						<< " Coloumn: " << setw(5) << col << "\n";
				break;
			case 8: //ElseToken
				myfile << left << setw(10) << "Token " << setw(20)
						<< t->getInfoKey()->getString()->getStr() << setw(5)
						<< "Line: " << setw(4) << t->getLine() << setw(10)
						<< " Coloumn: " << setw(5) << col << "\n";
				break;
			case 9: //IntToken
				myfile << left << setw(10) << "Token " << setw(20)
						<< t->getInfoKey()->getString()->getStr() << setw(5)
						<< "Line: " << setw(4) << t->getLine() << setw(10)
						<< " Coloumn: " << setw(5) << col << "\n";
				break;
			default:
				break;
			}
			t = scanner.nextToken();
		}
	} else
		cerr << "Unable to open file\n";
	cout << "stop\n";

	return tree;
}

Node* Parser::createNode(Rule rule, Token* token) {
	Node* child = new Node(rule);
	if (token != NULL) {
		child->setToken(token);
	}
	//eventuell auslagern
	this->current->add_ChildNode(child);
	return child;
}

void Parser::evaluateRule(Token* token) {
}

