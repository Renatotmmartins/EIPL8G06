/**
 * @file contém a declaração das funções correspondentes às operações
 * sobre arrays
 */

//! Include guard
#ifndef ARRAYOPERATIONS_H
//! Include guard
#define ARRAYOPERATIONS_H

#include "stack.h"


Value substrAndDispose(Value st, Value pat);

Value substr(Value st, Value pat);

Value separateBySubstr(Value s, Value pat);

Stack split(Stack st, long long n);

Value sort(State* s, Value array, Value block);

void reverseStack(Stack s);

Stack mergeStacks(State* s, Stack l, Stack r, Value block);

Stack mergeSort(State* s, Stack st, Value block, long long n);

#endif