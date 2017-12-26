#include "../includes/Parser.h"
#include <iostream>

int main (int argc, char* argv[]) {
	if (argc < 2) {
		cerr << "no argv input found.\n";
		return EXIT_FAILURE;
	}

	Parser* parser = new Parser(argv);
	ParseTree* tree = parser->parse();
	parser->typeCheck(tree->getRoot());
	return EXIT_SUCCESS;
}
