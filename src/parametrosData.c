#include "parametrosData.h"

#include "avl.h"
#include "consultasFuncoes.h"
#include "declaracoes.h"
#include "hashTable.h"
#include "imprimeSvg.h"
#include "leitura.h"
#include "lista.h"
#include "locacoesData.h"
#include "pessoasData.h"
#include "quadrasData.h"

//struct de dados, contem os dados que sao inseridos na hora de inserir um elemento
typedef struct parametros {
    char *pathEntrada;
    char *pathSaida;
    char *geo;
    char *qry;
    char *pm;

    int pathEntradaVerifica;
    int pathSaidaVerifica;
    int geoVerifica;
    int qryVerifica;
    int pmVerifica;
    int nx;
} Parametros;

//aloca memoria suficiente para uma struct de dados
void *createVar() {
    Parametros *ponteiro = calloc(1, sizeof(Parametros));
    ponteiro->pathEntrada = calloc(1, sizeof(char));
    ponteiro->pathSaida = calloc(1, sizeof(char));
    ponteiro->geo = calloc(1, sizeof(char));
    ponteiro->qry = calloc(1, sizeof(char));
    ponteiro->pm = calloc(1, sizeof(char));
    return ponteiro;
}

//bloco de get, retorna o valor de um dado expecifico da struct quando chamada indicado no nome da função
char *getVarEntrada(void *Svar) {
    Parametros *ponteiro = Svar;
    return ponteiro->pathEntrada;
}

char *getVarSaida(void *Svar) {
    Parametros *ponteiro = Svar;
    return ponteiro->pathSaida;
}

char *getVarGeo(void *Svar) {
    Parametros *ponteiro = Svar;
    return ponteiro->geo;
}

char *getVarQry(void *Svar) {
    Parametros *ponteiro = Svar;
    return ponteiro->qry;
}

char *getVarPm(void *Svar) {
    Parametros *ponteiro = Svar;
    return ponteiro->pm;
}

int getVarEntradaVerifica(void *Svar) {
    Parametros *ponteiro = Svar;
    return ponteiro->pathEntradaVerifica;
}

int getVarSaidaVerifica(void *Svar) {
    Parametros *ponteiro = Svar;
    return ponteiro->pathSaidaVerifica;
}

int getVarGeoVerifica(void *Svar) {
    Parametros *ponteiro = Svar;
    return ponteiro->geoVerifica;
}

int getVarQryVerifica(void *Svar) {
    Parametros *ponteiro = Svar;
    return ponteiro->qryVerifica;
}

int getVarPmVerifica(void *Svar) {
    Parametros *ponteiro = Svar;
    return ponteiro->pmVerifica;
}

int getVarNx(void *Svar) {
    Parametros *ponteiro = Svar;
    return ponteiro->nx;
}

//bloco de set, quando chamada a função. um dado expecifico da struct recebe o valor passado no argumento
void setVarEntrada(void *Svar, char *Entrada) {
    Parametros *ponteiro = Svar;
    ponteiro->pathEntrada = realloc(ponteiro->pathEntrada, strlen(ponteiro->pathEntrada) + strlen(Entrada) + 1);
    strcpy(ponteiro->pathEntrada, Entrada);
}

void setVarSaida(void *Svar, char *Saida) {
    Parametros *ponteiro = Svar;
    ponteiro->pathSaida = realloc(ponteiro->pathSaida, strlen(ponteiro->pathSaida) + strlen(Saida) + 1);
    strcpy(ponteiro->pathSaida, Saida);
}

void setVarGeo(void *Svar, char *Geo) {
    Parametros *ponteiro = Svar;
    ponteiro->geo = realloc(ponteiro->geo, strlen(ponteiro->geo) + strlen(Geo) + 1);
    strcpy(ponteiro->geo, Geo);
}

void setVarQry(void *Svar, char *Qry) {
    Parametros *ponteiro = Svar;
    ponteiro->qry = realloc(ponteiro->qry, strlen(ponteiro->qry) + strlen(Qry) + 1);
    strcpy(ponteiro->qry, Qry);
}

void setVarPm(void *Svar, char *Pm) {
    Parametros *ponteiro = Svar;
    ponteiro->pm = realloc(ponteiro->pm, strlen(ponteiro->pm) + strlen(Pm) + 1);
    strcpy(ponteiro->pm, Pm);
}

void setVarEntradaVerifica(void *Svar, int cont) {
    Parametros *ponteiro = Svar;
    ponteiro->pathEntradaVerifica = cont;
}

void setVarSaidaVerifica(void *Svar, int cont) {
    Parametros *ponteiro = Svar;
    ponteiro->pathSaidaVerifica = cont;
}

void setVarGeoVerifica(void *Svar, int cont) {
    Parametros *ponteiro = Svar;
    ponteiro->geoVerifica = cont;
}

void setVarQryVerifica(void *Svar, int cont) {
    Parametros *ponteiro = Svar;
    ponteiro->qryVerifica = cont;
}

void setVarPmVerifica(void *Svar, int cont) {
    Parametros *ponteiro = Svar;
    ponteiro->pmVerifica = cont;
}

void setVarNx(void *Svar, int cont) {
    Parametros *ponteiro = Svar;
    ponteiro->nx = cont;
}

void freeParametros(void *Svar) {
    Parametros *ponteiro = Svar;
    free(ponteiro->pathEntrada);
    free(ponteiro->pathSaida);
    free(ponteiro->geo);
    free(ponteiro->qry);
    free(ponteiro->pm);
    free(ponteiro);
}
