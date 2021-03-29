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

/**
 *
 * \brief O ponto de entrada da aplicação.
 * 
 */
int main() {
    char *line = NULL;
	size_t size = 0;
	
    //Usa-se getline porque o scanf para de ler ao encontrar um
    //espaço.
    size_t read = getline(&line, &size,stdin);

    //getline lê o caracter '\n', logo coloca-se u, '\0' no seu lugar
    //para não interferir no processamento
    line[read - 1] = '\0';

    Stack st = empty();

    processInput(line, &st);
    printStackLine(&st);
    
    return 0;
}
