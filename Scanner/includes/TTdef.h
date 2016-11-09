#ifndef SCANNER_SRC_TTDEF_H_
#define SCANNER_SRC_TTDEF_H_

enum TokenTypes {
	IdentifierToken, IfToken, WhileToken, IntegerToken, UnknownToken, OtherToken, WriteToken, ReadToken, ElseToken, IntToken
};

class TTdef {
public:
	TTdef();
	static char* getTokenType(int val);
	~TTdef();
};

#endif
