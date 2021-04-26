/**
 * @file contém a implementação de uma stack (pilha)
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stack.h"

/**
 * \brief A stack vazia.
 
 * @return   Um objeto do tipo Stack sem nenhum elemento
 */
Stack empty() {
	Stack st = malloc(sizeof(struct stack));
	st->previous = NULL;
	return st;
}

/**
 * \brief Verifica se o pointer aponta para uma stack vazia.
 * 
 * @param s  O pointer para o qual se quer averiguar se a stack é vazia
 * @return   1 (true) se a stack for vazia, 0 (false) se for
 */
bool isEmpty(Stack s) {
	return s->previous == NULL;
}

/**
 * \brief Insere o valor especificado na stack fornecida.
 * 
 *  @param s     O pointer para a stack
 *  @param value O valor a inserir na stack
 */
void push(Stack s, Value value) {
	Stack a = malloc(sizeof(struct stack));

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
Value pop(Stack s) {
	Stack previous = s->previous;
	Value top = s->value;
	*s = *previous;

    if(previous != NULL)
	    free(previous);

	return top;
}

/**
 * \brief Retorna o valor que está no fundo da stack
 * @param st A stack dada
 * @return Valor no fundo da stack
 */
Value popBottom(Stack st) {
    while (!isEmpty(st->previous))
        st = st->previous;

    st->previous = NULL;
    return st->value;
}
/**
 * \brief Apaga o valor que está no topo da stack
 * @param st A stack dada
 */
void eraseTop(Stack st) {
    disposeValue(pop(st));
}

/**
 * \brief Faz uma cópia da stack dada
 * @param st A stack dada
 * @return Uma stack igual à stack original
 */
Stack clone(Stack st)
{
    Stack ans = malloc(sizeof(struct stack));

    while (ans->previous != NULL) {
        ans->value = deepCopy(st->value);
        Stack previous = malloc(sizeof(struct stack));
        *previous = *st->previous;
        ans->previous = previous;
        ans = ans->previous;
    }

    return ans;
}

/**
 * \brief "Junta" duas stacks
 * @param a Primeira stack dada
 * @param b Segunda stack dada
 * @return Stack que resulta da junção das duas stacks dadas inicialmente
 */
Stack merge(Stack a, Stack b) {
    //Se uma stack for representada Tail---Head:
//{ 1, 2, 3 } + {4, 5, 6} = { 1, 2, 3, 4, 5, 6 }
//Ou seja, a cabeça do resultado é a cabeça da segunda stack passada
    Stack last = b;

    while (!isEmpty(last))
        last = last->previous;

    *last = *a;
    free(a);
    return b;
}

/**
 * \brief Enquanto o topo da stack for vazio, elimina as células vazias
 * @param st Stack dada
 */

void disposeStack(Stack st) {
    while (!isEmpty(st))
        eraseTop(st);

    free(st);
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

/**
 * \brief Copia valor que esteja inicialmente na stack
 * @param v Valor inicialmente dado
 * @return Valor copiado na sua nova localização.
 */
Value deepCopy(Value v) {
    Value copy = v;

    if (v.type == String) {
        copy.string = malloc((strlen(v.string) + 1) * sizeof(char));
        strcpy(copy.string, v.string);
    }

    return copy;
}

/**
 * \brief Desaloca valor que esteja presente na memória
 * @param v
 */
void disposeValue(Value v) {
    switch (v.type) {
        case String:    free(v.string);     break;
        default:                            break;
    }
}