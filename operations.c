/**
 * @file
 * @brief contém a implementação das funções correspondentes às operações
 * sobre a stack
 */

#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "value.h"
#include "stack.h"
#include "operations.h"
#include "stackOperations.h"
#include "typeOperations.h"
#include "arrayOperations.h"
#include "blockOperations.h"

//! O comprimento máximo de uma string de input
#define MAXINPUTLENGTH 1000000

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
    char *line = malloc(MAXINPUTLENGTH);
    assert(fgets(line, MAXINPUTLENGTH,stdin) != NULL);
    long long l = strlen(line);

    if (line[l - 1] == '\n')
        line[l - 1] = '\0';

    return line;
}


/**
 * \brief Decrementa o valor do tipo #Value se for um inteiro, um double ou um caracter. Se for uma string ou array retira o elemento que está no fundo da stack.
 *
 * @param s  o pointer para o estado do programa.
 * @param a  o elemento do tipo #Value.
 * @return   o elemento do tipo #Value decrementado.
 */
Value decrement(State* s,Value a) {
    //operação não definida para blocos
    assert(a.type != Block);

    if (a.type >= String) { //Se o tipo do Value for string ou array 
        Value aux = popBottom(a.array);
        push(s->stack,a);
        return aux;
    }
    //UNARYOPERATION(a.decimal - 1, a.integer - 1, a.character - 1);
    switch (a.type) {
        case Double:
            a.decimal = a.decimal - 1; break;
        case Int:
            a.integer = a.integer - 1; break;
        case Char:
            a.character = a.character - 1; break;
        default:
            break;
    }
    return a;
}


/**
 * \brief Incrementa o valor do tipo #Value, se for um inteiro, um double ou um caracter. Se for uma string ou array retira o elemento que está no topo da stack. .
 *
 * @param s  o pointer para o estado do programa.
 * @param a  o elemento do tipo #Value.
 * @return   o elemento do tipo #Value incrementado.
 */
Value increment(State* s,Value a) {
    //operação não definida para blocos
    assert(a.type != Block);

    if (a.type >= String) {
        Value aux = pop(a.array);
        push(s->stack,a);
        return aux;
    }
    //UNARYOPERATION(a.decimal + 1, a.integer + 1, a.character + 1);
    switch (a.type) {
        case Double:
            a.decimal = a.decimal + 1; break;
        case Int:
            a.integer = a.integer + 1; break;
        case Char:
            a.character = a.character + 1; break;
        default:
            break;
    }
    return a;
}

/**
 * \brief Aplica a negação binária a um elemento do tipo #Value.
 *
 * @param s  o pointer para o estado do programa.
 * @param a  o elemento do tipo #Value.
 * @return   o elemento do tipo #Value resultante de aplicar a negação.
 */
void negate(State* s, Value a) {
    if (a.type == Block) {
        execute(s, s->stack, a);
        disposeValue(a);
    }    
    else if (a.type >= String) {
        s->stack = merge(s->stack, a.array);
    }
    else {
        UNARYOPERATION(UNDEFINED, ~a.integer, ~a.character);
        push(s->stack, a);
    }
}


/**
 * \brief Converte elementos do tipo #Value para os tipos adequados para executar uma operação numérica.
 *
 * @param a  o elemento do tipo #Value.
 * @param b  o elemento do tipo #Value.
 */
void NumericOperationAux(Value *a, Value *b) {
    /*
        Para realizar uma operação numérica é necessário
        que se use o menor dos dois tipos (Double é o menor, depois Int, e
        finalmente Char)
    */
    if(a->type < b->type)
        NumericOperationAux(b,a);
    
    *a = convertToType(b->type, *a);
}


/**
 * \brief Soma dois elementos do tipo #Value, se forem do tipo inteiro, caracter ou double. Caso contrário, junta as duas stacks resultantes dos elementos fornecidos.
 *
 * @param a  o elemento do tipo #Value.
 * @param b  o elemento do tipo #Value.
 * @return     resultado da soma de a com b.
 */
Value sum(Value a, Value b) {
    //operação não definida para blocos
    assert(a.type != Block && b.type != Block);

    if (a.type >= String || b.type >= String) {//Se um dos dois elementos for uma string ou array 
        a = convertToStack(a);
        b = convertToStack(b);
        Value ans = fromStack(merge(a.array,b.array));
        ans.type = a.type > b.type ? a.type : b.type; //o maior dos dois tipos
        return ans;
    }
    //NUMERICOPERATION(a.decimal + b.decimal, a.integer + b.integer, a.character + b.character);
    NumericOperationAux(&a,&b);
    switch (a.type) {
        case Double:
            a.decimal += b.decimal; break;
        case Int:
            a.integer += b.integer; break;
        case Char:
            a.character += b.character; break;
        default:
            break;
    }
    return a;
}


/**
 * \brief Subtrai dois elementos do tipo #Value.
 *
 * @param a  o elemento do tipo #Value.
 * @param b  o elemento do tipo #Value.
 * @return     resultado da subtração de a com b.
 */
Value subtract(Value a, Value b) {
    //operação só definida para valores numéricos
    assert(a.type < String && b.type < String);

    //NUMERICOPERATION(a.decimal - b.decimal, a.integer - b.integer, a.character - b.character);
    NumericOperationAux(&a,&b);
    switch (a.type) {
        case Double:
            a.decimal -= b.decimal; break;
        case Int:
            a.integer -= b.integer; break;
        case Char:
            a.character -= b.character; break;
        default:
            break;
    }
    return a;
}
/**
 * \brief Divide dois elementos do tipo #Value, se for uma string divide-os pelos seus espaços.
 *
 * @param a  o elemento do tipo #Value.
 * @param b  o elemento do tipo #Value.
 * @return     resultado da divisão de a com b.
 */
Value divide(Value a, Value b) {
    //operação não definida para blocos
    assert(a.type != Block && b.type != Block);

    //Se estivermos a tratar de strings, faz a operação correspondente
    if(a.type >= String) {
        assert(b.type >= String); //ambos os operandos são strings ou arrays
        return separateBySubstr(a,b);
    }

    // NUMERICOPERATION(a.decimal / b.decimal, a.integer / b.integer, a.character / b.character);
    NumericOperationAux(&a,&b);
    assert(!isTrue(isEqual(fromInteger(0), b))); //descartar divisão por zero

    switch (a.type) {
        case Double:
            a.decimal /= b.decimal;
            break;
        case Int:
            a.integer /= b.integer;
            break;
        case Char:
            a.character /= b.character;
            break;
        default:
            break;
    }
    return a;
}
/**
 * \brief Multiplica dois elementos do tipo #Value. Se o tipo do #Value a for uma string ou array repete-o b vezes. Se o tipo do #Value b for um block aplica o fold. 
 *
 * @param a  o elemento do tipo #Value.
 * @param b  o elemento do tipo #Value.
 * @return     resultado da multiplicação de a com b.
 */
Value multiply(State* s, Value a, Value b) {
    if (b.type == Block) {
        assert(a.type == Array || a.type == String); //a é um array ou string
        fold(s, a.array, b);
        disposeValue(b);
        return a;
    } else if (a.type >= String) {
        assert(b.type == Int); //b é um inteiro
        a.array = repeat(a.array, b.integer);
        return a;
    }

    assert(a.type < String && b.type < String); //a e b são numéricos
    // NUMERICOPERATION(a.decimal * b.decimal, a.integer * b.integer, a.character * b.character);
    NumericOperationAux(&a,&b);
    switch (a.type) {
        case Double:
            a.decimal *= b.decimal;
            break;
        case Int:
            a.integer *= b.integer;
            break;
        case Char:
            a.character *= b.character;
            break;
        default:
            break;
    }
    return a;
}
/**
 * \brief Aplica a conjunção a dois elementos do tipo #Value.
 *
 * @param a  o elemento do tipo #Value.
 * @param b  o elemento do tipo #Value.
 * @return     o elemento do tipo #Value resultante de aplicar a conjunção.
 */
Value and(Value a, Value b) {
    //operação definida apenas para inteiros e caracteres
    assert((a.type == Int && b.type == Int) || (a.type == Char && b.type == Char));
    NUMERICOPERATION(UNDEFINED, a.integer & b.integer, a.character & b.character);
}
/**
 * \brief Aplica a disjunção a dois elementos de tipo #Value.
 *
 * @param a  o elemento do tipo #Value.
 * @param b  o elemento do tipo #Value.
 * @return   o elemento do tipo #Value resultante de aplicar a disjunção.
 */
Value or(Value a, Value b) {
    //operação definida apenas para inteiros e caracteres
    assert((a.type == Int && b.type == Int) || (a.type == Char && b.type == Char));
    NUMERICOPERATION(UNDEFINED, a.integer | b.integer, a.character | b.character);
}
/**
 * \brief Aplica o ou explosivo a dois elementos do tipo #Value.
 *
 * @param a  o elemento do tipo #Value.
 * @param b  o elemento do tipo #Value.
 * @return   o elemento do tipo #Value resultante de aplicar o ou explosivo.
 */
Value xor(Value a, Value b) {
    //operação definida apenas para inteiros e caracteres
    assert((a.type == Int && b.type == Int) || (a.type == Char && b.type == Char));
    NUMERICOPERATION(UNDEFINED, a.integer ^ b.integer, a.character ^ b.character);
}
/**
 * \brief Calcula o resto da divisão inteira entre dois elementos do tipo #Value. Se o tipo do #Value b for um block aplica a função map.
 *
 * @param s  o estado do programa
 * @param a  o elemento do tipo #Value que atua como dividendo.
 * @param b  o elemento do tipo #Value que atua como divisor.
 * @return   o resto da divisao inteira.
 */
Value module(State* s, Value a, Value b) {
    if (b.type == Block) {
        assert(a.type == Array || a.type == String);
        map(s, a.array, b);
        disposeValue(b);
        return a;
    }
    //a e b são valores numéricos
    assert(a.type < String && b.type < String);
    NUMERICOPERATION(fmod(a.decimal, b.decimal), a.integer % b.integer, a.character % b.character);
}

/**
 * \brief Calcula a potencia entre dois elementos do tipo #Value. Se o tipo do #Value a for um array ou string devolve o índice onde se encontra a sub-string. 
 *
 * @param a  o elemento do tipo #Value que atua como base.
 * @param b  o elemento do tipo #Value que atua como expoente.
 * @return   a potencia de a com b.
 */
Value exponentiate(Value a, Value b) {
    assert(a.type != Block && b.type != Block);

    //Se estivermos a tratar de strings, faz a operação correspondente
    if (a.type >= Char && b.type >= Char)
        return substrAndDispose(a,b); //TODO:: VERIFICAR ORDEM

    //a e b são valores numéricos
    assert(a.type < String && b.type < String);
    NUMERICOPERATION(pow(a.decimal, b.decimal), (long long)pow(a.integer, b.integer), (char)pow(a.character, b.character));
}

/**
 * \brief    Lê todas as linhas restantes do input e insere-as na stack.
 *           
 *           Concatena todas as linhas numa só string.
 * 
 * @param st A stack fornecida
 */
void readAllLines(Stack st) {
    //Alocar dinamicamente a string de resultado e a
    //string que guarda o valor de cada linha individualmente
    char* str = malloc(sizeof(char) * MAXINPUTLENGTH);
    char* curLine = malloc(sizeof(char) * MAXINPUTLENGTH);
    str[0] = '\0';
    //Enquanto houver input para ler
    while(fgets(curLine, MAXINPUTLENGTH,stdin) != NULL) {
        //Para ser possível parar a leitura na consola
        if(strcmp(curLine, "--ENDOFFILE--\n") == 0)
            break;
        //Concatena as strings
        strcat(str, curLine);        
    }

    //Liberta a string que guarda a linha atual, por não ser mais precisa
    free(curLine);
    push(st, fromString(str));
    free(str);
}

/**
 * \brief    Separa a string dada pelos espaços.
 *           
 * @param v  O #Value que contém a string
 * 
 * @return   O #Value que contém a stack resultante
 */
Value splitByWhitespace(Value v) {
    Value copy = deepCopy(v);
    for(long long i = 0; i < length(v.array); i++) {
        if(v.array->values[i].character == '\n')
            copy.array->values[i].character = ' ';
    }
    return separateBySubstr(copy, convertToString(fromCharacter(' ')));
}

/**
 * \brief    Separa a string dada pelos caracteres de mudança de linhas.
 *           
 * @param v  O #Value que contém a string
 * 
 * @return   O #Value que contém a stack resultante
 */
Value splitByLinebreak(Value v) {
    return separateBySubstr(v, convertToString(fromCharacter('\n')));
}