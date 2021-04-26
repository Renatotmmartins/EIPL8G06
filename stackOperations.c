/**
 * @file contém a implementação das funções correspondentes
 * às operações de manipulação da stack
 */

#include "operations.h"
#include "stackOperations.h"
#include <stdlib.h>
#include <string.h>

/**
 * \brief Retorna uma cópia do n-ésimo elemento da stack dada (o topo da stack é 0)
 *
 * Um erro ocorre quando n é negativo ou a stack tem n ou menos elementos (segmentation fault)
 *
 * @param st A stack dada
 * @param n  A posição do elemento a retornar
 *
 * @return Uma cópia do n-ésimo elemento da stack
 */
Value copyElement(Stack st, Value n) {
    return deepCopy(getElement(st, n.integer));
}

/**
 * \brief Roda os primeiros n elementos da stack
 *
 * @param st A stack dada
 * @param n  O número de elementos a rodar
 */
void rotateTop(Stack st, int n) {
    /* Para rodar os primeiros n elementos da stack basta removê-los
       e inseri-los novamente pela ordem que foram removidos. */

    Value elements[n];

    for(int i = n - 1; i >= 0; i--) {
        elements[i] = pop(st);
    }

    for(int i = 1; i < n; i++) {
        push(st, elements[i]);
    }

    push(st, elements[0]);
}


/**
 * \brief Lê uma linha do input e insere-a como uma string na stack.
 *
 * @param st A stack dada
 */
void readLine(Stack st)
{
    char* line = getInput();
    push (st, fromString (line));
}


/**
 * \brief Duplica o elemento do topo da stack (i.e. coloca uma cópia do topo da stack no topo da stack)
 *
 * @param st  A stack
 */
void duplicate(Stack st) {
    push(st, deepCopy(st->value));
}

/**
 * \brief Repete a stack n vezes
 *
 * @param st Stack dada
 *
 * @param n número de vezes que a stack é repetida
 *
 * @return stack n vezes repetida
 */
Stack repeat(Stack st, int n) {
    Stack b = st;
    while (--n)
        b = merge (b,clone(st));

    return b;
}


Stack range(int n) {    
    Stack a = empty();
    for (int i = 0; i < n; ++i)
        push (a,fromInteger(i));

    return a;
}