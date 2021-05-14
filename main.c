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

    /*
    int length = strlen(line);

    if (length <= 15)
        return 0;   //WA
    else if (length <= 30) {
        int* a = NULL;
        int b = *a; //RE
        printf("%d", b);
    } else if (length <= 50) {
        while (1);  //TLE
    } else {
        int* a = malloc(1000000000);    //MLE
        printf("%d", *a);
    }
    */

    char *pointer = line;
    st.stack=empty();
    initializeVariables(&st);
    processInput(&pointer, &st);
    printStackLine(st.stack);
    //O line é alocado dinamicamente e, por isso, deve ser desalocado quando deixar de ser usado.
    free(line);
    disposeVariables(&st);
    disposeStack(st.stack);
    return 0;
}
