/**
 * @file contém a implementação das funções correspondentes às operações
 * sobre a stack
 */

#include <string.h>
#include "operations.h"

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
            result.decimal = strtod(v.string);
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
    result.type = Double;

    // Escolha do método de conversão em função do tipo guardado em v
    switch(v.type) {
        case Double:
            result.character = (char)(int)v.decimal;
            break;
        case Int:
            result.decimal = (char)v.integer;
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
        case Double:
            int size = (int)((ceil(log10(v.decimal))+1)*sizeof(char));
            result.string = malloc(size);

            //Converter para string
            snprintf(result.string, size, "%f", result.decimal);
            break;
        case Int:
            int size = (int)((ceil(log10(v.integer))+1)*sizeof(char));
            result.string = malloc(size);

            //Converter para string
            snprintf(result.string, size, "%d", result.integer);
            break;

        case Char:
            int size = (int)sizeof(char);
            result.string = malloc(size);
            //Converter para string
            snprintf(result.string, size, "%c", result.character);
            break;
    }

    return result;
}