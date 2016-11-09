
#ifndef SCANNER_SRC_TOKEN_H_
#define SCANNER_SRC_TOKEN_H_

#include <cstddef>

#include "../../Symboltable/includes/Entry.h"


class Token {
private:
	TokenTypes TokenType;
	int line;
	int coloumn;
	Entry* infoKey;

public:
	Token(TokenTypes tt, int l, int c, Entry* infoKey);
	TokenTypes getTT();
	char* getTokenType();
	int getTTnummer();
	int getLine();
	int getColoumn();
	Entry* getInfoKey();
	~Token();
};

#endif
