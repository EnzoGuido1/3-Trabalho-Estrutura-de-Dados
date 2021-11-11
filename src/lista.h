#ifndef LISTA_H
#define LISTA_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "declaracoes.h"

//armazena espaço minimo para uma celula de uma lista
void *callocCelulaLista();

//retorna a primeira posição de uma lista
Posic getheadLista(List list);

//retorna o tamanho de uma lista
int gettamanhoLista(List list);

//retorna a ultima posiição de uma lista
Posic getlastLista(List list);

//retorna a celula anterior a celula passada no argumento
Posic getpreviousLista(List list, Posic aux);

//retorna a celula posterior a celula passada no argumento
Posic getnextLista(Posic aux);

//retorna a celula anterior a celula passada no argumento
Posic getantLista(List list, Posic aux);

//retorna o ponteiro para dados de uma celula da lista
void *getdataList(Posic aux);

//retorna um ponteiro para uma lista vazia com tamanho 0
List CriaLista();

//remove uma celula da lista de acordo com o ponteiro para dados (x) passado no argumento
void RemoveCelulaLista(List list, void *x);

//remove uma celula da lista de acordo com o ponteiro para dados (cpf) passado no argumento, faz a comparação de acordo com a outra função passada no argumento como getData
void RemoveCelulaListaPorData(List list, char *cpf, char *getData(void *auxDados));

//retorna a celula de uma lista de acordo com o index passado no argumento
Posic NaPosicaoLista(List list, int index);

//libera todos os dados armazenados de uma lista e posteriormente libera o ponteiro para lista
void FreeLista(List list, int tipo);

//libera uma lista sem liberar os dados contidos nela (caso haja algum)
void FreeListaSemDados(List list);

//insere um elemento na ultima posição da lista com os dados void* iten passado como argumento
void InsereElementoLista(List list, Iten iten);

//imprime a lista no terminal com os dados da função passado no argumento
void printList(List list, char *getData(void *auxDados));

/**/
#endif