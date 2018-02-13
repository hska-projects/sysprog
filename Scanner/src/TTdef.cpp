#include "../includes/TTdef.h"

char* TTdef::getTokenType(int val) {
	switch (val) {
	case 0:
		return (char*)"IdentifierToken";
	case 1:
		return (char*)"IfToken";
	case 2:
		return (char*)"WhileToken";
	case 3:
		return (char*)"IntegerToken";
	case 4:
		return (char*)"UnknownToken";
	case 5:
		return (char*)"OtherToken";
	case 6: 
		return (char*)"WriteToken";
	case 7: 
		return (char*)"ReadToken";
	case 8: 
		return (char*)"ElseToken";
	case 9: 
		return (char*)"IntToken";
	default:
		return (char*)"Error";
	}
}
