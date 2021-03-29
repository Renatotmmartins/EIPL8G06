/**
 * @file contém a implementação de uma stack (pilha)
 */

#include <stdlib.h>
#include "stack.h"

/**
 * \brief A stack vazia.
 
 * @return   Um objeto do tipo Stack sem nenhum elemento
 */
Stack empty() {
	Stack s;
	s.previous = 0;
	s.value = 0;
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
void push(Stack* s, int value) {
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
int pop(Stack* s) {
	Stack* previous = s->previous;
	int top = s->value;

	*s = *previous;
	free(previous);
	return top;
}
