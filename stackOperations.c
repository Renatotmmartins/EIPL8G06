/**
 * @file contém a implementação das funções correspondentes
 * às operações de manipulação da stack
 */

#include "operations.h"
#include "stackOperations.h"
#include "arrayOperations.h"
#include "blockOperations.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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
Value copyElement(State* s, Value n) {
    if (n.type == Block) {
        Value a = sort(s, pop(s->stack), n);
        disposeValue(n);
        return a;
    } else
        return deepCopy(getElement(s->stack, n.integer));
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
 * \brief Escreve na consola o elemento no topo da stack, seguido de uma quebra de linha
 *
 * @param st A stack dada
 */
void printTop(Stack st) {
    printVal(top(st));
    printf("\n");
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
    free(line);
}


/**
 * \brief Duplica o elemento do topo da stack (i.e. coloca uma cópia do topo da stack no topo da stack)
 *
 * @param st  A stack
 */
void duplicate(Stack st) {
    push(st, deepCopy(top(st)));
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
    if (n <= 0) {
        disposeStack(st);
        return empty();
    } else if (n == 1)
        return st;

    Stack b = clone(st);

    while (--n)
        st = merge (st, n == 1 ? b : clone(b));

    return st;
}
/**
 * \brief Função que cria uma stack com os números de 0 a n-1
 * @param n Número dado
 * @return Stack preenchida com o conteúdo pedido
 */

Stack range(long long n) {    
    Stack a = empty();
    for (long long i = 0; i < n; ++i)
        push (a,fromInteger(i));
    return a;
}

/**
 * \brief Se o Input for um inteiro devolve o seu range, se for um array devolve o seu tamanho
 * @param a o elemento do tipo Value
 * @return Devolve o range, se for inteiro, ou o tamanho, se for array.
 */
Value comma(State* s, Value a){
    Value aux;
    switch(a.type){
        case Char:
        return fromStack(range(a.character));
        case Int: //Retorna o range [0...n-1]
        return fromStack(range(a.integer));
        case String:
        case Array: //Retorna o tamanho da array
        aux = fromInteger(length(a.array));
        disposeStack(a.array);
        return aux;
        case Block:
        aux = pop(s->stack);
        filter(s, aux.array, a);
        return aux;
        //Operação não definida
        default: return fromInteger(UNDEFINED);
    }
}