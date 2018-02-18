/*
 * Scanner.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#include "../includes/Scanner.h"

#include <cstddef>

using std::cerr;

Scanner::Scanner(Buffer* buffer, Symboltable* stab) {
	// TODO Auto-generated constructor stub
	//Automat* automat = new Automat();
	this->automat = new Automat();
	this->buffer = buffer;
	this->stab = stab;
}

Token* Scanner::nextToken() {

	if (buffer->file_ < 0 ) {
		cerr << "Buffer has no input file.\n";
		return NULL;
	}

	Token* nextToken;

	char state;
	myString mystring;
//new
	while (automat->isFinalState() == 0) {
		if(buffer->wasEndOfFile == 1) {
			//buffer->closeFile(); file is closed in destructor
			return NULL;
		}
		char tempc = buffer->getChar();
		//set variable for next itteration. If Automat does not determine, abort flow at next itteration
		if (tempc == '\0') {
			buffer->wasEndOfFile = true;
		}
		//call automat
		automat->determineState(tempc);
		if (tempc != ' ' && tempc != '\t' && tempc != '\n' && tempc != '\0' && tempc != '\r') {

				myString s(tempc);
				if (automat->isComment) {
					myString temp;
					mystring = temp;
				} else if (automat->wasComment){
					automat->wasComment = false; //letztes zeichen von kommentar nicht hinzufügen
				} else {
						mystring += s;
				}

		} else if (automat->getState() == 'i') {
			myString s(tempc);
			mystring += s;
		}
		//=:= erwartet, nicht erkannt -> erstes Zeichen speichern
		if (automat->isGoBack()) {
			if (mystring.getLen() > 1){
			while (automat->isFinalState() == 0) {
				if (tempc == '\n' || tempc == '\t' || tempc == ' ' || tempc == '\0') {
					buffer->unGetChar();
				}
				myString tmp;
				for (int j = 1; j < mystring.getLen(); j++) {
					buffer->unGetChar();
					tempc = mystring[mystring.getLen() - j + 1];
					automat->goBack(tempc);
				}
				myString tmp2(mystring[1]);
				mystring = tmp2;
				automat->isFinal = true;
				automat->goBackState = false;
			}
			} else {
				automat->isFinal = true;
				automat->goBackState = false;
			}
		}

	}

	state = automat->getState();

	Entry* entry;
	//bei i und n letztes Zeichen löschen
	if (state == 'i') {
		if (automat->determineLetter(mystring[mystring.getLen()]) == 0) {
			myString tmp;
			for (int j = 1; j < mystring.getLen(); j++) {
				myString tmp2(mystring[j]);
				tmp += tmp2;
			}
			mystring = tmp;
			buffer->unGetChar();
		}
		entry = this->stab->insert(mystring.getStr());
		nextToken = new Token(entry->getTT(), buffer->getLine(), buffer->getCollumn(), entry);
	} else if (state == 'n') {
		buffer->unGetChar();
		long long num = 0;
		if (automat->isDigit(mystring[mystring.getLen()]) == 0) { //lösche letztes zeichen, wenn keine zahl
			myString tmp;
			for (int j = 1; j < mystring.getLen(); j++) {
				myString tmp2(mystring[j]);
				tmp += tmp2;
			}
			mystring = tmp;
		}

		for (int j = 1; j <= mystring.getLen(); j++) {
			num = (mystring[j]-'0') + (num * 10);
		}

		entry = new Entry(mystring.getStr(), IntegerToken);
		entry->setValue(num);
		nextToken = new Token(entry->getTT(), buffer->getLine(), buffer->getCollumn(), entry);
	} else if (state == 'c') {
		//do noting
	} else if (state == 's') {
		myString plus("+");
		myString minus("-");
		myString colon(":");
		myString star("*");
		myString lt("<");
		myString gt(">");
		myString eq("=");
		myString ex("!");
		myString a("&&");
		myString sem(";");
		myString par1("(");
		myString par2(")");
		myString bra1("{");
		myString bra2("}");
		myString sqa1("[");
		myString sqa2("]");
		myString sonder1("=:=");
		myString assign(":=");
		if (mystring.compare(plus) == 0) {
			myString s("Plus");
			mystring = s;
			entry = new Entry(mystring.getStr(), OtherToken);
			nextToken = new Token(entry->getTT(), buffer->getLine(), buffer->getCollumn(), entry);
		} else if (mystring.compare(minus) == 0) {
			myString s("Minus");
			mystring = s;
			entry = new Entry(mystring.getStr(), OtherToken);
			nextToken = new Token(entry->getTT(), buffer->getLine(), buffer->getCollumn(), entry);
		} else if (mystring.compare(colon) == 0) {
			myString s("Colon");
			mystring = s;
			entry = new Entry(mystring.getStr(), OtherToken);
			nextToken = new Token(entry->getTT(), buffer->getLine(), buffer->getCollumn(), entry);
		} else if (mystring.compare(star) == 0) {
			myString s("Star");
			mystring = s;
			entry = new Entry(mystring.getStr(), OtherToken);
			nextToken = new Token(entry->getTT(), buffer->getLine(), buffer->getCollumn(), entry);
		} else if (mystring.compare(lt) == 0) {
			myString s("Less than");
			mystring = s;
			entry = new Entry(mystring.getStr(), OtherToken);
			nextToken = new Token(entry->getTT(), buffer->getLine(), buffer->getCollumn(), entry);
		} else if (mystring.compare(gt) == 0) {
			myString s("Greater than");
			mystring = s;
			entry = new Entry(mystring.getStr(), OtherToken);
			nextToken = new Token(entry->getTT(), buffer->getLine(), buffer->getCollumn(), entry);
		} else if (mystring.compare(eq) == 0) {
			myString s("Equals");
			mystring = s;
			entry = new Entry(mystring.getStr(), OtherToken);
			nextToken = new Token(entry->getTT(), buffer->getLine(), buffer->getCollumn(), entry);
		} else if (mystring.compare(ex) == 0) {
			myString s("Exclamation");
			mystring = s;
			entry = new Entry(mystring.getStr(), OtherToken);
			nextToken = new Token(entry->getTT(), buffer->getLine(), buffer->getCollumn(), entry);
		} else if (mystring.compare(a) == 0) {
			myString s("And");
			mystring = s;
			entry = new Entry(mystring.getStr(), OtherToken);
			nextToken = new Token(entry->getTT(), buffer->getLine(), buffer->getCollumn(), entry);
		} else if (mystring.compare(sem) == 0) {
			myString s("Semicolon");
			mystring = s;
			entry = new Entry(mystring.getStr(), OtherToken);
			nextToken = new Token(entry->getTT(), buffer->getLine(), buffer->getCollumn(), entry);
		} else if (mystring.compare(par1) == 0) {
			myString s("Left Paranthesis");
			mystring = s;
			entry = new Entry(mystring.getStr(), OtherToken);
			nextToken = new Token(entry->getTT(), buffer->getLine(), buffer->getCollumn(), entry);
		} else if (mystring.compare(par2) == 0) {
			myString s("Right Paranthesis");
			mystring = s;
			entry = new Entry(mystring.getStr(), OtherToken);
			nextToken = new Token(entry->getTT(), buffer->getLine(), buffer->getCollumn(), entry);
		} else if (mystring.compare(bra1) == 0) {
			myString s("Left Bracket");
			mystring = s;
			entry = new Entry(mystring.getStr(), OtherToken);
			nextToken = new Token(entry->getTT(), buffer->getLine(), buffer->getCollumn(), entry);
		} else if (mystring.compare(bra2) == 0) {
			myString s("Right Bracket");
			mystring = s;
			entry = new Entry(mystring.getStr(), OtherToken);
			nextToken = new Token(entry->getTT(), buffer->getLine(), buffer->getCollumn(), entry);
		} else if (mystring.compare(sqa1) == 0) {
			myString s("Left Square Bracket");
			mystring = s;
			entry = new Entry(mystring.getStr(), OtherToken);
			nextToken = new Token(entry->getTT(), buffer->getLine(), buffer->getCollumn(), entry);
		} else if (mystring.compare(sqa2) == 0) {
			myString s("Right Square Bracket");
			mystring = s;
			entry = new Entry(mystring.getStr(), OtherToken);
			nextToken = new Token(entry->getTT(), buffer->getLine(), buffer->getCollumn(), entry);
		} else if (mystring.compare(sonder1) == 0) {
			entry = new Entry(mystring.getStr(), OtherToken);
			nextToken = new Token(entry->getTT(), buffer->getLine(), buffer->getCollumn(), entry);
		} else if (mystring.compare(assign) == 0) {
			myString s("Assign");
			mystring = s;
			entry = new Entry(mystring.getStr(), OtherToken);
			nextToken = new Token(entry->getTT(), buffer->getLine(), buffer->getCollumn(), entry);
		}

	} else if (state == 'f') {
			entry = new Entry(mystring.getStr(), UnknownToken);
			nextToken = new Token(entry->getTT(), buffer->getLine(), buffer->getCollumn(), entry);
	}
	automat->initAutomat();
	return nextToken;
}

Scanner::~Scanner() {
	// TODO Auto-generated destructor stub
}
