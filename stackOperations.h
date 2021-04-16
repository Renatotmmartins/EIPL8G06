/**
 * @file contém a declaração das funções correspondentes
 * às operações de manipulação da stack
 */

//! Include guard
#ifndef STACK_OPERATIONS_H
//! Include guard
#define STACK_OPERATIONS_H

#include "stack.h"


Value getElement(Stack* st, int n);

void rotateTop(Stack* st, int n);

void readLine(Stack* st);

void duplicate(Stack* st);


#endif