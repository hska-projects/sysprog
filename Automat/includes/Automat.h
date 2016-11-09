/*
 * Automat.h
 *
 *  Created on: Jul 5, 2012
 *      Author: knad0001
 */

#ifndef Automat_H_
#define Automat_H_

enum type {numbertype, identifiertype, commenttype, signtype};
enum state { number, identifier, comment, sign, fail, start };


class Automat {
public:
	Automat();
	virtual ~Automat();
	
	char sign1[15];
	
	int identifierState;
	int numberState;
	int signState;
	bool wasComment;
	bool isAnd;
	bool goBackState;
	bool isComment;
	bool isIdentifier;
	bool isNumber;
	bool isColon;
	bool isSign;
	bool isEQ;
	bool id;
	bool isFinal;
	bool isStar;
	bool failState;
	
	//*
	bool isFinalState();
	char getState();
	bool isInit();
	bool isSig(char c);
	bool isGoBack();
	void goBack(char c);
	void determineState(char c);
	void initAutomat();
	void initIsComment();
	void determineSign(char c);
	bool isDigit(char c);
	void determineNumber(char c);
	void determineIdentifier(char c);
	bool determineId(char c);
	bool determineLetter(char c);
	//*/
};

#endif /* Automat_H_ */
