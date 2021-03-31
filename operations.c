/**
 * @file contém a implementação das funções correspondentes às operações
 * sobre a stack
 */

#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "operations.h"

Value decrement(Value v)
{
    switch (v.type)
    {
        case Char:
        v.character--;
        break;

        case Int:
        v.integer--;
        break;

        case Double:
        v.decimal--;
        break;

        default:
        break;
        //case String:
    }

    return v;
}

Value increment(Value v)
{
    switch (v.type)
    {
        case Char:
        v.character++;
        break;

        case Int:
        v.integer++;
        break;

        case Double:
        v.decimal++;
        break;

        default:
        break;

        //case String:
    }

    return v;
}

Value negate(Value v)
{
    switch (v.type)
    {
        case Char:
        v.character = ~v.character;
        break;

        case Int:
        v.integer = ~v.integer;
        break;

        default:
        break;
        //case Double:

        //case String:
    }

    return v;
}


/**
 * \brief Converte o #Value dado para outro que armazena um inteiro
 * 
 * @param v  O #Value fornecido
 * @return   O #Value com a informação armazenada num inteiro
 */
Value convertToInt(Value v) {
    Value result;
    result.type = Int;

    // Escolha do método de conversão em função do tipo guardado em v
    switch(v.type) {
        case Char:
            result.integer = (int)v.character;
            break;
        case Double:
            result.integer = (int)v.decimal;
            break;
        case String:
            result.integer = atoi(v.string);
            break;
        default:
            break;
    }

    return result;
}


/**
 * \brief Converte o #Value dado para outro que armazena um valor decimal
 * 
 * @param v  O #Value fornecido
 * @return   O #Value com a informação armazenada num double
 */
Value convertToDouble(Value v) {
    Value result;
    result.type = Double;

    // Escolha do método de conversão em função do tipo guardado em v
    switch(v.type) {
        case Char:
            result.decimal = (double)v.character;
            break;
        case Int:
            result.decimal = (double)v.integer;
            break;
        case String:
            result.decimal = strtod(v.string, &v.string + (int)strlen(v.string));
            break;
        default:
            break;
    }

    return result;
}


/**
 * \brief Converte o #Value dado para outro que armazena um caracter
 * 
 * @param v  O #Value fornecido
 * @return   O #Value com a informação armazenada num caracter
 */
Value convertToChar(Value v) {
    Value result;
    result.type = Char;

    // Escolha do método de conversão em função do tipo guardado em v
    switch(v.type) {
        case Double:
            result.character = (char)(int)v.decimal;
            break;
        case Int:
            result.character = (char)v.integer;
            break;
        default:
            break;
    }

    return result;
}


/**
 * \brief Converte o #Value dado para outro que armazena texto
 * 
 * @param v  O #Value fornecido
 * @return   O #Value com a informação armazenada sob a forma de texto
 */
Value convertToString(Value v) {
    Value result;
    result.type = String;

    // Escolha do método de conversão em função do tipo guardado em v
    switch(v.type) {

        int size;

        case Double:
            size = (int)((ceil(log10(v.decimal))+1)*sizeof(char));
            result.string = malloc(size);

            //Converter para string
            snprintf(result.string, size, "%f", v.decimal);
            break;
        case Int:
            size = (int)((ceil(log10(v.integer))+1)*sizeof(char));
            result.string = malloc(size);
            snprintf(result.string, size, "%d", v.integer);
            break;

        case Char:
            size = (int)sizeof(char) + 1;
            result.string = malloc(size);
            result.string[0] = v.character;
            result.string[1] = '\0';
            break;
        default:
            break;
    }

    return result;
}



void NumericOperationAux(Value *a, Value *b)
{
    if (a->type == Double && b->type != Double)
        *b = convertToDouble(*b);
    else if (b->type == Double && a->type != Double)
        *a = convertToDouble(*a);
    else if (a->type == Int && b->type != Int)
        *b = convertToInt(*b);
    else if (b->type == Int && a->type != Int)
        *a = convertToInt(*a);
    else if (a->type == Char && b->type != Char)
        *b = convertToChar(*b);
    else if (b->type == Char && a->type != Char)
        *a = convertToChar(*a);
    else if (a->type == String && b->type != String)
        *b = convertToString(*b);
    else if (b->type == String && a->type != String)
        *a = convertToString(*a);
}


Value sum(Value a, Value b)
{
    NumericOperationAux(&a, &b);
    Value result;

    switch (a.type)
    {
        case Double:
        result.type = Double;
        result.decimal = a.decimal + b.decimal;
        break;

        case Int:
        result.type = Int;
        result.integer = a.integer + b.integer;
        break;

        case Char:
        result.type = Char;
        result.character = a.character + b.character;
        break;

        default:
        break;

        //case String:
    }

    return result;
}




Value subtract(Value a, Value b)
{
    NumericOperationAux(&a, &b);
    Value result;

    switch (a.type)
    {
        case Double:
        result.type = Double;
        result.decimal = a.decimal - b.decimal;
        break;

        case Int:
        result.type = Int;
        result.integer = a.integer - b.integer;
        break;

        case Char:
        result.type = Char;
        result.character = a.character - b.character;
        break;

        //case String:
        default:
        break;
    }

    return result;
}

Value divide(Value a, Value b)
{
    NumericOperationAux(&a, &b);
    Value result;

    switch (a.type)
    {
        case Double:
        result.type = Double;
        result.decimal = a.decimal / b.decimal;
        break;

        case Int:
        result.type = Int;
        result.integer = a.integer / b.integer;
        break;

        case Char:
        result.type = Char;
        result.character = a.character / b.character;
        break;

        default:
        break;
        //case String:
    }

    return result;
}

Value multiply(Value a, Value b)
{
    NumericOperationAux(&a, &b);
    Value result;

    switch (a.type)
    {
        case Double:
        result.type = Double;
        result.decimal = a.decimal * b.decimal;
        break;

        case Int:
        result.type = Int;
        result.integer = a.integer * b.integer;
        break;

        case Char:
        result.type = Char;
        result.character = a.character * b.character;
        break;

        default:
        break;
        //case String:
    }

    return result;
}

Value AND(Value a, Value b)
{
    NumericOperationAux(&a, &b);
    Value result;

    switch (a.type)
    {
        //case Double:

        case Int:
        result.type = Int;
        result.integer = a.integer & b.integer;
        break;

        case Char:
        result.type = Char;
        result.character = a.character & b.character;
        break;

        default:
        break;
        //case String:
    }

    return result;
}

Value OR(Value a, Value b)
{
    NumericOperationAux(&a, &b);
    Value result;

    switch (a.type)
    {
        //case Double:

        case Int:
        result.type = Int;
        result.integer = a.integer | b.integer;
        break;

        case Char:
        result.type = Char;
        result.character = a.character | b.character;
        break;

        default:
        break;
        //case String:
    }

    return result;
}

Value XOR(Value a, Value b)
{
    NumericOperationAux(&a, &b);
    Value result;

    switch (a.type)
    {
        //case Double:

        case Int:
        result.type = Int;
        result.integer = a.integer ^ b.integer;
        break;

        case Char:
        result.type = Char;
        result.character = a.character ^ b.character;
        break;

        default:
        break;
        //case String:
    }

    return result;
}

Value module(Value a, Value b)
{
    NumericOperationAux(&a, &b);
    Value result;

    switch (a.type)
    {
        case Double:
        result.type = Double;
        result.decimal = fmod(a.decimal, b.decimal);
        break;

        case Int:
        result.type = Int;
        result.integer = a.integer % b.integer;
        break;

        case Char:
        result.type = Char;
        result.character = a.character % b.character;
        break;

        default:
        break;
        //case String:
    }

    return result;
}

Value exponentiate(Value a, Value b)
{
    NumericOperationAux(&a, &b);
    Value result;

    switch (a.type)
    {
        case Double:
        result.type = Double;
        result.decimal = pow(a.decimal, b.decimal);
        break;

        case Int:
        result.type = Int;
        result.integer = (int)pow(a.integer, b.integer);
        break;

        case Char:
        result.type = Char;
        result.character = (char)pow(a.character, b.character);
        break;

        default:
        break;
        //case String:
    }

    return result;
}