#include "logicOperations.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "stackOperations.h"
#include "arrayOperations.h"
#include "blockOperations.h"
#include "stack.h"

/**
 * \brief Avalia o valor lógico do value
 * @param a   o elemento do tipo #Value
 * @return Um inteiro que simboliza o valor lógico (1 caso seja verdadeiro e 0 caso seja falso)
 */
bool isTrue(Value a) {
	switch (a.type) {
		case Double:	return a.decimal != 0;
		case Int: 		return a.integer != 0;
		case Char: 		return a.character != '\0';
		case String:	
		case Array:		return !isEmpty(a.array);
		case Block: 	return !isEmptyBlock(a.block);
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

Value shortcutSelect(char* str, Value x, Value y) {
	Value* r;

	switch (*str) {
		case '&':	r = isTrue(x) ? &y : &x;									break;
		case '|':	r = isTrue(x) ? &x : &y;									break;
		case '<':	r = isTrue(isLess(deepCopy(x), deepCopy(y))) ? &x : &y;		break;
		case '>':	r = isTrue(isGreater(deepCopy(x), deepCopy(y))) ? &x : &y;	break;
		default: 	r = isTrue(x) ? &x : &y;									break;
	}

	if (r == &x)
		disposeValue(y);
	else
		disposeValue(x);

	return *r;
}


/**
 * \brief Operação if then else
 * @param x   o elemento do tipo #Value que atua como condição
 * @param y   o elemento do tipo #Value que é o resultado caso a condição seja verdadeira
 * @param z   o elemento do tipo #Value que é o resultado caso a condição seja falsa
 * @return    y se for verdade, z se for falso
 */

Value conditional(Value x, Value y, Value z){
	if (isTrue(x)) {
		disposeValue(x);
		disposeValue(z);
		return y;
	} else {
		disposeValue(x);
		disposeValue(y);
		return z;
	}
}

/**
 * \brief Compara duas arrays. Destrói-as no final.
 * @param a   a primeira array
 * @param b   a segunda array
 * @return    1 se forem iguais, 0 se não
 */
bool compareArrays(Stack a, Stack b) {
	while (!isEmpty(a) && !isEmpty(b)) {
		if (!isTrue(isEqual(pop(a), pop(b)))) {
			disposeStack(a);
			disposeStack(b);
			return false;
		}
	}

	bool r = isEmpty(a) && isEmpty(b);
	disposeStack(a);
	disposeStack(b);
	return r;
}

/**
 * \brief Compara duas strings (sob a forma de valores) usando strcmp. Destrói-as no final.
 * @param a   a primeira string
 * @param b   a segunda string
 * @return    o resultado de strcmp: 0 se as strings forem iguais, negativo se
 * 			  a é inferior a b, positivo se b é inferior a a
 */
int compareStrings(Value x, Value y) {
	char *xstr = toString(x), *ystr = toString(y);
	int res = strcmp (xstr,ystr);
	//libertar variáveis
	free(xstr); 		free(ystr);
	disposeValue(x);	disposeValue(y);
	return res;
}

/**
 * \brief Operação de comparação de valores. Se o tipo do #Value de x for uma string ou array e do #Value y for um inteiro devolve o #Value que está nesse índice.
 * @param x   o elemento do tipo #Value 
 * @param y   o elemento do tipo #Value 
 * @return    1 se for verdade, 0 se for falso
 */
Value isEqual (Value x, Value y){
    if (x.type >= String && y.type == Int){
		Value resultado = x.array->values[y.integer];
		//para evitar usar deepCopy (pode ser dispendioso), tiramos o Value da array
		//diretamente e depois substituímo-lo por UNDEFINED para nao o apagar no dispose da array
		x.array->values[y.integer] = fromInteger(UNDEFINED);
		disposeValue(x);
		return resultado;
	}
	if(x.type >= String && y.type >= String)
		return fromInteger(compareArrays(x.array, y.array));

	//convertemos para o mesmo tipo antes de comparar
	NumericOperationAux(&x,&y);
	switch(x.type){
		case Double: 	return fromInteger(x.decimal==y.decimal);//testar tolerâncias
		case Int:		return fromInteger(x.integer==y.integer);
		case Char:		return fromInteger(x.character==y.character);
		default:		return fromInteger(UNDEFINED); //Caso de erro
	}
}

/**
 * \brief Verifica se o primeiro argumento é menor que o segundo. Se o tipo do #Value x for array ou string e do #Value y for um inteiro fica com os primeiros y elementos.
 * @param x   o elemento do tipo #Value 
 * @param y   o elemento do tipo #Value 
 * @return    1 se for verdade, 0 se for falso
 */

Value isLess (Value x, Value y){
    if(x.type >= String && y.type==Int){ //manter os primeiros y elementos
		disposeStack(split(x.array, length(x.array) - y.integer));
		return x;
	}
	if(x.type == String)
		return fromInteger(compareStrings(x, y) < 0);
	if (x.type == Array)
		return fromInteger(0);

	//convertemos para o mesmo tipo antes de comparar
    NumericOperationAux(&x,&y);
	switch(x.type){
		case Double:	return fromInteger(x.decimal < y.decimal);//testar tolerâncias
		case Int:		return fromInteger(x.integer < y.integer);
		case Char:		return fromInteger(x.character < y.character);
		default:		return fromInteger(UNDEFINED); //Caso de erro
	}
}

/**
 * \brief Verifica se o primeiro argumento é maior que o segundo. Se o tipo do #Value x for uma string ou array do #Value y for um inteiro fica com os y últimos elementos.
 * @param x   o elemento do tipo #Value 
 * @param y   o elemento do tipo #Value 
 * @return    1 se for verdade, 0 se for falso
 */

Value isGreater (Value x, Value y){

    if(x.type >= String && y.type==Int){ //manter os últimos y elementos da array
		Stack ans = split(x.array,y.integer);
		disposeValue(x);
		return fromStack(ans);
	}
	if(x.type==String)
		return fromInteger(compareStrings(x, y) > 0);
	if (x.type == Array)
		return fromInteger(0);

	//convertemos para o mesmo tipo antes de comparar
    NumericOperationAux(&x,&y);
	switch(x.type){
		case Double:	return fromInteger(x.decimal>y.decimal);//testar tolerâncias
		case Int:		return fromInteger(x.integer>y.integer);
		case Char:		return fromInteger(x.character>y.character);
		default:		return fromInteger(UNDEFINED); //Caso de erro
	}
}

/**
 * \brief Devolve 1 se for 0 e devolve 0 caso contrário
 * @param x   o elemento do tipo #Value 
 * @return    1 se for 0 e 0 se for 1
 */

Value logicNot (Value x){
	Value r = fromInteger(!isTrue(x));
	disposeValue(x);
	return r;
}

/**
 * \brief Muda o valor da variável para ser o x
 * @param var variável dada (letra de A a Z)
 * @param x   o elemento do tipo #Value
 * @param s   o state do programa
 */
void setVariable(char var, State* s){
	disposeValue(s->variables[var - 'A']);
	s->variables[var-'A'] = deepCopy(top(s->stack));
}

/**
 * \brief Define o valor inicial das variáveis
 * @param s   o state do programa
 */
void initializeVariables(State *s){
	for(int i = 0; i < 26; i++)
		s->variables[i] = fromInteger(UNDEFINED);

	for(int i=0;i<=5;i++)
		s->variables[i] = fromInteger(10+i);

	for(int i=0;i<=2;i++)
		s->variables[i + 'X' - 'A'] = fromInteger(i);

	s->variables['N' - 'A'] = fromCharacter('\n');
	s->variables['S' - 'A'] = fromCharacter(' ');
}

/**
 * \brief Liberta o espaço alocado para as variáveis
 * @param s   o state do programa
 */
void disposeVariables(State *s) {
	for(int i = 0; i < 26; i++)
		disposeValue(s->variables[i]);
}