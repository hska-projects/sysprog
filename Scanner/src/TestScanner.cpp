#include "../includes/Scanner.h"
#include "../../Symboltable/includes/Symboltable.h"

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
using std::cerr;
using std::cout;

int main(int argc, char* argv[]) {

	if (argc < 2) {
		cerr << "no argv input found.\n";
		return EXIT_FAILURE;
	}

	cout << "Processing...\n";
	Symboltable* stab = new Symboltable();
	Buffer* buffer = new Buffer(argv[1]);
	Scanner* s = new Scanner(buffer, stab);
	Token* t;
	myString nl("\n");
	myString tb("\t");
	int z1;
	int z2;
	ofstream myfile("out.txt");
	if (myfile.is_open()) {
		t = s->nextToken();
		int col;
		while (t != NULL) {
			col = t->getColoumn();
			if (col > 1) {
				if (t->getTTnummer() != 5)
					col -= (t->getInfoKey()->getString()->getLen());
				else {
					myString as("Assign");
					myString a("And");
					myString son("=:=");

					if (t->getInfoKey()->getString()->compare(as) == 0 || t->getInfoKey()->getString()->compare(a) == 0)
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
				z1 = t->getInfoKey()->getString()->compare(nl);
				z2 = t->getInfoKey()->getString()->compare(tb);
				if (z1 != 0 && z2 != 0) {
					cerr << "Unknown Token Line: " << t->getLine()
							<< " Coloumn: " << col << " Symbol: "
							<< t->getInfoKey()->getString()->getStr() << "\n";
				}
				break;
			case 5: // Other Token
				myfile << left << setw(10) << "Token " << setw(20)
							<< t->getInfoKey()->getString()->getStr()
							<< setw(5) << "Line: " << setw(4) << t->getLine()
							<< setw(10) << " Coloumn: " << setw(5) << col
							<< "\n";
				break;
			case 6: //WriteToken
				myfile << left << setw(10) << "Token " << setw(20)
							<< t->getInfoKey()->getString()->getStr()
							<< setw(5) << "Line: " << setw(4) << t->getLine()
							<< setw(10) << " Coloumn: " << setw(5) << col
							<< "\n";
				break;
			case 7: //ReadToken
				myfile << left << setw(10) << "Token " << setw(20)
							<< t->getInfoKey()->getString()->getStr()
							<< setw(5) << "Line: " << setw(4) << t->getLine()
							<< setw(10) << " Coloumn: " << setw(5) << col
							<< "\n";
				break;
			case 8: //ElseToken
				myfile << left << setw(10) << "Token " << setw(20)
							<< t->getInfoKey()->getString()->getStr()
							<< setw(5) << "Line: " << setw(4) << t->getLine()
							<< setw(10) << " Coloumn: " << setw(5) << col
							<< "\n";
				break;
			case 9: //IntToken
				myfile << left << setw(10) << "Token " << setw(20)
							<< t->getInfoKey()->getString()->getStr()
							<< setw(5) << "Line: " << setw(4) << t->getLine()
							<< setw(10) << " Coloumn: " << setw(5) << col
							<< "\n";
				break;
			default:
				break;
			}
			t = s->nextToken();
		}
	} else
		cerr << "Unable to open file\n";
	cout << "stop\n";
	//stab->printTable();
	return EXIT_SUCCESS;
}

