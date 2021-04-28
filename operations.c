/**
 * @file contém a implementação das funções correspondentes às operações
 * sobre a stack
 */

#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "operations.h"
#include "typeOperations.h"
#include "arrayOperations.h"

//! O comprimento máximo de uma string de input
#define MAXINPUTLENGTH 10000

/**
 * \brief Lê uma linha de input
 *
 * De notar que a função retorna um apontador alocado dinamicamente que, por isso,
 * deve ser desalocado quando deixar de ser usado.
 *
 * @return A string que contém a linha que foi lida
 */
char* getInput ()
{
    char *line = malloc(MAXINPUTLENGTH);

    assert(fgets(line, MAXINPUTLENGTH,stdin) != NULL);
    int l = strlen(line);

    if (line[l - 1] == '\n')
        line[l - 1] = '\0';

    return line;
}


/**
 * \brief Decrementa o valor do tipo #Value.
 *
 * @param a  o elemento do tipo #Value.
 * @return   o elemento do tipo #Value decrementado.
 */
Value decrement(Value a) {
    UNARYOPERATION(a.decimal - 1, a.integer - 1, a.character - 1, a.array);
}


/**
 * \brief Incrementa o valor do tipo #Value.
 *
 * @param a  o elemento do tipo #Value.
 * @return   o elemento do tipo #Value incrementado.
 */
Value increment( Value a) {
    UNARYOPERATION(a.decimal + 1, a.integer + 1, a.character + 1, a.array);
}

/**
 * \brief Aplica a negação binária a um elemento do tipo #Value.
 *
 * @param a  o elemento do tipo #Value.
 * @return   o elemento do tipo #Value resultante de aplicar a negação.
 */
Value negate(Stack st, Value a) {
    UNARYOPERATION(UNDEFINED, ~a.integer, ~a.character, merge(st,a.array);st=a.array;a=pop(st));
}


/**
 * \brief Converte elementos do tipo #Value para os tipos adequados para executar uma operação numérica.
 *
 * @param a  o elemento do tipo #Value.
 * @param b  o elemento do tipo #Value.
 */
void NumericOperationAux(Value *a, Value *b) {
    /*
        Para realizar uma operação numérica é necessário
        que se use o menor dos dois tipos (Double é o menor, depois Int, e
        finalmente Char)
    */
    if(a->type < b->type)
        NumericOperationAux(b,a);
    
    *a = convertToType(b->type, *a);
}


/**
 * \brief Soma dois elementos do tipo #Value.
 *
 * @param a  o elemento do tipo #Value.
 * @param b  o elemento do tipo #Value.
 * @return     resultado da soma de a com b.
 */
Value sum(Value a, Value b) {
    NUMERICOPERATION(a.decimal + b.decimal, a.integer + b.integer, a.character + b.character);
}


/**
 * \brief Subtrai dois elementos do tipo #Value.
 *
 * @param a  o elemento do tipo #Value.
 * @param b  o elemento do tipo #Value.
 * @return     resultado da subtração de a com b.
 */
Value subtract(Value a, Value b) {
    NUMERICOPERATION(a.decimal - b.decimal, a.integer - b.integer, a.character - b.character);
}
/**
 * \brief Divide dois elementos do tipo #Value.
 *
 * @param a  o elemento do tipo #Value.
 * @param b  o elemento do tipo #Value.
 * @return     resultado da divisão de a com b.
 */
Value divide(Value a, Value b) {
    //Se estivermos a tratar de strings, faz a operação correspondente
    if(a.type == String)
        return separateBySubstr(a,b); //TODO:: VERIFICAR ORDEM

    NUMERICOPERATION(a.decimal / b.decimal, a.integer / b.integer, a.character / b.character);
}
/**
 * \brief Multiplica dois elementos do tipo #Value.
 *
 * @param a  o elemento do tipo #Value.
 * @param b  o elemento do tipo #Value.
 * @return     resultado da multiplicação de a com b.
 */
Value multiply(Value a, Value b) {
    NUMERICOPERATION(a.decimal * b.decimal, a.integer * b.integer, a.character * b.character);
}
/**
 * \brief Aplica a conjunção a dois elementos do tipo #Value.
 *
 * @param a  o elemento do tipo #Value.
 * @param b  o elemento do tipo #Value.
 * @return     o elemento do tipo #Value resultante de aplicar a conjunção.
 */
Value and(Value a, Value b) {
    NUMERICOPERATION(UNDEFINED, a.integer & b.integer, a.character & b.character);
}
/**
 * \brief Aplica a disjunção a dois elementos de tipo #Value.
 *
 * @param a  o elemento do tipo #Value.
 * @param b  o elemento do tipo #Value.
 * @return   o elemento do tipo #Value resultante de aplicar a disjunção.
 */
Value or(Value a, Value b) {
    NUMERICOPERATION(UNDEFINED, a.integer | b.integer, a.character | b.character);
}
/**
 * \brief Aplica o ou explosivo a dois elementos do tipo #Value.
 *
 * @param a  o elemento do tipo #Value.
 * @param b  o elemento do tipo #Value.
 * @return   o elemento do tipo #Value resultante de aplicar o ou explosivo.
 */
Value xor(Value a, Value b) {
    NUMERICOPERATION(UNDEFINED, a.integer ^ b.integer, a.character ^ b.character);
}
/**
 * \brief Calcula o resto da divisão inteira entre dois elementos do tipo #Value.
 *
 * @param a  o elemento do tipo #Value que atua como dividendo.
 * @param b  o elemento do tipo #Value que atua como divisor.
 * @return   o resto da divisao inteira.
 */
Value module(Value a, Value b) {
    NUMERICOPERATION(fmod(a.decimal, b.decimal), a.integer % b.integer, a.character % b.character);
}

/**
 * \brief Calcula a potencia entre dois elementos do tipo #Value.
 *
 * @param a  o elemento do tipo #Value que atua como base.
 * @param b  o elemento do tipo #Value que atua como expoente.
 * @return   a potencia de a com b.
 */
Value exponentiate(Value a, Value b) {
    //Se estivermos a tratar de strings, faz a operação correspondente
    if(a.type == String)
        return substr(a,b); //TODO:: VERIFICAR ORDEM

    NUMERICOPERATION(pow(a.decimal, b.decimal), (int)pow(a.integer, b.integer), (char)pow(a.character, b.character));
}

/**
 * \brief    Lê todas as linhas restantes do input e insere-as na stack.
 *           
 *           Concatena todas as linhas numa só string.
 * 
 * @param st A stack fornecida
 */
void readAllLines(Stack st) {
    //Alocar dinamicamente a string de resultado e a
    //string que guarda o valor de cada linha individualmente
    char* str = malloc(sizeof(char) * MAXINPUTLENGTH);
    char* curLine = malloc(sizeof(char) * MAXINPUTLENGTH);

    //Enquanto houver input para ler
    while(scanf("%s", curLine)) {
        //Concatena as strings
        strcat(str, curLine);
    }
    //Liberta a string que guarda a linha atual, por não ser mais precisa
    free(curLine);

    push(st, fromString(str));
}