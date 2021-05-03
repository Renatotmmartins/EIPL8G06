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

void copyPrefix(char* src, char* dest, int length);

Value separateBySubstr(Value s, Value pat);

Stack split(Stack, int);

Value sort(Value array, Value block);

Stack mergeStacks(Stack l, Stack r, Value block);

Stack mergeSort(Stack st, Value block, int n);

#endif