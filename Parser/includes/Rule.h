/*
 * Rule.h
 *
 *  Created on: 02.11.2016
 *      Author: dominik
 */

#ifndef PARSER_INCLUDES_RULE_H_
#define PARSER_INCLUDES_RULE_H_

enum RuleType {
		PROG, DECLS, DECL, ARRAY, STATEMENTS, STATEMENT, EXP, EXP2, INDEX, OP_EXP, OP
	};

class Rule{
public:
	Rule();
	~Rule();
	char* getRuleType(int rule);

};



#endif /* PARSER_INCLUDES_RULE_H_ */
