/**
 * @file contém a declaração das funções correspondentes às operações de conversão de tipo
 * sobre a stack
 */

//! Include guard
#ifndef TYPE_OPERATIONS_H
//! Include guard
#define TYPE_OPERATIONS_H

#define UNDEFINED 13

#include "stack.h"


#define Convert(toType, unionArg, fromDouble, fromInt, fromChar, fromString) Value convertTo##toType(Value a) {\
    Value result;\
    result.type = toType;\
    switch(a.type) {\
        case Double:    result.unionArg = fromDouble;   break;\
        case Int:       result.unionArg = fromInt;      break;\
        case Char:      result.unionArg = fromChar;     break;\
        case String:    result.unionArg = fromString;   break;\
        default:                                        break;\
    }\
    return result;\
}

#define convertAndDisposeTo(type)  \
    Value ans = convertTo##type(a); \
    disposeValue(a); \
    return ans; 

Value convertToInt(Value v);
Value convertToDouble(Value v);
Value convertToChar(Value v);
Value convertToString(Value v);

char* convertFloatToString(Value v);
char* convertIntToString(Value v);
char* convertCharToString(Value v);
char* copyString(Value v);

Value convertToType(DataType, Value);

Value convertAndDisposeToDouble(Value);
Value convertAndDisposeToInt(Value);
Value convertAndDisposeToChar(Value);
Value convertAndDisposeToString(Value);

#endif
