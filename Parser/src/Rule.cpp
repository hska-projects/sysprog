/*
 * Rule.cpp
 *
 *  Created on: 02.11.2016
 *      Author: dominik
 */


Rule::Rule() {}

Rule::~Rule() {}

char* Rule::getRuleType(int rule) {
	switch (rule) {
		case 0:
			return RuleType::PROG;
			break;
		case 1:
			return RuleType::DECLS;
			break;
		case 2:
			return RuleType::DECL;
			break;
		case 3:
			return RuleType::ARRAY;
			break;
		case 4:
			return RuleType::STATEMENTS;
			break;
		case 5:
			return RuleType::STATEMENT;
			break;
		case 6:
			return RuleType::EXP;
			break;
		case 7:
			return RuleType::EXP2;
			break;
		case 8:
			return RuleType::INDEX;
			break;
		case 9:
			return RuleType::OP_EXP;
			break;
		case 10:
			return RuleType::OP;
			break;
		default:
			break;
	}
}

char* Rule::getClosingType(int closing) {
	switch (closing) {
		case 0:
				return ClosingType::INT;
			break;
		case 1:
				return ClosingType::ID;
			break;
		case 2:
				return ClosingType::EPSYLON;
			break;
		case 3:
				return ClosingType::WRITE;
			break;
		case 4:
				return ClosingType::READ;
			break;
		case 5:
				return ClosingType::IF;
			break;
		case 6:
				return ClosingType::ELSE;
			break;
		case 7:
				return ClosingType::WHILE;
			break;
		case 8:
				return ClosingType::SIGN;
			break;
		case 9:
				return ClosingType::INTEGER;
			break;
		default:
			break;
	}
}

