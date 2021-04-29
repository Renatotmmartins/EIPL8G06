/**
 * @file contém a declaração das funções correspondentes às operações
 * sobre a stack
 */

//! Include guard
#ifndef OPERATIONS_H
//! Include guard
#define OPERATIONS_H

#define UNDEFINED 13


#include "stack.h"


char* getInput ();

//! Usada para simplificar as funções só com um argumento.
#define UNARYOPERATION(caseDouble, caseInt, caseChar, caseArray)\
    switch (a.type) {\
        case Double:    a.decimal = caseDouble; break;\
        case Int: a.integer = caseInt;          break;\
        case Char: a.character = caseChar;      break;\
        case Array: a.array = caseArray;        break;\
        default:                                break;\
    }\
    return a\


Value decrement(State* s, Value a);
Value increment(State* s, Value a);
Value negate(State* s, Value a);

void NumericOperationAux(Value *a, Value *b);

//! Usada para simplficar as funções com dois argumentos.
#define NUMERICOPERATION(caseDouble, caseInt, caseChar) \
    NumericOperationAux(&a, &b);\
    Value result;\
    result.type = a.type;\
    switch (a.type) {\
        case Double:    result.decimal = caseDouble;    break;\
        case Int:       result.integer = caseInt;       break;\
        case Char:      result.character = caseChar;    break;\
        default:                                        break;\
    }\
    return result\



Value sum(Value a, Value b);
Value subtract(Value a, Value b);
Value divide(Value a, Value b);
Value multiply(Value a, Value b);
Value and(Value a, Value b);
Value or(Value a, Value b);
Value xor(Value a, Value b);
Value module(Value a, Value b);
Value exponentiate(Value a, Value b);

void readAllLines(Stack st);

#endif