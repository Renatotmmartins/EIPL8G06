/**
 * @file contém a implementação das funções correspondentes
 * às operações relacionadas com o tipo das variáveis
 */

#include "typeOperations.h"
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define UNDEFINED 13

#define Convert(toType, unionArg, fromDouble, fromInt, fromChar, fromString) Value convertTo##toType(Value a) {\
    Value result;\
    result.type = toType;\
    switch(a.type) {\
        case Double:\
        result.unionArg = fromDouble;\
        break;\
        case Int:\
        result.unionArg = fromInt;\
        break;\
        case Char:\
        result.unionArg = fromChar;\
        break;\
        case String:\
        result.unionArg = fromString;\
        break;\
        default:\
        break;\
    }\
    return result;\
}


/**
 * \brief Converte o #Value dado para outro que armazena um inteiro
 *
 * @param a  O #Value fornecido
 * @return   O #Value com a informação armazenada num inteiro
 */
Convert(Int, integer, (int)a.decimal, a.integer, (int)a.character, atoi(a.string))


/**
 * \brief Converte o #Value dado para outro que armazena um valor decimal
 *
 * @param a  O #Value fornecido
 * @return   O #Value com a informação armazenada num double
 */
Convert(Double, decimal, a.decimal, (double)a.integer, (double)a.character, atof(a.string))


/**
 * \brief Converte o #Value dado para outro que armazena um caracter
 *
 * @param a  O #Value fornecido
 * @return   O #Value com a informação armazenada num caracter
 */
Convert(Char, character, (char)(int)a.decimal, (char)a.integer, a.character, UNDEFINED)


/**
 * \brief Converte o #Value dado para outro que armazena texto
 *
 * @param a  O #Value fornecido
 * @return   O #Value com a informação armazenada sob a forma de texto
 */
Convert(String, string, convertFloatToString(a), convertIntToString(a), convertCharToString(a), copyString(a))

/**
 * \brief Converte o #Value dado, que armazena um número fracionário, para texto
 *
 * @param v  O #Value fornecido
 * @return   Um apontador com a informação armazenada sob a forma de texto
 */
char* convertFloatToString(Value v) {
    char* ans;
    int size = (int)((ceil(log10(v.decimal))+1)*sizeof(char));
    ans = malloc(size);

    //Converter para string
    snprintf(ans, size, "%f", v.decimal);

    return ans;
}


/**
 * \brief Converte o #Value dado, que armazena um número inteiro, para texto
 *
 * @param v  O #Value fornecido
 * @return  Um apontador com a informação armazenada sob a forma de texto
 */
char* convertIntToString(Value v) {

    int size = (int)((ceil(log10(v.integer))+1)*sizeof(char));
    char* ans = malloc(size); //Aloca memória suficiente

    //Converte para inteiro
    snprintf(ans, size, "%d", v.integer);

    return ans;
}


/**
 * \brief Converte o #Value dado, que armazena um caracter, para texto
 *
 * @param v  O #Value fornecido
 * @return   Um apontador com a informação armazenada sob a forma de texto
 */
char* convertCharToString(Value v) {

    char* ans = malloc(2); //Aloca memória suficiente
    ans[0] = v.character;
    ans[1] = '\0';

    return ans;
}


/**
 * \brief Copia a string do #Value dado para outra string
 *
 * @param v  O #Value fornecido
 * @return   Um apontador para a cópia
 */
char* copyString(Value v) {

    char* ans = malloc(strlen(v.string) + 1);//Aloca memória suficiente
    strcpy(ans, v.string);

    return ans;
}
