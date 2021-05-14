/**
 * @file que contém as funções relacionadas com o Value
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "value.h"
#include "stack.h"

/**
 * \brief Converte um inteiro para tipo #Value.
 *
 * @param i  o inteiro
 * @return   o inteiro convertido para #Value.
 */
Value fromInteger(long long i){
    Value val;

    val.type=Int;
    val.integer=i;

    return val;
}

/**
 * \brief Converte um double para tipo #Value.
 *
 * @param d  o double
 * @return   o double convertido para #Value.
 */
Value fromDecimal(double d){
    Value val;

    val.type=Double;
    val.decimal=d;

    return val;
}

/**
 * \brief Converte um caracter para tipo #Value.
 *
 * @param ch  o caracter
 * @return    o caracter convertido para #Value.
 */
Value fromCharacter(char ch){
    Value val;

    val.type=Char;
    val.character=ch;

    return val;
}

/**
 * \brief Converte uma string para tipo #Value. Não liberta a str.
 *
 * @param str  a string. Não é libertada.
 * @return     a string convertida para #Value.
 */
Value fromString(char* str){
    Value val;

    val.type = String;

    val.array = stringToStack(str);
    return val;
}

/**
 * \brief Cria um value a partir de um bloco com a forma de string. A string não é libertada.
 * @param block bloco dado. Não é libertado.
 * @param length Tamanho da string + 1
 * @return Value criado a partir de um bloco com a forma da string
 */

Value fromBlock(char* block, long long length) {
    Value val;

    val.type = Block;
    val.block = malloc( length * sizeof (char));
    memcpy(val.block,block,(length-1) * sizeof (char));
    val.block [(length-1)] = '\0';
    return val;
}

/**
 * \brief Copia valor que esteja inicialmente na stack
 * @param v Valor inicialmente dado
 * @return Valor copiado na sua nova localização.
 */
Value deepCopy(Value v) {
    Value copy = v;

    if (v.type == Array || v.type == String)
        copy.array = clone(v.array);

    else if (v.type == Block)
        copy.block = strdup(v.block);

    return copy;
}

/**
* \brief Efetua print do valor dado
* @param top Valor a ser dado print
*/

void printVal(Value top) {
    switch (top.type) {
        case Double:    printf("%g", top.decimal);      break;
        case Int:       printf("%lld", top.integer);      break;
        case Char:      printf("%c", top.character);    break;
        case String:
        case Array:     printStack(top.array);          break;
        case Block:     printf("{%s}", top.block);       break;
    }
}