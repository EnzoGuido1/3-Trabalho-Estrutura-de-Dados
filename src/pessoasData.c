#include "pessoasData.h"

#include "avl.h"
#include "consultasFuncoes.h"
#include "declaracoes.h"
#include "hashTable.h"
#include "imprimeSvg.h"
#include "leitura.h"
#include "lista.h"
#include "locacoesData.h"
#include "parametrosData.h"
#include "quadrasData.h"

typedef struct pessoa {
    int tipoMoradia;  //caso a pessoa não more em lugar algum = 0, caso more de aluguel = 1, caso more em casa comprada (função m da pm) = 2
    char cpf[100];
    char nome[100];
    char sobrenome[100];
    char nascimento[15];
    char sexo;
    void* moradia;
} Pessoa;

int getDataPessoaTipoMoradia(void* Sdata) {
    Pessoa* pessoa = Sdata;
    return pessoa->tipoMoradia;
}

char* getDataPessoaCpf(void* Sdata) {
    Pessoa* pessoa = Sdata;
    return pessoa->cpf;
}

char* getDataPessoaNome(void* Sdata) {
    Pessoa* pessoa = Sdata;
    return pessoa->nome;
}

char* getDataPessoaSobrenome(void* Sdata) {
    Pessoa* pessoa = Sdata;
    return pessoa->sobrenome;
}

char getDataPessoaSexo(void* Sdata) {
    Pessoa* pessoa = Sdata;
    return pessoa->sexo;
}

char* getDataPessoaNascimento(void* Sdata) {
    Pessoa* pessoa = Sdata;
    return pessoa->nascimento;
}

void* getDataPessoaMoradia(void* Sdata) {
    Pessoa* pessoa = Sdata;
    return pessoa->moradia;
}

//set
void setDataPessoaCpf(void* Sdata, char* Scpf) {
    Pessoa* pessoa = Sdata;
    strcpy(pessoa->cpf, Scpf);
}

void setDataPessoaNome(void* Sdata, char* Snome) {
    Pessoa* pessoa = Sdata;
    strcpy(pessoa->nome, Snome);
}

void setDataPessoaSobrenome(void* Sdata, char* Ssobrenome) {
    Pessoa* pessoa = Sdata;
    strcpy(pessoa->sobrenome, Ssobrenome);
}

void setDataPessoaSexo(void* Sdata, char Ssexo) {
    Pessoa* pessoa = Sdata;
    pessoa->sexo = Ssexo;
}

void setDataPessoaNascimento(void* Sdata, char* Snascimento) {
    Pessoa* pessoa = Sdata;
    strcpy(pessoa->nascimento, Snascimento);
}

void setDataPessoaMoradia(void* Sdata, void* moradia) {
    Pessoa* pessoa = Sdata;
    pessoa->moradia = moradia;
}

void setDataPessoaTipoMoradia(void* Sdata, int tipoMoradia) {
    Pessoa* pessoa = Sdata;
    pessoa->tipoMoradia = tipoMoradia;
}

void* callocDataPessoa(char* cpf, char* nome, char* sobrenome, char sexo, char* nascimento, void* moradia, int tipoMoradia) {
    Pessoa* pessoa = calloc(1, sizeof(Pessoa));
    setDataPessoaCpf(pessoa, cpf);
    setDataPessoaNome(pessoa, nome);
    setDataPessoaSobrenome(pessoa, sobrenome);
    setDataPessoaSexo(pessoa, sexo);
    setDataPessoaNascimento(pessoa, nascimento);
    setDataPessoaMoradia(pessoa, moradia);
    setDataPessoaTipoMoradia(pessoa, tipoMoradia);
    return pessoa;
}

void freeDadosPessoa(void* dados) {
    Pessoa* pessoa = dados;
    if (pessoa->moradia) {
        free(pessoa->moradia);
    }
}
