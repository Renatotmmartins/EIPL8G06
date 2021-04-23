#include "logicOperations.h"

/**
 * \brief Avalia o valor lógico do value
 * @param a   o elemento do tipo #Value
 * @return Um inteiro que simboliza o valor lógico (1 caso seja verdadeiro e 0 caso seja falso)
 */

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

/**
 * \brief Executa as operações pedidas
 * @param str A string correspondente aos operadores
 * @param x   o elemento do tipo #Value
 * @param y   o elemento do tipo #Value
 * @return    x ou y, dependendo do resultado da operação que for efetuada
 */

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


/**
 * \brief Muda o valor da variável para ser o x
 * @param var variável dada (letra de A a Z)
 * @param x   o elemento do tipo #Value
 * @return O valor dado (x)
 */
Value setVariable(char* var, Value x)
{
	return x;
}