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

/**
 * \brief Macro que captura o padrão de computação para a conversão de tipos
 * @param toType Tipo para o qual será convertido
 * @param unionArg Nome da variável armazenada na Union
 * @param fromDouble Como converter para double
 * @param fromInt Como converter para inteiro
 * @param fromChar Como converter para character
 * @param fromString Como converter para string
 * @return retorna o valor convertido
 */
#define Convert(toType, unionArg, fromDouble, fromInt, fromChar, fromString) \
    Value result;\
    result.type = toType;\
    switch(a.type) {\
        case Double:    result.unionArg = fromDouble;   break;\
        case Int:       result.unionArg = fromInt;      break;\
        case Char:      result.unionArg = fromChar;     break;\
        case String:    fromString   break;\
        default:                                        break;\
    }\
    return result;

/**
 * \brief Converte e desaloca o elemento para o tipo dado
 * @param type Tipo para o qual se pretende converter
 * @return Valor convertido
 */
#define convertAndDisposeTo(type)  \
    Value ans = convertTo##type(a); \
    disposeValue(a); \
    return ans; 

Value convertToInt(Value v);
Value convertToDouble(Value v);
Value convertToChar(Value v);
Value convertToString(Value v);

char* convertFloatToString(double v);
char* convertIntToString(long long v);
char* convertCharToString(char v);

Value convertToType(DataType, Value);

Value convertAndDisposeToDouble(Value);
Value convertAndDisposeToInt(Value);
Value convertAndDisposeToChar(Value);
Value convertAndDisposeToString(Value);

#endif
