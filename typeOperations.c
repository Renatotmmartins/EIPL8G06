#include "typeOperations.h"
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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
            result.integer = v.integer;
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
            result.decimal = atof(v.string);//strtod(v.string, &v.string + (int)strlen(v.string));
            break;
        default:
            result.decimal = v.decimal;
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
            result.character = v.character;
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

    // Escolha do método de conversão em função do tipo guardado em v
    switch(v.type) {
        case Double:
            result = convertFloatToString(v);
            break;
        case Int:
            result = convertIntToString(v);
            break;

        case Char:
            result = convertCharToString(v);
            break;
        default:
            result = copyString(v);
            break;
    }

    return result;
}

/**
 * \brief Converte o #Value dado, que armazena um número fracionário para outro que armazena texto
 *
 * @param v  O #Value fornecido
 * @return   O #Value com a informação armazenada sob a forma de texto
 */
Value convertFloatToString(Value v) {
    Value result;
    int size = (int)((ceil(log10(v.decimal))+1)*sizeof(char));
    result.string = malloc(size);

    //Converter para string
    snprintf(result.string, size, "%f", v.decimal);

    return result;
}


/**
 * \brief Converte o #Value dado, que armazena um número inteiro para outro que armazena texto
 *
 * @param v  O #Value fornecido
 * @return   O #Value com a informação armazenada sob a forma de texto
 */
Value convertIntToString(Value v) {
    Value result;
    int size = (int)((ceil(log10(v.integer))+1)*sizeof(char));
    result.string = malloc(size); //Aloca memória suficiente

    //Converte para inteiro
    snprintf(result.string, size, "%d", v.integer);

    return result;
}


/**
 * \brief Converte o #Value dado, que armazena um caracter para outro que armazena texto
 *
 * @param v  O #Value fornecido
 * @return   O #Value com a informação armazenada sob a forma de texto
 */
Value convertCharToString(Value v) {
    Value result;

    result.string = malloc(2); //Aloca memória suficiente
    result.string[0] = v.character;
    result.string[1] = '\0';

    return result;
}


/**
 * \brief Copia a string do #Value dado para outro #Value
 *
 * @param v  O #Value fornecido
 * @return   O #Value com a string copiada
 */
Value copyString(Value v) {
    Value result;

    result.string = malloc(strlen(v.string) + 1);//Aloca memória suficiente
    strcpy(result.string, v.string);

    return result;
}
