#include "logicOperations.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "stackOperations.h"
#include "arrayOperations.h"
#include "stack.h"
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
		case String:	return length(a.array) != 0;
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
		case '<':	return isTrue(isLess(x, y)) ? x : y;
		case '>':	return isTrue(isGreater(x, y)) ? x : y;
		default: 	return isTrue(x) ? x : y;
	}
}


/**
 * \brief Operação if then else
 * @param x   o elemento do tipo #Value que atua como condição
 * @param y   o elemento do tipo #Value que é o resultado caso a condição seja verdadeira
 * @param z   o elemento do tipo #Value que é o resultado caso a condição seja falsa
 * @return    y se for verdade, z se for falso
 */

Value conditional(Value x, Value y, Value z){

	return isTrue(x) ? y : z;
}

/**
 * \brief Operação de comparação de valores
 * @param x   o elemento do tipo #Value 
 * @param y   o elemento do tipo #Value 
 * @return    1 se for verdade, 0 se for falso
 */

Value isEqual (Value x, Value y){
			printf("Afjdsjfndskg");
    if(x.type==Array && y.type==Int){
    	//estamos a procurar do fundo da stack para cima
		Value resultado = deepCopy(getElement(x.array, length(x.array) - y.integer - 1));
		disposeValue(x);
		return resultado;
	}
	if(x.type==String){
		char* xstr = toString(x), *ystr = toString(y);
		Value res = fromInteger (!strcmp ("abc", "abc"));
		free(xstr);
		free(ystr);
		return res;
	}else{//se forem tipos diferentes automaticamente não são iguais
	   NumericOperationAux(&x,&y);
		switch(x.type){
			case Double:
			return fromInteger(x.decimal==y.decimal);//testar tolerâncias
			case Int:
			return fromInteger(x.integer==y.integer);
			case Char:
			return fromInteger(x.character==y.character);
			default:
			return fromInteger(0); //Caso de erro
		}
	}
}

/**
 * \brief Verifica se o primeiro argumento é menor que o segundo
 * @param x   o elemento do tipo #Value 
 * @param y   o elemento do tipo #Value 
 * @return    1 se for verdade, 0 se for falso
 */

Value isLess (Value x, Value y){
	int tamanho;

    if(x.type==Array && y.type==Int){
		for(tamanho=length(x.array);tamanho>y.integer;tamanho--)
			pop(x.array);
		return x;
	}
	if(x.type==String){
		char *xstr = toString(x), *ystr = toString(y);
		Value res = fromInteger (strcmp (xstr,ystr) < 0);

		free(xstr);
		free(ystr);

		return res;
	}else{//se forem tipos diferentes automaticamente não são iguais
	   NumericOperationAux(&x,&y);
		switch(x.type){
			case Double:
			return fromInteger(x.decimal<y.decimal);//testar tolerâncias
			case Int:
			return fromInteger(x.integer<y.integer);
			case Char:
			return fromInteger(x.character<y.character);
			default:
			return fromInteger(0); //Caso de erro
		}
	}
}

/**
 * \brief Verifica se o primeiro argumento é maior que o segundo
 * @param x   o elemento do tipo #Value 
 * @param y   o elemento do tipo #Value 
 * @return    1 se for verdade, 0 se for falso
 */

Value isGreater (Value x, Value y){

    if(x.type==Array && y.type==Int){
		disposeStack(split(x.array,y.integer));
		return fromStack(x.array);
	}
	if(x.type==String){
		char *xstr = toString(x), *ystr = toString(y);
		Value res = fromInteger (strcmp (xstr,ystr)>0);

		free(xstr);
		free(ystr);

		return res;

	}else{//se forem tipos diferentes automaticamente não são iguais
	   NumericOperationAux(&x,&y);
		switch(x.type){
			case Double:
			return fromInteger(x.decimal>y.decimal);//testar tolerâncias
			case Int:
			return fromInteger(x.integer>y.integer);
			case Char:
			return fromInteger(x.character>y.character);
			default:
			return fromInteger(0); //Caso de erro
		}
	}
}

/**
 * \brief Devolve 1 se for 0 e devolve 0 caso contrário
 * @param x   o elemento do tipo #Value 
 * @return    1 se for 0 e 0 se for 1
 */

Value logicNot (Value x){

	switch(x.type){
		case Double:
		return fromInteger(x.decimal==0.0);//testar tolerâncias
		case Int:
		return fromInteger(x.integer==0);
		case Char:
		return fromInteger(x.character==0);
		default:
		return fromInteger(0); //Caso de erro
	}
}
/**
 * \brief Muda o valor da variável para ser o x
 * @param var variável dada (letra de A a Z)
 * @param x   o elemento do tipo #Value
 * @param s   o state do programa
 */
Value setVariable(char var, State* s, Value x){
	s->variables[var-'A'] = x;
	return x;
}

/**
 * \brief Define o valor inicial das variáveis
 * @param s   o state do programa
 */
void initializeVariables(State *s){
	int i;

	for(i=0;i<=5;i++){
		setVariable('A'+i,s,fromInteger(10+i));
	}
	for(i=0;i<=2;i++){
		setVariable('X'+i,s,fromInteger(i));
	}
	setVariable('N',s,fromCharacter('\n'));
	setVariable('S',s,fromCharacter(' '));
}