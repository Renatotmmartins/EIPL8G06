/**
 * @file contém a implementação de uma stack (pilha)
 */

#include <stdlib.h>
#include "stack.h"

/**
 * \brief A stack vazia.
 
 * @return   Um objeto do tipo struct stack sem nenhum elemento
 */
struct stack empty() {
	struct stack s;
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
bool isEmpty(struct stack* s) {
	return s->previous == 0;
}

/**
 * \brief Insere o valor especificado na stack fornecida.
 * 
 *  @param s     O pointer para a stack
 *  @param value O valor a inserir na stack
 */
void push(struct stack* s, int value) {
	struct stack* a = malloc(sizeof(struct stack));

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
int pop(struct stack* s) {
	struct stack* previous = s->previous;
	int top = s->value;

	*s = *previous;
	free(previous);
	return top;
}
