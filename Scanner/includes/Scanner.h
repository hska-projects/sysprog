/*
 * Scanner.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#ifndef SCANNER_H_
#define SCANNER_H_

#include "../includes/Token.h"
#include "../../Symboltable/includes/Symboltable.h"
#include "../../Symboltable/includes/Entry.h"
#include "../../Automat/includes/Automat.h"
#include "../../Buffer/includes/Buffer.h"


class Scanner {
public:
	Scanner(Buffer* buffer, Symboltable* stab);
	Token* nextToken();
	Symboltable* stab;
	Buffer* buffer;
	virtual ~Scanner();
private:
	Automat* automat;
};

#endif /* SCANNER_H_ */
