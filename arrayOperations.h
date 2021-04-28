/**
 * @file contém a declaração das funções correspondentes às operações
 * sobre arrays
 */

//! Include guard
#ifndef ARRAYOPERATIONS_H
//! Include guard
#define ARRAYOPERATIONS_H

#include "stack.h"


Value substr(Value st, Value pat);

void copyPrefix(char* src, char* dest, int length);

Value separateBySubstr(Value s, Value pat);

Stack split(Stack , int );

#endif