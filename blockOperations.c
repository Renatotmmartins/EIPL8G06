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
 * \brief Avalia se um bloco representa a instrução vazia
 * @param a   o bloco, em forma de string
 * @return Um inteiro que simboliza o valor lógico (1 caso seja verdadeiro e 0 caso seja falso)
 */
bool isEmptyBlock(char* a) {
    for (; *a; a++)
        if (*a != ' ')
            return false;
    return true;
}

/**
 * \brief Executa um bloco dentro de uma stack
 * @param s O estado do programa
 * @param st A stack
 * @param block bloco fornecido
 * @return Value que é resultado da operação do bloco dentro da stack
 */
void execute (State* s, Stack st, Value block) {
    Stack temp = s->stack;
    s->stack = st;
    processInput (&block.block, s);
    s->stack = temp;
}

/**
 * \brief Executa um bloco dentro de uma stack que comtém o Value indicado
 * @param s O estado do programa
 * @param a O Value indicado
 * @param block bloco fornecido
 * @return Value que é resultado da operação do bloco dentro da stack
 */
Value executeValue(State* s, Value a, Value block) {
    Stack temp = empty();
    push(temp, a);
    execute(s, temp, block);
    Value ans = pop(temp);
    disposeStack(temp);
    return ans;
}

/**
 * \brief Executa um bloco dentro de uma stack enquanto houver um valor verdadeiro no topo da stack
 * @param st a stack fornecida
 * @param block bloco fornecido
 */
void executeWhileTrue (State* s, Value block) {
    push(s->stack, fromInteger(1)); //Adiciona um valor verdadeiro no topo da stack para este não se perder no pop do while
    bool dispose = false;
    while (!isEmpty(s->stack) && (dispose = true) && isTrue(top(s->stack))) {
        eraseTop(s->stack);
        dispose = false;
        execute (s, s->stack, block);
    }
    
    if (dispose)
        eraseTop(s->stack); //Apaga o zero que está no topo da stack
    disposeValue(block);
}

/**
 * \brief Mofica cada valor da array para a respetiva imagem pela função block.
 * @param s     o estado do programa
 * @param block bloco fornecido
 */
void map (State* s, Stack st, Value block){
    Stack aux = empty();

    while (!isEmpty(st))
        push(aux, pop(st));

    while (!isEmpty(aux)) {
        push(st, pop(aux));
        execute(s, st, block);
    }

    disposeStack(aux);
}

/**
 * \brief Retira da stack os elementos que não satisfazem a condição do block
 * @param s     o estado do programa
 * @param block bloco fornecido
 */
void filter (State* s, Stack st, Value block){
    Stack aux = empty(); //stack para conter os elementos pea ordem certa

    while (!isEmpty(st)) //colocar os elementos
        push(aux, pop(st));

    while (!isEmpty(aux)) {
        push(st, deepCopy(top(aux)));
        execute(s, st, block); //executa a comparação
        Value a = pop(st);
        if (isTrue(a))
            push(st, pop(aux));
        else
            eraseTop(aux);
        disposeValue(a);
    }

    disposeStack(aux);
}

/**
 * \brief Aplica a função do block enquanto que o tamanho da stack seja no mínimo 2
 * @param s     o estado do programa
 * @param st    o array sobre o qual fazer fold
 * @param block bloco fornecido
 */
void fold (State* s, Stack st, Value block){
    Stack aux = empty();

    while (length(st) > 1)
        push(aux, pop(st));

    while (!isEmpty(aux)) {
        push(st, pop(aux));
        execute(s, st, block);
    }

    disposeStack(aux);
}