/*
 * Symboltable.cpp
 * HashTable
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 *
 *	This header file contains the Hash Table class definition.
 *  Hash Table array elements consist of Linked List objects.
 */

#include "../includes/Symboltable.h"
#include "../includes/LinkedList.h"

// Constructs the empty Hash Table object.
// Array length is set to 193 by default.
Symboltable::Symboltable() {
	int tableLength = 193;
	array = new LinkedList[tableLength];
	length = tableLength;
	this->initSymbolTable();
}

// Returns an array location for a given Entry key.
int Symboltable::hash(char* str) {
	myString* EntryString = new myString(str);
	int value = 0;
	for (int i = 0; i < EntryString->getLen(); i++)
		value += EntryString->getStr()[i];
	int res = (value * EntryString->getLen()) % length;
	return res;
}

// Adds an Entry to the Hash Table.
Entry* Symboltable::insert(char* str) {
	Entry* search = this->lookup(str);
	if (search != NULL)
		return search;
	else {
		Entry* newEntry = new Entry(str);
		int index = hash(str);
		array[index].insertEntry(newEntry);
		return newEntry;
	}
}

// Adds an Entry to the Hash Table.
void Symboltable::insert(char* str, TokenTypes tt) {
	Entry* newEntry = new Entry(str, tt);
	int index = hash(str);
	array[index].insertEntry(newEntry);
}

// Returns an Entry from the Hash Table by key.
// If the Entry isn't found, a null pointer is returned.
Entry* Symboltable::lookup(char* str) {
	myString* EntryKey = new myString(str);
	int index = hash(str);
	return array[index].getEntry(*EntryKey);
}

// Deletes an Entry by key from the Hash Table.
// Returns true if the operation is successful.
bool Symboltable::remove(char* EntryKey) {
	int index = hash(EntryKey);
	return array[index].removeEntry(*lookup(EntryKey)->getString());
}

// Display the contents of the Hash Table to console window.
void Symboltable::printTable() {
	printf("\n\nHash Table:\n");
	for (int i = 0; i < length; i++) {
		printf("Array %d: ", i + 1);
		array[i].printList();
	}
}

// Prints a histogram illustrating the Entry distribution.
void Symboltable::printHistogram() {
	printf("\n\nHash Table Contains ");
	printf("%d Entrys total\n", getNumberOfEntrys());
	for (int i = 0; i < length; i++) {
		printf("%d:\t", i + 1);
		for (int j = 0; j < array[i].getLength(); j++)
			printf(" X");
		printf("\n");
	}
}

// Returns the number of locations in the Hash Table.
int Symboltable::getLength() {
	return length;
}

// Returns the number of Entrys in the Hash Table.
int Symboltable::getNumberOfEntrys() {
	int EntryCount = 0;
	for (int i = 0; i < length; i++)
		EntryCount += array[i].getLength();
	return EntryCount;
}

// Initialize SymbolTable
void Symboltable::initSymbolTable() {
	this->insert("while", WhileToken);
	this->insert("WHILE", WhileToken);
	this->insert("if", IfToken);
	this->insert("IF", IfToken);
	this->insert("write", WriteToken);
	this->insert("read", ReadToken);
	this->insert("else", ElseToken);
	this->insert("ELSE", ElseToken);
	this->insert("int", IntToken);

	/*
	 *
	 * Test if capital/small letter compare works
	 *
	myString s = "if";
	myString s2 = "IF";

	if (s.compare(s2) != 0)
		printf("\n%s\n", "IF != if");
	//printf("\n%d\n", );
	//printf("\n%d\n", capWhileEntry->EntryType);
	 *
	 */
}

// De-allocates all memory used for the Hash Table.
Symboltable::~Symboltable() {
	delete[] array;
}
