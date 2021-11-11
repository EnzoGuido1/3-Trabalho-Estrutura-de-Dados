#include "quadrasData.h"

#include "avl.h"
#include "consultasFuncoes.h"
#include "declaracoes.h"
#include "hashTable.h"
#include "imprimeSvg.h"
#include "leitura.h"
#include "lista.h"
#include "locacoesData.h"
#include "parametrosData.h"
#include "pessoasData.h"

typedef struct quadra {
    char cep[100];
    char corC[30];
    char corP[30];

    double x;
    double y;
    double w;
    double h;
    double sw;

    void* pessoasLista;
    void* locacoesLista;
} Quadra;

char* getDataCep(void* Sdata) {
    Quadra* quadra = Sdata;
    return quadra->cep;
}

char* getDataCorC(void* Sdata) {
    Quadra* quadra = Sdata;
    return quadra->corC;
}

char* getDataCorP(void* Sdata) {
    Quadra* quadra = Sdata;
    return quadra->corP;
}

double getDataX(void* Sdata) {
    Quadra* quadra = Sdata;
    return quadra->x;
}

double getDataY(void* Sdata) {
    Quadra* quadra = Sdata;
    return quadra->y;
}

double getDataW(void* Sdata) {
    Quadra* quadra = Sdata;
    return quadra->w;
}

double getDataH(void* Sdata) {
    Quadra* quadra = Sdata;
    return quadra->h;
}

void* getDataPessoasLista(void* Sdata) {
    Quadra* quadra = Sdata;
    return quadra->pessoasLista;
}

void* getDataLocacoesLista(void* Sdata) {
    Quadra* quadra = Sdata;
    return quadra->locacoesLista;
}

//set
void setDataCep(void* Sdata, char* Scep) {
    Quadra* quadra = Sdata;
    strcpy(quadra->cep, Scep);
}

void setDataCorC(void* Sdata, char* ScorC) {
    Quadra* quadra = Sdata;
    strcpy(quadra->corC, ScorC);
}

void setDataCorP(void* Sdata, char* ScorP) {
    Quadra* quadra = Sdata;
    strcpy(quadra->corP, ScorP);
}

void setDataX(void* Sdata, double Sx) {
    Quadra* quadra = Sdata;
    quadra->x = Sx;
}

void setDataY(void* Sdata, double Sy) {
    Quadra* quadra = Sdata;
    quadra->y = Sy;
}

void setDataW(void* Sdata, double Sw) {
    Quadra* quadra = Sdata;
    quadra->w = Sw;
}

void setDataH(void* Sdata, double Sh) {
    Quadra* quadra = Sdata;
    quadra->h = Sh;
}

void setDataPessoasLista(void* Sdata, void* SpessoasLista) {
    Quadra* quadra = Sdata;
    quadra->pessoasLista = SpessoasLista;
}

void setDataLocacoesLista(void* Sdata, void* SlocacoesLista) {
    Quadra* quadra = Sdata;
    quadra->locacoesLista = SlocacoesLista;
}

void* callocDataQuadra(char* cep, char* corc, char* corp, double x, double y, double w, double h) {
    Quadra* quadra = calloc(1, sizeof(Quadra));
    setDataCep(quadra, cep);
    setDataCorC(quadra, corc);
    setDataCorP(quadra, corp);
    setDataX(quadra, x);
    setDataY(quadra, y);
    setDataW(quadra, w);
    setDataH(quadra, h);
    return quadra;
}
