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
#include <unistd.h>


/**
 * \brief Converte o #Value dado para outro que armazena um inteiro
 *
 * @param a  O #Value fornecido
 * @return   O #Value com a informação armazenada num inteiro
 */
Value convertToInt(Value a) {
    char* str; //Variável para armazenar string temporária quando o argumento é do tipo String

    Value result;
    result.type = Int;

    //Decide o método de conversão de acordo com o tipo original
    switch(a.type) {
        case Double:    result.integer = (long long)a.decimal;   break;
        case Int:       result.integer = a.integer;              break;
        case Char:      result.integer = a.character;            break;
        case String:    
             str = toString(a); //Obtém a string
             result.integer = atoi(str);
             free(str);
             break;
        default:                                                 break;
    }
    return result;
}

/**
 * \brief Converte o #Value dado para outro que armazena um valor decimal
 *
 * @param a  O #Value fornecido
 * @return   O #Value com a informação armazenada num double
 */
Value convertToDouble(Value a) {
    char* str;

    Value result;
    result.type = Double;

    //Decide o método de conversão de acordo com o tipo original
    switch(a.type) {
        case Double:    result.decimal = a.decimal;             break;
        case Int:       result.decimal = (double)a.integer;     break;
        case Char:      result.decimal = (double)a.character;   break;
        case String:    
            str = toString(a); //Obtém a string
            result.decimal = atof(str);
            free(str);
            break;
        default:                                                break;
    }
    return result;
}

/**
 * \brief Converte o #Value dado para outro que armazena um caracter
 *
 * @param a  O #Value fornecido
 * @return   O #Value com a informação armazenada num caracter
 */
Value convertToChar(Value a) {
    Value result;
    result.type = Char;

    //Decide o método de conversão de acordo com o tipo original
    switch(a.type) {
        case Double:    result.character = (char)(long long)a.decimal;   break;
        case Int:       result.character = (char)a.integer;              break;
        case Char:      result.character = a.character;                  break;
        case String:    result.character = '\0';                         break;
        default:                                                         break;
    }
    return result;
}

/**
 * \brief Converte o #Value dado para outro que armazena texto
 *
 * @param a  O #Value fornecido
 * @return   O #Value com a informação armazenada sob a forma de texto
 */
Value convertToString(Value a) {
    char* string = NULL;

    //Determina a forma de conversão consoante o tipo original
    switch (a.type) {
        case Double:    string = convertFloatToString(a.decimal);   break;
        case Int:       string = convertIntToString(a.integer);     break;
        case Char:      string = convertCharToString(a.character);  break;
        case String:
        case Array:
            //Copia o valor e muda apenas o tipo para Array (Strings são armazenadas como arrays de caracteres)
            a = deepCopy(a); 
            a.type = String;
            return a;
        case Block:     string = strdup(a.block);           break;
    }

    Value ans = fromString(string);
    //Liberta a string, pois não é mais necessária
    free(string);
    return ans;
}

/**
 * \brief Converte o #Value dado, que armazena um número fracionário, para texto
 *
 * @param v  O #Value fornecido
 * @return   Um apontador com a informação armazenada sob a forma de texto
 */
char* convertFloatToString(double v) {
    char useless[100];
    long long size = snprintf(useless, 100, "%g", v) + 1;
    char* ans = malloc(size * sizeof(char));

    //Converter para string
    snprintf(ans, size, "%g", v);

    return ans;
}


/**
 * \brief Converte o #Value dado, que armazena um número inteiro, para texto
 *
 * @param v  O #Value fornecido
 * @return  Um apontador com a informação armazenada sob a forma de texto
 */
char* convertIntToString(long long v) {
    long long size = (long long)((ceil(log10(v + 1)) + 1));
    char* ans = malloc(size * sizeof(char)); //Aloca memória suficiente
    //Converte para inteiro
    snprintf(ans, size, "%lld", v);
    return ans;
}


/**
 * \brief Converte o #Value dado, que armazena um caracter, para texto
 *
 * @param v  O #Value fornecido
 * @return   Um apontador com a informação armazenada sob a forma de texto
 */
char* convertCharToString(char v) {

    char* ans = malloc(2 * sizeof(char)); //Aloca memória suficiente
    ans[0] = v;
    ans[1] = '\0';

    return ans;
}


/**
 * \brief Converte os valores dados para o tipo pedido
 * @param type Tipo do valor
 * @param val Valor dado
 * @return Valor dado no tipo pedido
 */
Value convertToType(DataType type, Value val) {
    //Escolhe o tipo apropriado
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
    Value ans = convertToDouble(a);
    disposeValue(a);
    return ans; 
}
/**
 * \brief Converte o valor para o tipo pedido e desaloca-o
 * @param a Valor dado
 * @return Valor convertido para o tipo pedido
 */
Value convertAndDisposeToInt(Value a) {
    Value ans = convertToInt(a);
    disposeValue(a);
    return ans; 
}
/**
 * \brief Converte o valor para o tipo pedido e desaloca-o
 * @param a Valor dado
 * @return Valor convertido para o tipo pedido
 */
Value convertAndDisposeToChar(Value a) {
    Value ans = convertToChar(a);
    disposeValue(a);
    return ans; 
}
/**
 * \brief Converte o valor para o tipo pedido e desaloca-o
 * @param a Valor dado
 * @return Valor convertido para o tipo pedido
 */
Value convertAndDisposeToString(Value a) {
    Value ans = convertToString(a);
    disposeValue(a);
    return ans; 
}