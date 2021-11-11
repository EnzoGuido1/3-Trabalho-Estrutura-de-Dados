#include "hashTable.h"

#include "avl.h"
#include "consultasFuncoes.h"
#include "declaracoes.h"
#include "imprimeSvg.h"
#include "leitura.h"
#include "lista.h"
#include "locacoesData.h"
#include "parametrosData.h"
#include "pessoasData.h"
#include "quadrasData.h"

typedef struct registro {
    void* lista;
} Registro;

typedef struct hash {
    Registro* vetor;
    int tamanho;
} Hash;

Tabela criaTabela(int nx) {
    if (nx < 0)
        return NULL;
    Hash* tabela = calloc(1, sizeof(Hash));
    tabela->tamanho = nx;
    tabela->vetor = calloc(nx, sizeof(Registro));
    return tabela;
}

int criaChave(Hash* tabela, char* string) {
    int contNx = 0;
    for (int i = 0; i < strlen(string); i++) {
        contNx = contNx + string[i];
    }
    contNx = contNx % tabela->tamanho;
    return contNx;
}

void insereRegistro(Tabela tabelaEspalhamento, char* string, void* dadoLista) {
    Hash* tabela = tabelaEspalhamento;
    int contNx = criaChave(tabela, string);

    if (!tabela->vetor[contNx].lista) {
        tabela->vetor[contNx].lista = CriaLista();
    }
    InsereElementoLista(tabela->vetor[contNx].lista, dadoLista);
}

Posic getRegistro(Tabela tabela, char* chave) {
    Hash* hash = tabela;
    int index = criaChave(hash, chave);
    if (hash->vetor[index].lista) {
        return hash->vetor[index].lista;
    } else {
        // puts("Erro getRegistro");
        return NULL;
    }
}

bool existeChave(Tabela tabela, char* chave) {
    Hash* hash = tabela;
    int index = criaChave(hash, chave);
    if (hash->vetor[index].lista) {
        return true;
    } else {
        return false;
    }
}

void removeChave(Tabela tabela, char* chave) {
    Hash* hash = tabela;
    if (existeChave(tabela, chave) == false)
        return;
    else {
        int index = criaChave(hash, chave);
        RemoveCelulaLista(hash->vetor[index].lista, chave);
    }
}

void* retornaRegistroLista(Tabela tabela, int index) {
    Hash* hash = tabela;
    return hash->vetor[index].lista;
}

void freeRegistro(Tabela tabela, int tipo) {
    Hash* hash = tabela;
    for (int i = 0; i < hash->tamanho; i++) {
        FreeLista(hash->vetor[i].lista, tipo);
        free(hash->vetor[i].lista);
    }
    free(hash->vetor);
}
