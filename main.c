/**
 *
 * @file Contém a definição da função main
 *
 *
*/


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "parser.h"
#include "operations.h"

/**
 *
 * \brief O ponto de entrada da aplicação.
 * 
 */
int main() {
    char *line = getInput();
    Stack st = empty();
    processInput(line, &st);
    printStackLine(&st);
    //O line é alocado dinamicamente e, por isso, deve ser desalocado quando deixar de ser usado.
    free(line);
    return 0;
}
