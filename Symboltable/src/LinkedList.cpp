/*
 * LinkedList.cpp
 *
 *  Created on: Oct 18, 2015
 *      Author: haitham
 *
 *  This header file contains the Linked List class declaration.
 *  Hash Table array elements consist of Linked List objects.
 */

#include "../includes/LinkedList.h"
#include "../includes/myString.h"

// Constructs the empty linked list object.
// Creates the head node and sets length to zero.
LinkedList::LinkedList() {
	head = NULL;
	//head -> next = NULL;
	length = 0;
}

// Inserts an Entry at the end of the list.
void LinkedList::insertEntry(Entry* newEntry) {
	if (head == NULL) {
		head = newEntry;
		length++;
		return;
	}

	if (!head->getNext()) {
		head->setNext(newEntry);
		length++;
		return;
	}

	Entry* p = head;
	Entry* q = head;
	while (q) {
		p = q;
		q = p->getNext();
	}
	p->setNext(newEntry);
	newEntry->setNext(NULL);
	length++;
}

// Removes an Entry from the list by Entry key.
// Returns true if the operation is successful.
bool LinkedList::removeEntry(myString& EntryKey) {
	if (!head->getNext())
		return false;
	Entry* p = head;
	Entry* q = head;
	while (q) {
		if ((q->getString())->compare(EntryKey) == 0) {
			p->setNext(q->getNext());
			delete q;
			length--;
			return true;
		}
		p = q;
		q = p->getNext();
	}
	return false;
}

// Searches for an Entry by its key.
// Returns a reference to first match.
// Returns a NULL pointer if no match is found.
Entry* LinkedList::getEntry(myString& EntryKey) {
	Entry* p = head;
	Entry* q = head;
	while (q) {
		p = q;
		if (p->getString()->compare(EntryKey) == 0)
			return p;
		q = p->getNext();
	}
	return NULL;
}

// Displays list contents to the console window.
void LinkedList::printList() {
	if (length == 0) {
		printf("\n{ }\n");
		return;
	}
	Entry* p = head;
	Entry* q = head;
	printf("\n{ ");
	while (q) {
		p = q;
		if (p != NULL) {
			printf("%s, %s", (p->getString())->getStr(), p->getTokenType());
			if (p->getNext())
				printf(", ");
			else
				printf(" ");
		}
		q = p->getNext();
	}
	printf("}\n");
}

// Returns the length of the list.
int LinkedList::getLength() {
	return length;
}

// De-allocates list memory when the program terminates.
LinkedList::~LinkedList() {
	Entry* p = head;
	Entry* q = head;
	while (q) {
		p = q;
		q = p->getNext();
		if (q)
			delete p;
	}
}
