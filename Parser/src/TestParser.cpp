#include "../includes/Parser.h"
#include <iostream>

int main (int argc, char* argv[]) {
	if (argc < 1) {
		cerr << "no argv input found.\n";
		return EXIT_FAILURE;
	}
	Parser* parser = new Parser(argv);
	ParseTree tree = parser->parse();
	return 1;
}
