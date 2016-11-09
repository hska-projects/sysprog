/*
 * LinkedList.h
 *
 *  Created on: Oct 18, 2015
 *      Author: haitham
 *
 *  This header file contains the Linked List class declaration.
 *  Hash Table array elements consist of Linked List objects.
 */

#ifndef SYMBOLTABLE_SRC_LINKEDLIST_H_
#define SYMBOLTABLE_SRC_LINKEDLIST_H_

#include "myString.h"
#include "Entry.h"

#include <stdio.h>
#include <cstddef>

class LinkedList {

private:
	// Head is a reference to a list of data nodes.
	Entry* head;

	// Length is the number of data nodes.
	int length;

public:
	// Constructs the empty linked list object.
	// Creates the head node and sets length to zero.
	LinkedList();

	// Inserts an Entry at the end of the list.
	void insertEntry(Entry* newEntry);

	// Removes an Entry from the list by Entry key.
	// Returns true if the operation is successful.
	bool removeEntry(myString& EntryKey);

	// Searches for an Entry by its key.
	// Returns a reference to first match.
	// Returns a NULL pointer if no match is found.
	Entry * getEntry(myString& EntryKey);

	// Displays list contents to the console window.
	void printList();

	// Returns the length of the list.
	int getLength();

	// De-allocates list memory when the program terminates.
	~LinkedList();
};

#endif /* SYMBOLTABLE_SRC_LINKEDLIST_H_ */
