#ifndef PARAMETROSDATA_H
#define PARAMETROSDATA_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "declaracoes.h"

//aloca memoria suficiente para uma struct de dados
void *createVar();

//bloco de get, retorna o valor de um dado expecifico da struct quando chamada
//indicado no nome da função
char *getVarEntrada(void *Svar);
char *getVarSaida(void *Svar);
char *getVarGeo(void *Svar);
char *getVarQry(void *Svar);
char *getVarPm(void *Svar);
int getVarEntradaVerifica(void *Svar);
int getVarSaidaVerifica(void *Svar);
int getVarGeoVerifica(void *Svar);
int getVarQryVerifica(void *Svar);
int getVarPmVerifica(void *Svar);
int getVarNx(void *Svar);

void freeParametros(void *Svar);
/**/
#endif