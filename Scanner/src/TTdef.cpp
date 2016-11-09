#include "../includes/TTdef.h"

char* TTdef::getTokenType(int val) {
	switch (val) {
	case 0:
		return "IdentifierToken";
	case 1:
		return "IfToken";
	case 2:
		return "WhileToken";
	case 3:
		return "IntegerToken";
	case 4:
		return "UnknownToken";
	case 5:
		return "OtherToken";
	case 6: 
		return "WriteToken";
	case 7: 
		return "ReadToken";
	case 8: 
		return "ElseToken";
	case 9: 
		return "IntToken";
	default:
		return "Error";
	}
}
