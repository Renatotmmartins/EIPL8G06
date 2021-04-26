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
    State st;
    char *line = getInput();
    char *pointer = line;
    st.stack=empty();
    initializeVariables(&st);
    processInput(&pointer, &st);
    printStackLine(st.stack);
    //O line é alocado dinamicamente e, por isso, deve ser desalocado quando deixar de ser usado.
    free(line);
    disposeStack(st.stack);
    return 0;
}
