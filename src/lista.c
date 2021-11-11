#include "lista.h"

#include "avl.h"
#include "consultasFuncoes.h"
#include "declaracoes.h"
#include "hashTable.h"
#include "imprimeSvg.h"
#include "leitura.h"
#include "locacoesData.h"
#include "parametrosData.h"
#include "pessoasData.h"
#include "quadrasData.h"

typedef struct celulaLista {
    void *Dados;
    struct celulaLista *prox;
    struct celulaLista *ant;

} CelulaLista;

//struct lista da lista dinamica, contem o tamanho e referencias de ultimo e primeiro elemento da lista
typedef struct lista {
    int tamanho;
    CelulaLista *cabeca;
    CelulaLista *rabo;

} Lista;

void setValor(void *Sdata, void *valor) {
    CelulaLista *celula = Sdata;
    celula->Dados = valor;
}

void *callocCelulaLista() {
    CelulaLista *celula = calloc(1, sizeof(CelulaLista));
    return celula;
}

Posic getheadLista(List list) {
    Lista *lista = list;
    if (!lista->tamanho) {
        return NULL;
    }
    return lista->cabeca;
}

int gettamanhoLista(List list) {
    Lista *lista = list;
    if (!lista->tamanho) {
        return 0;
    }
    return lista->tamanho;
}

Posic getlastLista(List list) {
    Lista *lista = list;
    if (!lista->tamanho) {
        return NULL;
    }
    return lista->rabo;
}

Posic getpreviousLista(List list, Posic aux) {
    Lista *ponteiro = list;
    CelulaLista *aux1 = aux;
    if (aux1 == ponteiro->cabeca) {
        return NULL;
    }
    return aux1->ant;
}

Posic getnextLista(Posic aux) {
    CelulaLista *ponteiro = aux;
    if (ponteiro->prox == NULL) {
        return NULL;
    }
    return ponteiro->prox;
}

Posic getantLista(List list, Posic aux) {
    CelulaLista *aux1 = aux;
    return aux1->ant;
}

void *getdataList(Posic aux) {
    CelulaLista *ponteiro = aux;
    if (aux == NULL) {
        return 0;
    }
    return ponteiro->Dados;
}

List CriaLista() {
    Lista *ponteiro = malloc(sizeof(Lista));
    ponteiro->tamanho = 0;
    ponteiro->cabeca = NULL;
    ponteiro->rabo = NULL;
    return ponteiro;
}

void RemoveCelulaLista(List list, void *x) {
    Lista *lista = list;
    CelulaLista *aux3 = lista->cabeca;
    if (!lista->tamanho) {
        printf("Lista Vazia!");
        return;
    }
    while ((getdataList(aux3)) != x) {
        if (aux3->prox) {
            aux3 = aux3->prox;
        } else {
            puts("elemento com este valor nao existe");
            return;
        }
    }
    if (aux3 == lista->cabeca) {
        lista->cabeca = lista->cabeca->prox;
        lista->cabeca->ant = NULL;
    } else if (aux3 == lista->rabo) {
        lista->rabo = aux3->ant;
        lista->rabo->prox = NULL;
    } else {
        CelulaLista *aux2 = aux3->ant;
        CelulaLista *aux4 = aux3->prox;
        if (!aux3 || !aux2) {
            return;
        }
        aux4->ant = aux2;
        aux2->prox = aux3->prox;
    }
    lista->tamanho--;
    // free(aux3->Dados);
    free(aux3);
}

void RemoveCelulaListaPorData(List list, char *cpf, char *getData(void *auxDados)) {
    Lista *lista = list;
    CelulaLista *aux3 = lista->cabeca;
    if (!lista->tamanho) {
        printf("Lista Vazia!");
        return;
    }
    while (strcmp(getData(getdataList(aux3)), cpf)) {
        if (aux3->prox) {
            aux3 = aux3->prox;
        }
        if (!strcmp(getData(getdataList(aux3)), cpf))
            break;
    }

    if (strcmp(getData(getdataList(aux3)), cpf)) {
        puts("elemento com este valor nao existe");
        return;
    }

    if (aux3 == lista->cabeca && aux3 == lista->rabo) {
        lista->cabeca = NULL;
        lista->rabo = NULL;
    } else if (aux3 == lista->cabeca) {
        lista->cabeca = lista->cabeca->prox;
        lista->cabeca->ant = NULL;
    } else if (aux3 == lista->rabo) {
        lista->rabo = aux3->ant;
        lista->rabo->prox = NULL;
    } else {
        CelulaLista *aux2 = aux3->ant;
        CelulaLista *aux4 = aux3->prox;
        if (!aux3 || !aux2) {
            return;
        }
        aux4->ant = aux2;
        aux2->prox = aux3->prox;
    }
    lista->tamanho--;
    free(aux3->Dados);
    free(aux3);
}

Posic NaPosicaoLista(List list, int index) {
    Lista *lista = list;
    CelulaLista *aux = lista->cabeca;
    if (index < 0 || index > lista->tamanho - 1) {
        puts("Index Invalido");
        return NULL;
    }
    for (int i = 0; i < index; i++) {
        aux = aux->prox;
    }
    return aux;
}

void FreeLista(List list, int tipo) {
    if (!list)
        return;
    Lista *lista = list;
    if (!lista->tamanho || lista->tamanho == 0)
        return;
    CelulaLista *aux = lista->cabeca, *aux2;
    for (int i = 0; i < lista->tamanho; i++) {
        aux2 = aux;
        Iten *ponteiro = aux->Dados;
        if (tipo == 1) {
            freeDadosPessoa(ponteiro);
        }
        if (tipo == -1) {
            FreeLista(getDataPessoasLista(ponteiro), 0);
            FreeLista(getDataLocacoesLista(ponteiro), 0);
            free(getDataPessoasLista(ponteiro));
            free(getDataLocacoesLista(ponteiro));
            // FreeLista(getDataLocacoesLista(ponteiro), 0);
            // free(getDataLocacoesLista(ponteiro));
        }
        free(ponteiro);

        aux = aux->prox;
        free(aux2);
    }
    // free(lista);
}

void InsereElementoLista(List list, Iten iten) {
    Lista *lista = list;
    CelulaLista *aux = calloc(1, sizeof(CelulaLista));
    aux->Dados = iten;
    if (lista->tamanho == 0) {
        lista->cabeca = aux;
        lista->rabo = aux;
        aux->prox = NULL;
        aux->ant = NULL;
    } else {
        aux->ant = lista->rabo;
        lista->rabo->prox = aux;
        lista->rabo = aux;
        aux->prox = NULL;
    }
    lista->tamanho++;
}

void printList(List list, char *getData(void *auxDados)) {
    Lista *lista = list;
    if (!lista)
        return;
    CelulaLista *aux = getheadLista(lista);
    while (aux) {
        printf("[%s]-", getData(aux->Dados));
        aux = getnextLista(aux);
    }
    puts(" ");
}
