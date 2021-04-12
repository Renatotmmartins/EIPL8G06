/**
 * @file contém a implementação das funções correspondentes às operações
 * sobre a stack
 */

#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "operations.h"

/**
 * \brief Lê uma linha de input
 *
 * De notar que a função retorna um apontador alocado dinamicamente que, por isso,
 * deve ser desalocado quando deixar de ser usado.
 *
 * @return A string que contém a linha que foi lida
 */
char* getInput ()
{
        char *line = NULL;
        size_t size = 0;

        //Usa-se getline porque o scanf para de ler ao encontrar um
        //espaço.
        size_t read = getline(&line, &size,stdin);

        //getline lê o caracter '\n', logo coloca-se um '\0' no seu lugar
        //para não interferir no processamento
        if(line[read - 1] == '\n')
            line[read - 1] = '\0';
            
        return line;
}

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
Value getElement(Stack* st, int n)
{
    //if (n < 0)
        //ERRO: input inválido

    while (n--)
    {
        st = st->previous;

        //if (st->previous == 0)
            //ERRO: a stack tem n ou menos elementos
    }

    Value copy = st->value;

    if (copy.type == String)
    {
        copy.string = malloc(strlen(copy.string));
        strcpy(copy.string, st->value.string);
    }

    return copy;
}

/**
 * \brief Roda os primeiros n elementos da stack
 *
 * @param st A stack dada
 * @param n  O número de elementos a rodar
 */
void rotateTop(Stack* st, int n) {
    /* Para rodar os primeiros n elementos da stack basta removê-los
       e inseri-los novamente pela ordem que foram removidos. */

    Value elements[n];

    int i;

    for(i = 0; i < n; i++) {
        elements[i] = pop(st);
    }

    for(int i = 0; i < n; i++) {
        push(st, elements[i]);
    }
}

/**
 * \brief Decrementa o valor do tipo #Value.
 *
 * @param v  o elemento do tipo #Value.
 * @return   o elemento do tipo #Value decrementado.
 */
Value decrement(Value v)
{
    switch (v.type)
    {
        case Char:
        v.character--;
        break;

        case Int:
        v.integer--;
        break;

        case Double:
        v.decimal--;
        break;

        default:
        break;
        //case String:
    }

    return v;
}

/**
 * \brief Incrementa o valor do tipo #Value.
 *
 * @param v  o elemento do tipo #Value.
 * @return   o elemento do tipo #Value incrementado.
 */
Value increment(Value v)
{
    switch (v.type)
    {
        case Char:
        v.character++;
        break;

        case Int:
        v.integer++;
        break;

        case Double:
        v.decimal++;
        break;

        default:
        break;

        //case String:
    }

    return v;
}

/**
 * \brief Aplica a negação binária a um elemento do tipo #Value.
 *
 * @param v  o elemento do tipo #Value.
 * @return   o elemento do tipo #Value resultante de aplicar a negação.
 */
Value negate(Value v)
{
    switch (v.type)
    {
        case Char:
        v.character = ~v.character;
        break;

        case Int:
        v.integer = ~v.integer;
        break;

        default:
        break;
        //case Double:

        //case String:
    }

    return v;
}

/**
 * \brief Converte o #Value dado para outro que armazena um inteiro
 * 
 * @param v  O #Value fornecido
 * @return   O #Value com a informação armazenada num inteiro
 */
Value convertToInt(Value v) {
    Value result;
    result.type = Int;

    // Escolha do método de conversão em função do tipo guardado em v
    switch(v.type) {
        case Char:
            result.integer = (int)v.character;
            break;
        case Double:
            result.integer = (int)v.decimal;
            break;
        case String:
            result.integer = atoi(v.string);
            break;
        default:
            break;
    }

    return result;
}


/**
 * \brief Converte o #Value dado para outro que armazena um valor decimal
 * 
 * @param v  O #Value fornecido
 * @return   O #Value com a informação armazenada num double
 */
Value convertToDouble(Value v) {
    Value result;
    result.type = Double;

    // Escolha do método de conversão em função do tipo guardado em v
    switch(v.type) {
        case Char:
            result.decimal = (double)v.character;
            break;
        case Int:
            result.decimal = (double)v.integer;
            break;
        case String:
            result.decimal = strtod(v.string, &v.string + (int)strlen(v.string));
            break;
        default:
            break;
    }

    return result;
}


/**
 * \brief Converte o #Value dado para outro que armazena um caracter
 * 
 * @param v  O #Value fornecido
 * @return   O #Value com a informação armazenada num caracter
 */
Value convertToChar(Value v) {
    Value result;
    result.type = Char;

    // Escolha do método de conversão em função do tipo guardado em v
    switch(v.type) {
        case Double:
            result.character = (char)(int)v.decimal;
            break;
        case Int:
            result.character = (char)v.integer;
            break;
        default:
            break;
    }

    return result;
}


/**
 * \brief Converte o #Value dado para outro que armazena texto
 * 
 * @param v  O #Value fornecido
 * @return   O #Value com a informação armazenada sob a forma de texto
 */
Value convertToString(Value v) {
    Value result;
    result.type = String;

    // Escolha do método de conversão em função do tipo guardado em v
    switch(v.type) {

        int size;

        case Double:
            size = (int)((ceil(log10(v.decimal))+1)*sizeof(char));
            result.string = malloc(size);

            //Converter para string
            snprintf(result.string, size, "%f", v.decimal);
            break;
        case Int:
            size = (int)((ceil(log10(v.integer))+1)*sizeof(char));
            result.string = malloc(size);
            snprintf(result.string, size, "%d", v.integer);
            break;

        case Char:
            size = (int)sizeof(char) + 1;
            result.string = malloc(size);
            result.string[0] = v.character;
            result.string[1] = '\0';
            break;
        default:
            break;
    }

    return result;
}

/**
 * \brief Lê uma linha do input e insere-a como uma string na stack.
 *
 * @param st A stack dada
 */
void readLine(Stack* st)
{
    char* line = getInput();
    push (st, fromString (line));
}

/**
 * \brief Converte elementos do tipo #Value para os tipos adequados para executar uma operação numérica.
 *
 * @param a  o elemento do tipo #Value.
 * @param b  o elemento do tipo #Value.
 */
void NumericOperationAux(Value *a, Value *b)
{
    if (a->type == Double && b->type != Double)
        *b = convertToDouble(*b);
    else if (b->type == Double && a->type != Double)
        *a = convertToDouble(*a);
    else if (a->type == Int && b->type != Int)
        *b = convertToInt(*b);
    else if (b->type == Int && a->type != Int)
        *a = convertToInt(*a);
    else if (a->type == Char && b->type != Char)
        *b = convertToChar(*b);
    else if (b->type == Char && a->type != Char)
        *a = convertToChar(*a);
    else if (a->type == String && b->type != String)
        *b = convertToString(*b);
    else if (b->type == String && a->type != String)
        *a = convertToString(*a);
}

/**
 * \brief Soma dois elementos do tipo #Value.
 *
 * @param a  o elemento do tipo #Value.
 * @param b  o elemento do tipo #Value.
 * @return     resultado da soma de a com b.
 */
Value sum(Value a, Value b)
{
    NumericOperationAux(&a, &b);
    Value result;

    switch (a.type)
    {
        case Double:
        result.type = Double;
        result.decimal = a.decimal + b.decimal;
        break;

        case Int:
        result.type = Int;
        result.integer = a.integer + b.integer;
        break;

        case Char:
        result.type = Char;
        result.character = a.character + b.character;
        break;

        default:
        break;

        //case String:
    }

    return result;
}

/**
 * \brief Subtrai dois elementos do tipo #Value.
 *
 * @param a  o elemento do tipo #Value.
 * @param b  o elemento do tipo #Value.
 * @return     resultado da subtração de a com b.
 */
Value subtract(Value a, Value b)
{
    NumericOperationAux(&a, &b);
    Value result;

    switch (a.type)
    {
        case Double:
        result.type = Double;
        result.decimal = a.decimal - b.decimal;
        break;

        case Int:
        result.type = Int;
        result.integer = a.integer - b.integer;
        break;

        case Char:
        result.type = Char;
        result.character = a.character - b.character;
        break;

        //case String:
        default:
        break;
    }

    return result;
}

/**
 * \brief Divide dois elementos do tipo #Value.
 *
 * @param a  o elemento do tipo #Value.
 * @param b  o elemento do tipo #Value.
 * @return     resultado da divisão de a com b.
 */
Value divide(Value a, Value b)
{
    NumericOperationAux(&a, &b);
    Value result;

    switch (a.type)
    {
        case Double:
        result.type = Double;
        result.decimal = a.decimal / b.decimal;
        break;

        case Int:
        result.type = Int;
        result.integer = a.integer / b.integer;
        break;

        case Char:
        result.type = Char;
        result.character = a.character / b.character;
        break;

        default:
        break;
        //case String:
    }

    return result;
}

/**
 * \brief Multiplica dois elementos do tipo #Value.
 *
 * @param a  o elemento do tipo #Value.
 * @param b  o elemento do tipo #Value.
 * @return     resultado da multiplicação de a com b.
 */
Value multiply(Value a, Value b)
{
    NumericOperationAux(&a, &b);
    Value result;

    switch (a.type)
    {
        case Double:
        result.type = Double;
        result.decimal = a.decimal * b.decimal;
        break;

        case Int:
        result.type = Int;
        result.integer = a.integer * b.integer;
        break;

        case Char:
        result.type = Char;
        result.character = a.character * b.character;
        break;

        default:
        break;
        //case String:
    }

    return result;
}

/**
 * \brief Aplica a conjunção a dois elementos do tipo #Value.
 *
 * @param a  o elemento do tipo #Value.
 * @param b  o elemento do tipo #Value.
 * @return     o elemento do tipo #Value resultante de aplicar a conjunção.
 */
Value AND(Value a, Value b)
{
    NumericOperationAux(&a, &b);
    Value result;

    switch (a.type)
    {
        //case Double:

        case Int:
        result.type = Int;
        result.integer = a.integer & b.integer;
        break;

        case Char:
        result.type = Char;
        result.character = a.character & b.character;
        break;

        default:
        break;
        //case String:
    }

    return result;
}

/**
 * \brief Aplica a disjunção a dois elementos de tipo #Value.
 *
 * @param a  o elemento do tipo #Value.
 * @param b  o elemento do tipo #Value.
 * @return   o elemento do tipo #Value resultante de aplicar a disjunção.
 */
Value OR(Value a, Value b)
{
    NumericOperationAux(&a, &b);
    Value result;

    switch (a.type)
    {
        //case Double:

        case Int:
        result.type = Int;
        result.integer = a.integer | b.integer;
        break;

        case Char:
        result.type = Char;
        result.character = a.character | b.character;
        break;

        default:
        break;
        //case String:
    }

    return result;
}

/**
 * \brief Aplica o ou explosivo a dois elementos do tipo #Value.
 *
 * @param a  o elemento do tipo #Value.
 * @param b  o elemento do tipo #Value.
 * @return   o elemento do tipo #Value resultante de aplicar o ou explosivo.
 */
Value XOR(Value a, Value b)
{
    NumericOperationAux(&a, &b);
    Value result;

    switch (a.type)
    {
        //case Double:

        case Int:
        result.type = Int;
        result.integer = a.integer ^ b.integer;
        break;

        case Char:
        result.type = Char;
        result.character = a.character ^ b.character;
        break;

        default:
        break;
        //case String:
    }

    return result;
}

/**
 * \brief Calcula o resto da divisão inteira entre dois elementos do tipo #Value.
 *
 * @param a  o elemento do tipo #Value que atua como dividendo.
 * @param b  o elemento do tipo #Value que atua como divisor.
 * @return   o resto da divisao inteira.
 */
Value module(Value a, Value b)
{
    NumericOperationAux(&a, &b);
    Value result;

    switch (a.type)
    {
        case Double:
        result.type = Double;
        result.decimal = fmod(a.decimal, b.decimal);
        break;

        case Int:
        result.type = Int;
        result.integer = a.integer % b.integer;
        break;

        case Char:
        result.type = Char;
        result.character = a.character % b.character;
        break;

        default:
        break;
        //case String:
    }

    return result;
}

/**
 * \brief Calcula a potencia entre dois elementos do tipo #Value.
 *
 * @param a  o elemento do tipo #Value que atua como base.
 * @param b  o elemento do tipo #Value que atua como expoente.
 * @return   a potencia de a com b.
 */
Value exponentiate(Value a, Value b)
{
    NumericOperationAux(&a, &b);
    Value result;

    switch (a.type)
    {
        case Double:
        result.type = Double;
        result.decimal = pow(a.decimal, b.decimal);
        break;

        case Int:
        result.type = Int;
        result.integer = (int)pow(a.integer, b.integer);
        break;

        case Char:
        result.type = Char;
        result.character = (char)pow(a.character, b.character);
        break;

        default:
        break;
        //case String:
    }

    return result;
}