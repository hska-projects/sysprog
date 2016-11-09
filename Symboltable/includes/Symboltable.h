/*
 * Symboltable.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 *
 *  This header file contains the Hash Table class declaration.
 *  Hash Table array elements consist of Linked List objects.
 */

#ifndef SYMBOLTABLE_H_
#define SYMBOLTABLE_H_

#include "LinkedList.h"

class Symboltable {

private:
	// Array is a reference to an array of Linked Lists.
	LinkedList* array;

	// Length is the size of the Hash Table array.
	int length;

	// Returns an array location for a given Entry key.
	int hash(char* EntryString);

public:
	// Constructs the empty Hash Table object.
	// Array length is set to 13 by default.
	Symboltable();

	// Adds an Entry to the Hash Table.
	Entry* insert(char* str);
	// Adds an Entry to the Hash Table.
	//void insert(Entry* newEntry);
	void insert(char* str, TokenTypes tt);

	// Deletes an Entry by key from the Hash Table.
	// Returns true if the operation is successful.
	bool remove(char* EntryKey);

	// Returns an Entry from the Hash Table by key.
	// If the Entry isn't found, a null pointer is returned.
	Entry* lookup(char* str);

	// Display the contents of the Hash Table to console window.
	void printTable();

	// Prints a histogram illustrating the Entry distribution.
	void printHistogram();

	// Returns the number of locations in the Hash Table.
	int getLength();

	// Returns the number of Entrys in the Hash Table.
	int getNumberOfEntrys();

	// Initialize Hash Table
	void initSymbolTable();

	// De-allocates all memory used for the Hash Table.
	~Symboltable();
};

#endif /* SYMBOLTABLE_H_ */
