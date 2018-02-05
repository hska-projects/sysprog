#ifndef SYMBOLTABLE_SRC_ENTRY_H_
#define SYMBOLTABLE_SRC_ENTRY_H_

#include <cstddef>

#include "myString.h"
#include "../../Scanner/includes/TTdef.h"

class Entry {
private:
	myString* str;
	TokenTypes TokenType;
	int value;
	Entry* next;

public:
	Entry(char* str);
	Entry(char* str, TokenTypes tt);
	myString* getString();
	TokenTypes getTT();
	char* getTokenType();
	int getTTnumber();
	Entry* getNext();
	int getValue();
	void setNext(Entry* newEntry);
	void setValue(int v);
	~Entry();
};

#endif
