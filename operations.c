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

#define UNDEFINED 13

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
    char *line = malloc(10000);

    assert(fgets(line, 10000,stdin) != NULL);
    int l = strlen(line);

    if (line[l - 1] == '\n')
        line[l - 1] = '\0';

    return line;
}

#define UnaryOperation(name, caseDouble, caseInt, caseChar) Value name(Value a) {\
    switch (a.type) {\
        case Double:\
        a.decimal = caseDouble;\
        break;\
        case Int:\
        a.integer = caseInt;\
        break;\
        case Char:\
        a.character = caseChar;\
        break;\
        default:\
        break;\
    }\
    return a;\
}


/**
 * \brief Decrementa o valor do tipo #Value.
 *
 * @param a  o elemento do tipo #Value.
 * @return   o elemento do tipo #Value decrementado.
 */
UnaryOperation(decrement, a.decimal - 1, a.integer - 1, a.character - 1)

/**
 * \brief Incrementa o valor do tipo #Value.
 *
 * @param a  o elemento do tipo #Value.
 * @return   o elemento do tipo #Value incrementado.
 */
UnaryOperation(increment, a.decimal + 1, a.integer + 1, a.character + 1)

/**
 * \brief Aplica a negação binária a um elemento do tipo #Value.
 *
 * @param a  o elemento do tipo #Value.
 * @return   o elemento do tipo #Value resultante de aplicar a negação.
 */
UnaryOperation(negate, UNDEFINED, ~a.integer, ~a.character)


/**
 * \brief Converte elementos do tipo #Value para os tipos adequados para executar uma operação numérica.
 *
 * @param a  o elemento do tipo #Value.
 * @param b  o elemento do tipo #Value.
 */
void NumericOperationAux(Value *a, Value *b) {
    /*
        Arrays com os diferentes tipos de operandos e as funções a usar para converter um Value
        para esse tipo.
    */
    DataType numericTypes[4] = { Double, Int, Char, String };
    Value (*converters[4])(Value) = { &convertToDouble, &convertToInt, &convertToChar, &convertToString };

    /*
        De notar que a ordem dos elementos na array numericTypes é importante. Double tem de ser o 1º
        elemento, pois este tipo tem precedência sobre os outros (isto é, basta um operando ser double
        para o resultado também o ser)
    */
    for (int i = 0; i < 4; i++) {
        if (a->type == numericTypes[i]) {
            *b = (*converters[i])(*b);
            return;
        } else if (b->type == numericTypes[i]) {
            *a = (*converters[i])(*a);
            return;
        }
    }
}

#define NumericOperation(name, caseDouble, caseInt, caseChar) Value name(Value a, Value b) {\
    NumericOperationAux(&a, &b);\
    Value result;\
    switch (a.type)\
    {\
        case Double:\
        result.type = Double;\
        result.decimal = caseDouble;\
        break;\
        case Int:\
        result.type = Int;\
        result.integer = caseInt;\
        break;\
        case Char:\
        result.type = Char;\
        result.character = caseChar;\
        break;\
        default:\
        break;\
    }\
\
    return result;\
}


/**
 * \brief Soma dois elementos do tipo #Value.
 *
 * @param a  o elemento do tipo #Value.
 * @param b  o elemento do tipo #Value.
 * @return     resultado da soma de a com b.
 */
NumericOperation(sum, a.decimal + b.decimal, a.integer + b.integer, a.character + b.character)

/**
 * \brief Subtrai dois elementos do tipo #Value.
 *
 * @param a  o elemento do tipo #Value.
 * @param b  o elemento do tipo #Value.
 * @return     resultado da subtração de a com b.
 */
NumericOperation(subtract, a.decimal - b.decimal, a.integer - b.integer, a.character - b.character)

/**
 * \brief Divide dois elementos do tipo #Value.
 *
 * @param a  o elemento do tipo #Value.
 * @param b  o elemento do tipo #Value.
 * @return     resultado da divisão de a com b.
 */
NumericOperation(divide, a.decimal / b.decimal, a.integer / b.integer, a.character / b.character)

/**
 * \brief Multiplica dois elementos do tipo #Value.
 *
 * @param a  o elemento do tipo #Value.
 * @param b  o elemento do tipo #Value.
 * @return     resultado da multiplicação de a com b.
 */
NumericOperation(multiply, a.decimal * b.decimal, a.integer * b.integer, a.character * b.character)

/**
 * \brief Aplica a conjunção a dois elementos do tipo #Value.
 *
 * @param a  o elemento do tipo #Value.
 * @param b  o elemento do tipo #Value.
 * @return     o elemento do tipo #Value resultante de aplicar a conjunção.
 */
NumericOperation(AND, UNDEFINED, a.integer & b.integer, a.character & b.character)

/**
 * \brief Aplica a disjunção a dois elementos de tipo #Value.
 *
 * @param a  o elemento do tipo #Value.
 * @param b  o elemento do tipo #Value.
 * @return   o elemento do tipo #Value resultante de aplicar a disjunção.
 */
NumericOperation(OR, UNDEFINED, a.integer | b.integer, a.character | b.character)

/**
 * \brief Aplica o ou explosivo a dois elementos do tipo #Value.
 *
 * @param a  o elemento do tipo #Value.
 * @param b  o elemento do tipo #Value.
 * @return   o elemento do tipo #Value resultante de aplicar o ou explosivo.
 */
NumericOperation(XOR, UNDEFINED, a.integer ^ b.integer, a.character ^ b.character)

/**
 * \brief Calcula o resto da divisão inteira entre dois elementos do tipo #Value.
 *
 * @param a  o elemento do tipo #Value que atua como dividendo.
 * @param b  o elemento do tipo #Value que atua como divisor.
 * @return   o resto da divisao inteira.
 */
NumericOperation(module, fmod(a.decimal, b.decimal), a.integer % b.integer, a.character % b.character)


/**
 * \brief Calcula a potencia entre dois elementos do tipo #Value.
 *
 * @param a  o elemento do tipo #Value que atua como base.
 * @param b  o elemento do tipo #Value que atua como expoente.
 * @return   a potencia de a com b.
 */
NumericOperation(exponentiate, pow(a.decimal, b.decimal), (int)pow(a.integer, b.integer), (char)pow(a.character, b.character))
