/**
* @file contém a implementação das funções correspondentes
        * às operações relacionadas com blocos
*/

#include "stack.h"
#include "logicOperations.h"

/**
 * \brief Executa um bloco dentro de uma stack
 * @param st a stack fornecida
 * @param block bloco fornecido
 * @return Value que é resultado da operação do bloco dentro da stack
 */

Value execute (Stack st, Value block) {
    State s;
    s -> Stack = st;
    processInput (&block.block, &s);
    return st -> value;
}

/**
 * \brief Executa um bloco dentro de uma stack enquanto houver um valor verdadeiro no topo da stack
 * @param st a stack fornecida
 * @param block bloco fornecido
 */

Void execute_while_true (Stack st, Value block) {
    while (!isEmpty(st) && isTrue(st -> value))
        execute (st, block);
}