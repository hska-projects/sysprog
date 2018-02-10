/*
 * Rule.cpp
 *
 *  Created on: 02.11.2016
 *      Author: dominik
 */

#include "../includes/Rule.h"

Rule::Rule() {
}

Rule::~Rule() {
}

int Rule::getRuleType(int rule) {
	switch (rule) {
	case 0:
		return PROG;
		break;
	case 1:
		return DECLS;
		break;
	case 2:
		return DECL;
		break;
	case 3:
		return ARRAY;
		break;
	case 4:
		return STATEMENTS;
		break;
	case 5:
		return STATEMENT;
		break;
	case 6:
		return EXP;
		break;
	case 7:
		return EXP2;
		break;
	case 8:
		return INDEX;
		break;
	case 9:
		return OP_EXP;
		break;
	case 10:
		return OP;
		break;
	default:
		return -1;
		break;
	}

}
