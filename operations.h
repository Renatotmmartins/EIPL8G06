/**
 * @file
 * @brief contém a declaração das funções correspondentes às operações
 * sobre a stack
 */

//! Include guard
#ifndef OPERATIONS_H
//! Include guard
#define OPERATIONS_H


#include "stack.h"


char* getInput ();

Value decrement(State* s, Value a);
Value increment(State* s, Value a);
void negate(State* s, Value a);

void NumericOperationAux(Value *a, Value *b);


Value sum(Value a, Value b);
Value subtract(Value a, Value b);
Value divide(Value a, Value b);
Value multiply(State* s, Value a, Value b);
Value and(Value a, Value b);
Value or(Value a, Value b);
Value xor(Value a, Value b);
Value module(State* s, Value a, Value b);
Value exponentiate(Value a, Value b);

void readAllLines(Stack st);
Value splitByWhitespace(Value v);
Value splitByLinebreak(Value v);
#endif