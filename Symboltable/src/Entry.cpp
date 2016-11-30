#include "../includes/Entry.h"
#include "../../Scanner/includes/TTdef.h"

Entry::Entry(char* str) {
	this->str = new myString(str);
	this->TokenType = IdentifierToken;
	this->value = -1;
	this->next = NULL;
}

Entry::Entry(char* str, TokenTypes tt) {
	this->str = new myString(str);
	this->TokenType = tt;
	this->value = -1;
	this->next = NULL;
}

Entry* Entry::getNext() {
	return this->next;
}

myString* Entry::getString() {
	return this->str;
}

TokenTypes Entry::getTT(){
	return this->TokenType;
}

char* Entry::getTokenType() {
	return TTdef::getTokenType(this->TokenType);
}

int Entry::getTTnumber() {
	return this->TokenType;
}

void Entry::setNext(Entry* newEntry) {
	this->next = newEntry;
}

void Entry::setValue(int v) {
	this->value = v;
}

Entry::~Entry() {
}
