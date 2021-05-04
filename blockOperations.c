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
    s.stack = st;
    processInput (&block.block, &s);
    return st -> value;
}

/**
 * \brief Executa um bloco dentro de uma stack enquanto houver um valor verdadeiro no topo da stack
 * @param st a stack fornecida
 * @param block bloco fornecido
 */

void execute_while_true (Stack st, Value block) {
    while (!isEmpty(st) && isTrue(st -> value))
        execute (st, block);
}

/**
 * \brief Mofica cada valor da array para a respetiva imagem pela função block.
 * @param st a stack fornecida
 * @param block bloco fornecido
 */
void map (Stack st, Value block){

    if(isEmpty(st)==0){
        map(st->previous, block);
        execute(st,block);
    }
}

/**
 * \brief Retira da stack os elementos que não satisfazem a condição do block
 * @param st a stack fornecida
 * @param block bloco fornecido
 */
void filter (Stack st, Value block){

    if(isEmpty(st)==0){
        filter(st->previous, block);
        Stack a=convertToStack(deepCopy(st->value)).array;
        if(isTrue(a->value)==0)
            eraseTop(st);
        
        disposeStack(a);
    }
}

/**
 * \brief Aplica a função do block enquanto que o tamanho da stack seja no mínimo 2
 * @param st a stack fornecida
 * @param block bloco fornecido
 */
void fold (Stack st, Value block){

    while(isEmpty(st)==0 && isEmpty(st->previous)==0)
        execute(st,block);
    
}