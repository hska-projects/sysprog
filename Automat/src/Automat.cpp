/*
 * Automat.cpp
 *
 */

#include "../includes/Automat.h"

Automat::Automat() {
	//initialisiere Array und Variablen
	sign1[0] = '+';
	sign1[1] = '-';
	sign1[2] = ':';
	sign1[3] = '*';
	sign1[4] = '<';
	sign1[5] = '>';
	sign1[6] = '=';
	sign1[7] = '!';
	sign1[8] = ';';
	sign1[9] = '(';
	sign1[10] = ')';
	sign1[11] = '{';
	sign1[12] = '}';
	sign1[13] = '[';
	sign1[14] = ']';
		
	identifierState = 0;
	numberState = 0;
	signState = 0;
	isAnd = false;
	wasComment = false;
	goBackState = false;;
	isComment = false;
	isIdentifier = false;
	isNumber = false;
	isColon = false;
	isSign = false;
	isEQ = false;
	id = false;
	isFinal = false;
	isStar = false;
	failState = false;
}

Automat::~Automat() {
}

bool Automat::isFinalState() { return isFinal; }

char Automat::getState() {
	if (isNumber) {
		return 'n';
	} else if (isIdentifier) {
		return 'i';
	} else if (isComment) {
		return 'c';
	} else if (isSign) {
		return 's';
	} else if (failState) {
		return 'f';	
	}
	return '0';
}

void Automat::determineState(char c) {

	//überprüfe ob char in Muster passt; erhöhe state-variablen
	determineIdentifier(c);
	determineNumber(c);
	determineSign(c);
	
	//number<->identifier unterscheidung; erstes Zeichen
	//unterscheidung ob zahl oder identifier bsp: 001919AB : 001919 number AB identifier
	 if (identifierState == numberState && signState == 0 && numberState != 0 && isComment == 0){
		isNumber = true;
		isComment = false;
		isIdentifier = false;
		isSign = false;	
	}
	
	//Kommentar; Automat initialisieren, char nicht beachten
	if (isComment) {
		//potentielles Kommentarende
		if (signState == 1 && c == '*') {
			isStar = true;
		} else if (signState == 2 && c == ':' && isStar) {
		// *: Kommentarende erkannt
			isComment = false;
			wasComment = true;
			initAutomat();
		} else {
			initIsComment();
		}
	} else if (signState == 2 && c == '*' && isColon) {
		// :* Kommentar erkannt
		isComment = true;
		initIsComment();
	} else if (isNumber) {
	//Number erkannt
	//aktueller char keine Zahl -> Tokenende
		if(isDigit(c) == 0) {
			isFinal = true;
		}
	} else if (identifierState > numberState && id == 1 && signState == 0) {
	//Identifier erkannt
		isIdentifier = true;
	} else if (identifierState > 0 && id == 0) {
	//identifier Tokenende; char aktuell kein identifier
		isFinal = true;
		isIdentifier = true;
		isNumber = false;
		isComment = false;
		isSign = false;
	} else if (signState == 1 && c == ':') {
	//: erkennung
		isColon = true;
		isSign = true;
		isNumber = false;
		isComment = false;
		isIdentifier = false;
	} else if (signState == 1 && c == '=') {
	//= erkennung
		isEQ = true;
		isSign = true;
		isNumber = false;
		isComment = false;
		isIdentifier = false;
	} else if (signState == 1 && c == '*') {
	//* erkennung
		isStar = true;
		isSign = true;
		isNumber = false;
		isComment = false;
		isIdentifier = false;
	} else if (signState == 2 && c == '=' && isColon && id == 0) {
	// := erkannt; Token Ende
		isFinal = true;
		isSign = true;
		isNumber = false;
		isComment = false;
		isIdentifier = false;
	} else if (signState == 2 && c == ':' && isEQ) {
	//=: erkennung
		isColon = true;
	} else if (signState == 3 && c == '=' && isEQ && isColon && id == 0) {
	// =:= erkannt; Token Ende
		isFinal = true;
		isSign = true;
		isNumber = false;
		isComment = false;
		isIdentifier = false;
	} else if (signState == 1 && c == '&') {
	//& erkennung
		isAnd = true;
		isSign = true;
		isNumber = false;
		isComment = false;
		isIdentifier = false;
	} else if (signState == 2 && c == '&' && isAnd) {
	//&& erkannt; Token Ende
		isFinal = true;
		isSign = false;
		isNumber = false;
		isComment = false;
		isIdentifier = false;
	} else if (signState == 1) {
	//sign erkannt (kein Sonderfall)
		if(numberState > 0 || identifierState > 0 || isSig(c) == 0) {
		//->ungetChar 
			goBackState = true;
		} else {
		//sign erkannt; Token Ende
			isFinal = true;
			isSign = true;
			isNumber = false;
			isComment = false;
			isIdentifier = false;
		}
	} else if (isSig(c) == 0 && isDigit(c) == 0 && determineLetter(c) == 0) {
	//kein bekanntes Zeichen
		if (c != '\n' && c != '\t' && c != '\0' && c !=' ') {
		//fail State -> Unkown Token -> Fehler
			failState = true;
			isFinal = true;
			isSign = false;
			isNumber = false;
			isComment = false;
			isIdentifier = false;
		}
		if (isIdentifier == 1 || isNumber == 1 || isSign == 1) {
		//Token vorher erkannt -> ungetChar -> Ende
			goBackState = true;
		}
	} else if (c == '\0') {
		//dummy end of file
	} else if (c == ' ') {
	//Leerzeichen überspringen
			initAutomat();
  	} else {
	//keine Erkennung, Automat wird zurück gesetzt, Wiederholung
		goBackState = true;
	}
	return;
}

bool Automat::isGoBack() {	return goBackState; 	}

bool Automat::isInit() {
	if (signState == 0 && identifierState == 0 && numberState == 0) {
		return true;
	}
	return false;
}

//Automat einen char zurück gehen lassen
void Automat::goBack(char c){
	if(determineLetter(c) || isDigit(c)){
		identifierState--;
	}
	if(isDigit(c)){
		numberState--;
	}
	if(isSig(c)){
		signState--;
	 if (signState < 2) {
		signState--;
		goBackState = false;
	 }
	}
}

void Automat::initAutomat() {
	identifierState = 0;
	numberState = 0;
	signState = 0;
	goBackState = false;
	isComment = false;
	isIdentifier = false;
	isNumber = false;
	isColon = false;
	isSign = false;
	isEQ = false;
	id = false;
	isFinal = false;
	isStar = false;
	failState = false;
	return;
}

void Automat::initIsComment() {
	identifierState = 0;
	numberState = 0;
	signState = 0;
	isIdentifier = false;
	isNumber = false;
	isColon = false;
	isSign = false;
	isEQ = false;
	id = false;
	isFinal = false;
	isStar = false;
	failState = false;
	return;
}

bool Automat::isSig(char c) {
	for( int i = 0; i < 16; i++) {
		if(c == sign1[i]  && c != '\0') {
			return true;
		}
	}
	return false;
}


void Automat::determineSign(char c) {
	for( int i = 0; i < 16; i++) {
		if(c == sign1[i] && c != '\0') {
			signState += 1;
			return;
		}
	}
	return;	
}

bool Automat::isDigit(char c) {
	if( c <= '9' && c >= '0') {
		return true;
	}
	return false;
}

void Automat::determineNumber(char c) {
	if (isDigit(c)) {
		numberState += 1;
	}
	return;
}
void Automat::determineIdentifier(char c) {
	id = determineId(c);
	if (id) {
		identifierState += 1;
	}
	return;
}

bool Automat::determineId(char c) {	return (determineLetter(c) || isDigit(c));	}

bool Automat::determineLetter(char c) {
	if( (c <= 'Z' && c >= 'A') || (c <= 'z' && c >= 'a')) {
		return true;	
	}
	return false;
}
