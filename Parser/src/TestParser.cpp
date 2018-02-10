#include "../includes/Parser.h"
#include <iostream>

int main (int argc, char* argv[]) {
	if (argc < 2) {
		cerr << "no argv input found.\n";
		return EXIT_FAILURE;
	}

	Parser* parser = new Parser(argv);
	ParseTree* tree = parser->parse();

	cout << "\nbegin typeCheck()" << endl;
	tree->typeCheck(tree->getRoot());
	cout << "done typeCheck()\n" << endl;

	cout << "begin makeCode()" << endl;
	tree->makeCode(tree->getRoot());
	tree->createCodeFile();
	cout << "done makeCode()" << endl;

	return EXIT_SUCCESS;
}
