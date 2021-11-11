#include "locacoesData.h"

#include "avl.h"
#include "consultasFuncoes.h"
#include "declaracoes.h"
#include "hashTable.h"
#include "imprimeSvg.h"
#include "leitura.h"
#include "lista.h"
#include "parametrosData.h"
#include "pessoasData.h"
#include "quadrasData.h"

typedef struct locacao {
    int tipoLocacao;  //caso a locação esteja disponível para alugar = 0; caso esteja alugada = 1; caso esteja comprada = 2; caso o locatario tenha encerrado a locação, ela é removida = -1
    char id[100];
    char cep[100];
    char face;
    int num;
    char complexo[100];
    double area;
    double vMensais;
    char inquilinoCpf[100];
} Locacao;

int getDataNumeroLocacao(void* Sdata) {
    Locacao* locacao = Sdata;
    return locacao->num;
}

char* getDataComplexoLocacao(void* Sdata) {
    Locacao* locacao = Sdata;
    return locacao->complexo;
}

char getDataFaceLocacao(void* Sdata) {
    Locacao* locacao = Sdata;
    return locacao->face;
}

char* getDataCepLocacao(void* Sdata) {
    Locacao* locacao = Sdata;
    return locacao->cep;
}

char* getDataIdLocacao(void* Sdata) {
    Locacao* locacao = Sdata;
    return locacao->id;
}

double getDataAreaLocacao(void* Sdata) {
    Locacao* locacao = Sdata;
    return locacao->area;
}

double getDatavMensaisLocacao(void* Sdata) {
    Locacao* locacao = Sdata;
    return locacao->vMensais;
}

int getDataTipoLocacao(void* Sdata) {
    Locacao* locacao = Sdata;
    return locacao->tipoLocacao;
}

char* getDataInquilinoLocacao(void* Sdata) {
    Locacao* locacao = Sdata;
    return locacao->inquilinoCpf;
}

//set
void setDataNumeroLocacao(void* Sdata, int Snum) {
    Locacao* locacao = Sdata;
    locacao->num = Snum;
}

void setDataComplexoLocacao(void* Sdata, char* Scomplexo) {
    Locacao* locacao = Sdata;
    strcpy(locacao->complexo, Scomplexo);
}

void setDataFaceLocacao(void* Sdata, char Sface) {
    Locacao* locacao = Sdata;
    locacao->face = Sface;
}

void setDataCepLocacao(void* Sdata, char* Scep) {
    Locacao* locacao = Sdata;
    strcpy(locacao->cep, Scep);
}

void setDataIdLocacao(void* Sdata, char* Sid) {
    Locacao* locacao = Sdata;
    strcpy(locacao->id, Sid);
}

void setDataAreaLocacao(void* Sdata, double Sarea) {
    Locacao* locacao = Sdata;
    locacao->area = Sarea;
}

void setDatavMensaisLocacao(void* Sdata, double SvMensais) {
    Locacao* locacao = Sdata;
    locacao->vMensais = SvMensais;
}

void setDataTipoLocacao(void* Sdata, int StipoLocacao) {
    Locacao* locacao = Sdata;
    locacao->tipoLocacao = StipoLocacao;
}

void setDataInquilinoLocacao(void* Sdata, char* Sinquilino) {
    Locacao* locacao = Sdata;
    strcpy(locacao->inquilinoCpf, Sinquilino);
}

void* callocDataLocacoes(int num, char* complexo, char face, char* cep, char* id, double area, double vMensais, int tipoLocacao, char* inquilino) {
    Locacao* locacao = calloc(1, sizeof(Locacao));
    setDataNumeroLocacao(locacao, num);
    setDataComplexoLocacao(locacao, complexo);
    setDataFaceLocacao(locacao, face);
    setDataCepLocacao(locacao, cep);
    setDataIdLocacao(locacao, id);
    setDataAreaLocacao(locacao, area);
    setDatavMensaisLocacao(locacao, vMensais);
    setDataTipoLocacao(locacao, tipoLocacao);
    setDataInquilinoLocacao(locacao, inquilino);

    return locacao;
}
