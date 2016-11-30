#include "../includes/Token.h"

Token::Token(TokenTypes tt, int l, int c, Entry* infoKey) {
	this->TokenType = tt;
	this->line = l;
	this->coloumn = c;
	this->infoKey = infoKey;
}

char* Token::getTokenType() {
	return TTdef::getTokenType(this->TokenType);
}

TokenTypes Token::getTT() {
	return this->TokenType;
}

Entry* Token::getInfoKey() {
	return this->infoKey;
}

void Token::setColumn(int col) {
	coloumn = col;
}

int Token::getLine() {
	return this->line;
}

int Token::getColoumn() {
	return this->coloumn;
}

int Token::getTTnummer(){
	return this->TokenType;
}

Token::~Token() {
}
