/**
 * @file contém a declaração das funções correspondentes
 * às operações de manipulação da stack
 */

//! Include guard
#ifndef STACK_OPERATIONS_H
//! Include guard
#define STACK_OPERATIONS_H

#include "stack.h"


#define swap(st) rotateTop(st, 2)

#define rotate(st) rotateTop(st, 3)

void rotateTop(Stack, int);

Value getElement(Stack, Value);

void readLine(Stack);

void duplicate(Stack);


#endif