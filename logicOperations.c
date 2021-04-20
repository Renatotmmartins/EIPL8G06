#include "logicOperations.h"

bool isTrue(Value a)
{
	switch (a.type) {
		case Double:	return a.decimal != 0;
		case Int: 		return a.integer != 0;
		case Char: 		return a.character != '\0';
		case String:	return *a.string != '\0';
		default:		return false;
	}
}


Value shortcutSelect(char* str, Value x, Value y)
{
	switch (*str)
	{
		case '&':	return isTrue(x) ? y : x;
		case '|':	return isTrue(x) ? x : y;
		//case '<':	return isTrue(menor(x, y)) ? x : y;
		//case '>':	return isTrue(maior(x, y)) ? x : y;
		default: 	return isTrue(x) ? x : y;
	}
}

Value setVariable(char* var, Value x)
{
	return x;
}