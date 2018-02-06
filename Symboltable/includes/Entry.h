#ifndef SYMBOLTABLE_SRC_ENTRY_H_
#define SYMBOLTABLE_SRC_ENTRY_H_

#include <cstddef>

#include "myString.h"
#include "../../Scanner/includes/TTdef.h"
#include "../../Parser/includes/CheckTypes.h"

class Entry {
private:
	myString* str;
	TokenTypes TokenType;
	CheckTypes type;
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
	void setNext(Entry* newEntry);
	int getValue();
	void setValue(int v);
	CheckTypes getType();
	void setType(CheckTypes::Type type);
	~Entry();
};

#endif
