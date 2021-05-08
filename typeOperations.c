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


/**
 * \brief Converte o #Value dado para outro que armazena um inteiro
 *
 * @param a  O #Value fornecido
 * @return   O #Value com a informação armazenada num inteiro
 */
Value convertToInt(Value a) {
    char* str;
    Convert(Int, integer, (long long)a.decimal, a.integer, (long long)a.character, str = toString(a); result.integer = atoi(str); free(str);)  
}

/**
 * \brief Converte o #Value dado para outro que armazena um valor decimal
 *
 * @param a  O #Value fornecido
 * @return   O #Value com a informação armazenada num double
 */
Value convertToDouble(Value a) {
    char* str;
    Convert(Double, decimal, a.decimal, (double)a.integer, (double)a.character, str = toString(a); result.decimal = atof(str); free(str);)
}

/**
 * \brief Converte o #Value dado para outro que armazena um caracter
 *
 * @param a  O #Value fornecido
 * @return   O #Value com a informação armazenada num caracter
 */
Value convertToChar(Value a) {
    Convert(Char, character, (char)(long long)a.decimal, (char)a.integer, a.character, result.character = '\0';);
}

/**
 * \brief Converte o #Value dado para outro que armazena texto
 *
 * @param a  O #Value fornecido
 * @return   O #Value com a informação armazenada sob a forma de texto
 */
Value convertToString(Value a) {
    Convert(String, array, stringToStack(convertFloatToString(a)), stringToStack(convertIntToString(a)), stringToStack(convertCharToString(a)), a.array = stringToStack(copyString(a));)
}

/**
 * \brief Converte o #Value dado, que armazena um número fracionário, para texto
 *
 * @param v  O #Value fornecido
 * @return   Um apontador com a informação armazenada sob a forma de texto
 */
char* convertFloatToString(Value v) {
    char useless[100];
    int size = snprintf(useless, 100, "%f", v.decimal) + 1;
    char* ans = malloc(size * sizeof(char));

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
    int size = (int)((ceil(log10(v.integer))+1));
    char* ans = malloc(size * sizeof(char)); //Aloca memória suficiente
    //Converte para inteiro
    snprintf(ans, size, "%lld", v.integer);
    return ans;
}


/**
 * \brief Converte o #Value dado, que armazena um caracter, para texto
 *
 * @param v  O #Value fornecido
 * @return   Um apontador com a informação armazenada sob a forma de texto
 */
char* convertCharToString(Value v) {

    char* ans = malloc(2 * sizeof(char)); //Aloca memória suficiente
    ans[0] = v.character;
    ans[1] = '\0';

    return ans;
}


/**
 * \brief Copia a string do #Value dado para outra string
 *
 * @param v  O #Value fornecidos
 * @return   Um apontador para a cópia
 */
char* copyString(Value v) {
    char *str = toString(v);
    char* ans = malloc((strlen(str) + 1) * sizeof(char));//Aloca memória suficiente
    strcpy(ans, str);

    //free(str);

    return ans;
}

/**
 * \brief Converte os valores dados para o tipo pedido
 * @param type Tipo do valor
 * @param val Valor dado
 * @return Valor dado no tipo pedido
 */
Value convertToType(DataType type, Value val) {
    switch(type) {
        case Double:    return convertToDouble(val);
        case Int:       return convertToInt(val);
        case Char:      return convertToChar(val);
        case String:    return convertToString(val);
        default:        return fromDecimal(UNDEFINED);
    }
}

/**
 * \brief Converte o valor para o tipo pedido e desaloca-o
 * @param a Valor dado
 * @return Valor convertido para o tipo pedido
 */
Value convertAndDisposeToDouble(Value a) {
    convertAndDisposeTo(Double)
}
/**
 * \brief Converte o valor para o tipo pedido e desaloca-o
 * @param a Valor dado
 * @return Valor convertido para o tipo pedido
 */
Value convertAndDisposeToInt(Value a) {
    convertAndDisposeTo(Int)
}
/**
 * \brief Converte o valor para o tipo pedido e desaloca-o
 * @param a Valor dado
 * @return Valor convertido para o tipo pedido
 */
Value convertAndDisposeToChar(Value a) {
    convertAndDisposeTo(Char)
}
/**
 * \brief Converte o valor para o tipo pedido e desaloca-o
 * @param a Valor dado
 * @return Valor convertido para o tipo pedido
 */
Value convertAndDisposeToString(Value a) {
    convertAndDisposeTo(String)
}