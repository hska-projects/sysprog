/*
 * Rule.h
 *
 *  Created on: 02.11.2016
 *      Author: dominik
 */

#ifndef PARSER_INCLUDES_RULE_H_
#define PARSER_INCLUDES_RULE_H_

enum RuleType {
	PROG, DECLS, DECL, ARRAY, STATEMENTS, STATEMENT, EXP, EXP2, INDEX, OP_EXP, OP,
	//Leafs
	INT, ID, EPSYLON, WRITE, READ, IF, ELSE, WHILE, SIGN, INTEGER,
	SQUAREOPEN, SQUARECLOSE, ASSIGN, OPEN, CLOSE, POPEN, PCLOSE,
	MINUS, EMARK, PLUS, STAR, COLON, LT, GT, EQUALS, SONDER, AND
};

class Rule{
public:
	Rule();
	~Rule();
	char* getRuleType(int rule);
	char* getClosingType(int closing);

};



#endif /* PARSER_INCLUDES_RULE_H_ */
