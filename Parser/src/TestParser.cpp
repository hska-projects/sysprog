#include "../includes/Parser.h"
#include <iostream>

int main (int argc, char* argv[]) {
	if (argc < 2) {
		cerr << "no argv input found.\n";
		return EXIT_FAILURE;
	}

	Parser* parser = new Parser(argv);
	ParseTree* tree = parser->parse();

	cout <<"begin typeCheck()";
	tree->typeCheck(tree->getRoot());

	cout <<"begin makeCode()";
	tree->makeCode();

	return EXIT_SUCCESS;
}
