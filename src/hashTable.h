#include "avl.h"
#include "lista.h"

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "declaracoes.h"

//cria uma hash table de tamanho nx e em cada posição dessa tabela cria uma lista vazia, retorna esse ponteiro para a hash table vazia
Tabela criaTabela(int nx);

//insere na posição da chave string passada o elemento dadoLista como próximo elemento da lista dessa posição
void insereRegistro(Tabela tabelaEspelhamento, char *string, void *dadoLista);

//retorna a lista de posição correspondente a chave (passada no argumento) da hash table
Posic getRegistro(Tabela tabela, char *chave);

//retorna a lista de posição correspondente ao index (passado no argumento) da hash table
void *retornaRegistroLista(Tabela tabela, int index);

//remove um elemento da lista da posição correspondente a chave (passada no argumento) da hash table
void removeChave(Tabela tabela, char *chave);

//libera toda a memoria alocada em uma hash table, primeiro as listas que a hash table armazena depois a hash table em si
void freeRegistro(Tabela tabela, int tipo);

/**/
#endif