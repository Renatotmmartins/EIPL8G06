/**
* @file contém a implementação das funções correspondentes
        * às operações relacionadas com blocos
*/

#include "stack.h"
#include "logicOperations.h"

/**
 * \brief Executa um bloco dentro de uma stack
 * @param s O estado do programa
 * @param block bloco fornecido
 * @return Value que é resultado da operação do bloco dentro da stack
 */

Value execute (State* s, Value block) {
    processInput (&block.block, s);
    return s->stack->value;
}

/**
 * \brief Executa um bloco dentro de uma stack enquanto houver um valor verdadeiro no topo da stack
 * @param st a stack fornecida
 * @param block bloco fornecido
 */

void executeWhileTrue (State* s, Value block) {
    while (!isEmpty(s->stack) && isTrue(s->stack->value))
        execute (s, block);
}

/**
 * \brief Mofica cada valor da array para a respetiva imagem pela função block.
 * @param s     o estado do programa
 * @param block bloco fornecido
 */
void map (State* s, Value block){

    if(isEmpty(s->stack)==0){
        Stack st = s->stack;
        s->stack = s->stack->previous;
        map(s, block);
        s->stack = st;
        execute(s, block);
    }
}

/**
 * \brief Retira da stack os elementos que não satisfazem a condição do block
 * @param s     o estado do programa
 * @param block bloco fornecido
 */
void filter (State* s, Value block){

    if(isEmpty(s->stack)==0){
        Stack st = s->stack;
        s->stack = s->stack->previous;
        filter(s, block);
        Stack a=convertToStack(deepCopy(st->value)).array;
        s->stack = a;
        if(isTrue(execute(s, block))==0)
            eraseTop(st);
        
        s->stack = st;
        disposeStack(a);
    }
}

/**
 * \brief Aplica a função do block enquanto que o tamanho da stack seja no mínimo 2
 * @param s     o estado do programa
 * @param block bloco fornecido
 */
void fold (State* s, Value block){

    while(isEmpty(s->stack)==0 && isEmpty(s->stack->previous)==0)
        execute(s,block);
    
}