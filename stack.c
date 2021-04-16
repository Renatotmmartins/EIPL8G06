/**
 * @file contém a implementação de uma stack (pilha)
 */

#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

/**
 * \brief A stack vazia.
 
 * @return   Um objeto do tipo Stack sem nenhum elemento
 */
Stack empty() {
    Value v;
    v.type = Int;
    v.integer = 0;
	Stack s;
	s.previous = 0;
	s.value = v;
	return s;
}

/**
 * \brief Verifica se o pointer aponta para uma stack vazia.
 * 
 * @param s  O pointer para o qual se quer averiguar se a stack é vazia
 * @return   1 (true) se a stack for vazia, 0 (false) se for
 */
bool isEmpty(Stack* s) {
	return s->previous == 0;
}

/**
 * \brief Insere o valor especificado na stack fornecida.
 * 
 *  @param s     O pointer para a stack
 *  @param value O valor a inserir na stack
 */
void push(Stack* s, Value value) {
	Stack* a = malloc(sizeof(Stack));

    *a = *s;
    s->value = value;
    s->previous = a;
}

/**
 * \brief Remove o elemento do topo da stack, retornando o valor 
 * desse mesmo elemento.
 * 
 * @param s     O pointer para a stack
 * @return 	O elemento removido do topo da stack
 */
Value pop(Stack* s) {
	Stack* previous = s->previous;
	Value top = s->value;
	*s = *previous;

    if(previous != NULL)
	    free(previous);

    previous = NULL;

	return top;
}

/**
 * \brief Converte um inteiro para tipo #Value.
 *
 * @param i  o inteiro
 * @return   o inteiro convertido para #Value.
 */
Value fromInteger(int i){
    Value val;

    val.type=Int;
    val.integer=i;

    return val;
}


/**
 * \brief Converte um double para tipo #Value.
 *
 * @param d  o double
 * @return   o double convertido para #Value.
 */
Value fromDecimal(double d){
    Value val;

    val.type=Double;
    val.decimal=d;

    return val;
}

/**
 * \brief Converte um caracter para tipo #Value.
 *
 * @param ch  o caracter
 * @return    o caracter convertido para #Value.
 */
Value fromCharacter(char ch){
    Value val;

    val.type=Char;
    val.character=ch;

    return val;
}

/**
 * \brief Converte uma string para tipo #Value.
 *
 * @param str  a string
 * @return     a string convertida para #Value.
 */
Value fromString(char* str){
    Value val;

    val.type=String;
    val.string=str;

    return val;
}
