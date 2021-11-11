#ifndef QUADRASTADA_H
#define QUADRASTADA_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "declaracoes.h"

//bloco de get, retorna o valor de um dado expecifico da struct quando chamada
//indicado no nome da função
char* getDataCep(void* Sdata);
char* getDataCorC(void* Sdata);
char* getDataCorP(void* Sdata);
double getDataX(void* Sdata);
double getDataY(void* Sdata);
double getDataW(void* Sdata);
double getDataH(void* Sdata);

//retorna o ponteiro para lista de pessoas de uma quadra
void* getDataPessoasLista(void* Sdata);

//retorna o ponteiro para lista de locações de uma quadra
void* getDataLocacoesLista(void* Sdata);

//da calloc com espaço suficiente para todos os parametros da struct e retorna o ponteiro com esses espaços armazenados
void* callocDataQuadra(char* cep, char* corc, char* corp, double x, double y, double w, double h);

/**/
#endif