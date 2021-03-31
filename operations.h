/**
 * @file contém a declaração das funções correspondentes às operações
 * sobre a stack
 */

//! Include guard
#ifndef OPERATIONS_H
//! Include guard
#define OPERATIONS_H

#include "stack.h"

Value decrement(Value v);
Value increment(Value v);
Value negate(Value v);
Value convertToInt(Value v);
Value convertToDouble(Value v);
Value convertToChar(Value v);
Value convertToString(Value v);


void NumericOperationAux(Value *a, Value *b);

Value sum(Value a, Value b);
Value subtract(Value a, Value b);
Value divide(Value a, Value b);
Value multiply(Value a, Value b);
Value AND(Value a, Value b);
Value OR(Value a, Value b);
Value XOR(Value a, Value b);
Value module(Value a, Value b);
Value exponentiate(Value a, Value b);


#endif