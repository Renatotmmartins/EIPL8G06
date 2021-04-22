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


#define UNARYOPERATION(caseDouble, caseInt, caseChar)\
    switch (a.type) {\
        case Double:    a.decimal = caseDouble; break;\
        case Int: a.integer = caseInt;          break;\
        case Char: a.character = caseChar;      break;\
        default:                                break;\
    }\
    return a\


Value decrement(Value v);
Value increment(Value v);
Value negate(Value v);

void NumericOperationAux(Value *a, Value *b);


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


#endif