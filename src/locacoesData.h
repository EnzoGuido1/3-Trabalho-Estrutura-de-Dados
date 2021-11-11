#ifndef LOCACOESDATA_H
#define LOCACOESDATA_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "declaracoes.h"

//bloco de get, retorna o valor de um dado expecifico da struct quando chamada
//indicado no nome da função
int getDataNumeroLocacao(void* Sdata);
char* getDataComplexoLocacao(void* Sdata);
char getDataFaceLocacao(void* Sdata);
char* getDataCepLocacao(void* Sdata);
char* getDataIdLocacao(void* Sdata);
double getDataAreaLocacao(void* Sdata);
double getDatavMensaisLocacao(void* Sdata);

//retorna o tipo de locação (1 para alugada, 2 para comprada, 0 para nenhum morador)
int getDataTipoLocacao(void* Sdata);

//retorna o cpf do inquilino de uma locação
char* getDataInquilinoLocacao(void* Sdata);

//da calloc com espaço suficiente para todos os parametros da struct e retorna o ponteiro com esses espaços armazenados
void* callocDataLocacoes(int num, char* complexo, char face, char* cep, char* id, double area, double vMensais, int tipoLocacao, char* inquilino);

/**/
#endif