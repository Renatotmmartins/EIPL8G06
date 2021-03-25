/**
 * @file contém a implementação de uma stack (pilha)
 */

#include <stdlib.h>
#include "stack.h"

struct stack empty() {
	struct stack s;
	s.previous = 0;
	s.value = 0;
	return s;
}

bool isEmpty(struct stack* s) {
	return s->previous == 0;
}

void push(struct stack* s, int value) {
	struct stack* a = malloc(sizeof(struct stack));

	*a = *s;
	s->value = value;
	s->previous = a;
}

int pop(struct stack* s) {
	struct stack* previous = s->previous;
	int top = s->value;

	*s = *previous;
	free(previous);
	return top;
}
