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
Value getElement(Stack st, Value n)
{
    //if (n < 0 || n.type != Integer) //permitir doubles?
        //ERRO: input inválido

    while (n.integer--)
    {
        st = st->previous;

        //if (st->previous == 0)
            //ERRO: a stack tem n ou menos elementos
    }

    return deepCopy(st->value);
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

    Value top = pop (st);
    if (top.type == String) {
        char* str = malloc((strlen(top.string) + 1) * sizeof(char));
        strcpy(str,top.string);
        push(st,fromString(str));
    }
    else
        push(st,top);

    push(st,top);
}