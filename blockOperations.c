/**
* @file contém a implementação das funções correspondentes
* às operações relacionadas com blocos
*/
#include <stdio.h>
#include <string.h>
#include "stack.h"
#include "logicOperations.h"
#include "stackOperations.h"
#include "arrayOperations.h"

/**
 * \brief Executa um bloco dentro de uma stack
 * @param s O estado do programa
 * @param block bloco fornecido
 * @return Value que é resultado da operação do bloco dentro da stack
 */

Value execute (State* s, Stack st, Value block) {
    Stack temp = s->stack;
    s->stack = st;
    processInput (&block.block, s);
    s->stack = temp;
    return st->value;
}


/**
 * \brief Executa um bloco dentro de uma stack enquanto houver um valor verdadeiro no topo da stack
 * @param st a stack fornecida
 * @param block bloco fornecido
 */

void executeWhileTrue (State* s, Value block) {
    while (!isEmpty(s->stack) && isTrue(s->stack->value))
        execute (s, s->stack, block);
}

/**
 * \brief Mofica cada valor da array para a respetiva imagem pela função block.
 * @param s     o estado do programa
 * @param block bloco fornecido
 */
void map (State* s, Value block){
    Stack aux = empty();

    while (!isEmpty(s->stack))
        push(aux, pop(s->stack));

    while (!isEmpty(aux)) {
        push(s->stack, pop(aux));
        execute(s, s->stack, block);
    }

    disposeStack(aux);
}

/**
 * \brief Retira da stack os elementos que não satisfazem a condição do block
 * @param s     o estado do programa
 * @param block bloco fornecido
 */
void filter (State* s, Value block){
    Stack aux = empty(); //stack para conter os elementos pea ordem certa

    while (!isEmpty(s->stack)) //colocar os elementos
        push(aux, pop(s->stack));

    while (!isEmpty(aux)) {
        Stack temp = empty(); //stack para realizar a comparação
        push(temp, deepCopy(aux->value));
        execute(s, temp, block); //executa a operação
        if (isTrue(pop(temp)))
            push(s->stack, pop(aux));
        else
            eraseTop(aux);
        disposeStack(temp);
    }

    disposeStack(aux);
}

/**
 * \brief Aplica a função do block enquanto que o tamanho da stack seja no mínimo 2
 * @param s     o estado do programa
 * @param st    o array sobre o qual fazer fold
 * @param block bloco fornecido
 */
Value fold (State* s, Stack st, Value block){
    Stack aux = empty();

    while (!isEmpty(st->previous))
        push(aux, pop(st));

    while (!isEmpty(aux)) {
        push(st, pop(aux));
        execute(s, st, block);
    }

    disposeStack(aux);
    return st->value;
}