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
#include "quadrasData.h"

typedef struct dados {
    void *valor;
} Dados;

typedef struct celula {
    void *Dados;
    int profundidade;
    struct celula *right;
    struct celula *left;
    struct celula *prev;
    struct celula *next;
    double min;
    double max;

} Celula;

typedef struct arvore {
    int tamanho;
    Celula *raiz;
    int (*compare)(void *, void *);
    void (*freeNode)(void *);

} Arvore;

void *getData(void *Sdata) {
    Celula *dados = Sdata;
    if (!dados) {
        return 0;
    }
    return dados->Dados;
}

void *getHead(Tree tree) {
    Arvore *arvore = tree;
    if (!tree)
        return NULL;
    return arvore->raiz;
}

double getMin(Posic celula) {
    Celula *ponteiro = celula;
    return ponteiro->min;
}

double getMax(Posic celula) {
    Celula *ponteiro = celula;
    return ponteiro->max;
}

Tree CriaArvore(int (*compare)(void *, void *), void (*freeNode)(void *)) {
    Arvore *ponteiro = malloc(sizeof(Arvore));
    ponteiro->tamanho = 0;
    ponteiro->raiz = NULL;
    ponteiro->compare = compare;
    ponteiro->freeNode = freeNode;
    return ponteiro;
}

void InsereElementoRec(Tree tree, Iten dados) {
    Arvore *arvore = tree;
    void *ponteiro;
    int tamanho = arvore->tamanho;
    InsereElemento(arvore, dados, arvore->raiz, ponteiro, 1);
}

//funcao recursiva de inserção na arvore kd, tanto de retangulo quanto de circulo
void InsereElemento(Tree tree, Iten dados, Iten celulaAtual, void *currentAux, int profundidadeGlobal) {
    Arvore *arvore = tree;
    Celula *celulaAtualAux = celulaAtual;
    Celula *aux;

    if (arvore->tamanho == 0) {
        aux = calloc(1, sizeof(Celula));
        arvore->raiz = aux;
        aux->Dados = CriaLista();
        InsereElementoLista(arvore->raiz->Dados, dados);
        aux->right = NULL;
        aux->left = NULL;
        aux->prev = NULL;
        aux->profundidade = 1;
        aux->min = getDataX(dados);
        aux->max = getDataX(dados) + getDataW(dados);
        arvore->tamanho++;
    } else {
        if (celulaAtualAux->min > getDataX(dados))
            celulaAtualAux->min = getDataX(dados);
        if (celulaAtualAux->max < getDataX(dados) + getDataW(dados))
            celulaAtualAux->max = getDataX(dados) + getDataW(dados);

        profundidadeGlobal++;
        if (arvore->compare(dados, getdataList(getheadLista(celulaAtualAux->Dados))) == 1) {
            if (!celulaAtualAux->right) {
                aux = calloc(1, sizeof(Celula));
                celulaAtualAux->right = aux;
                aux->Dados = CriaLista();
                InsereElementoLista(aux->Dados, dados);
                aux->right = NULL;
                aux->left = NULL;
                aux->prev = celulaAtualAux;
                aux->profundidade = profundidadeGlobal;
                aux->min = getDataX(dados);
                aux->max = getDataX(dados) + getDataW(dados);
                arvore->tamanho++;

            } else {
                if (celulaAtualAux->min > getDataX(dados))
                    celulaAtualAux->min = getDataX(dados);
                if (celulaAtualAux->max < getDataX(dados) + getDataW(dados))
                    celulaAtualAux->max = getDataX(dados) + getDataW(dados);
                InsereElemento(arvore, dados, celulaAtualAux->right, aux, profundidadeGlobal);
            }
        } else if (arvore->compare(dados, getdataList(getheadLista(celulaAtualAux->Dados))) == -1) {
            if (!celulaAtualAux->left) {
                aux = calloc(1, sizeof(Celula));
                celulaAtualAux->left = aux;
                aux->Dados = CriaLista();
                InsereElementoLista(aux->Dados, dados);
                aux->right = NULL;
                aux->left = NULL;
                aux->prev = celulaAtualAux;
                aux->profundidade = profundidadeGlobal;
                aux->min = getDataX(dados);
                aux->max = getDataX(dados) + getDataW(dados);
                arvore->tamanho++;

            } else {
                if (celulaAtualAux->min > getDataX(dados))
                    celulaAtualAux->min = getDataX(dados);
                if (celulaAtualAux->max < getDataX(dados) + getDataW(dados))
                    celulaAtualAux->max = getDataX(dados) + getDataW(dados);
                InsereElemento(arvore, dados, celulaAtualAux->left, aux, profundidadeGlobal);
            }
        } else {
            if (celulaAtualAux->min > getDataX(dados))
                celulaAtualAux->min = getDataX(dados);
            if (celulaAtualAux->max < getDataX(dados) + getDataW(dados))
                celulaAtualAux->max = getDataX(dados) + getDataW(dados);
            InsereElementoLista(celulaAtualAux->Dados, dados);
        }

        Balance(comparaRotacao(celulaAtualAux), celulaAtualAux, arvore);
    }
    if (celulaAtualAux)
        if (celulaAtualAux->left)
            celulaAtualAux->min = celulaAtualAux->left->min;
}

void Balance(int condicional, Posic celulaDesbalanceada, Tree arvore) {
    Celula *celula = celulaDesbalanceada;
    if (condicional == 1) {
        rotacaoEsquerda(celula, arvore);
    } else if (condicional == 2) {
        rotacaoDireita(celula, arvore);
    } else if (condicional == 3) {
        rotacaoDireita(celula->right, arvore);
        rotacaoEsquerda(celula, arvore);
    } else if (condicional == 4) {
        rotacaoEsquerda(celula->left, arvore);
        rotacaoDireita(celula, arvore);
    }
}

void *Referencia(Arvore *tree, Celula *delete) {
    if (delete->right && !delete->left) {  //delete tem so o filho direito
        return delete->right;

    } else if (delete->left && !delete->right) {  //delete tem so o filho esquerdo
        return delete->left;

    } else if (delete->left && delete->right) {  //delete tem os 2 filhos
        return minValueNode(delete->right);

    } else {  //delete não tem filhos
        return NULL;
    }
}

void arrumaMinMaxNaRecursaoDelete(Iten aux) {
    Celula *celulaAtual = aux;

    if (celulaAtual->right) {
        if (celulaAtual->right->max > celulaAtual->max) {
            celulaAtual->max = celulaAtual->right->max;
        }
    }
    if (celulaAtual->left) {
        if (celulaAtual->left->min < celulaAtual->min) {
            celulaAtual->min = celulaAtual->left->min;
        }
        if (celulaAtual->left->max > celulaAtual->max) {
            celulaAtual->max = celulaAtual->left->max;
        }
    }
}

void deleteNodeRecursive(Arvore *tree, Celula *celulaAtual, Iten aux, double *MinMax) {
    if (celulaAtual == NULL) {
        return;
    }

    Arvore *arvore = tree;

    if (tree->compare(aux, getdataList(getheadLista(celulaAtual->Dados))) == 1) {  //desce para direita
        deleteNodeRecursive(tree, celulaAtual->right, aux, MinMax);

        atualizaMinMaxSoCelula(celulaAtual);
        if (celulaAtual->min < MinMax[0])
            MinMax[0] = celulaAtual->min;
        else
            celulaAtual->min = MinMax[0];

        if (celulaAtual->max > MinMax[1])
            MinMax[1] = celulaAtual->max;
        else
            celulaAtual->max = MinMax[1];

        arrumaMinMaxNaRecursaoDelete(celulaAtual);
    }

    else if (tree->compare(aux, getdataList(getheadLista(celulaAtual->Dados))) == -1) {  //desce para esquerda
        deleteNodeRecursive(tree, celulaAtual->left, aux, MinMax);

        atualizaMinMaxSoCelula(celulaAtual);
        if (celulaAtual->min < MinMax[0])
            MinMax[0] = celulaAtual->min;
        else
            celulaAtual->min = MinMax[0];

        if (celulaAtual->max > MinMax[1])
            MinMax[1] = celulaAtual->max;
        else
            celulaAtual->max = MinMax[1];

        arrumaMinMaxNaRecursaoDelete(celulaAtual);
    }

    else if (tree->compare(aux, getdataList(getheadLista(celulaAtual->Dados))) == 0) {
        Celula *novo = Referencia(tree, celulaAtual);
        if (arvore->tamanho == 1) {
            arvore->tamanho = 0;
            arvore->raiz = NULL;
            FreeLista(celulaAtual->Dados, 0);
            free(celulaAtual->Dados);
            free(celulaAtual);
            return;

        } else if (!celulaAtual->right && !celulaAtual->left) {  //caso o no a ser removido seja uma folha
            if (celulaAtual == celulaAtual->prev->right)
                celulaAtual->prev->right = NULL;
            else
                celulaAtual->prev->left = NULL;
        } else if (!celulaAtual->left && celulaAtual->right || !celulaAtual->right && celulaAtual->left) {  //caso o no a ser removido tenha um filho
            if (celulaAtual == tree->raiz)
                tree->raiz = novo;
            else {
                if (celulaAtual == celulaAtual->prev->right)
                    celulaAtual->prev->right = novo;
                else
                    celulaAtual->prev->left = novo;
            }
            novo->prev = celulaAtual->prev;
        } else {  //caso 3, o no a ser deletado tem 2 filhos
            if (novo == celulaAtual->right) {
                if (celulaAtual != tree->raiz) {
                    if (celulaAtual->prev->right == celulaAtual)
                        celulaAtual->prev->right = novo;
                    else
                        celulaAtual->prev->left = novo;
                } else {
                    tree->raiz = novo;
                }
            } else {
                if (celulaAtual != tree->raiz) {
                    if (celulaAtual->prev->right == celulaAtual)
                        celulaAtual->prev->right = novo;
                    else
                        celulaAtual->prev->left = novo;
                } else
                    tree->raiz = novo;
                novo->prev->left = novo->right;
                novo->right = celulaAtual->right;
            }
            celulaAtual->right->prev = novo;
            celulaAtual->left->prev = novo;
            novo->left = celulaAtual->left;
            novo->prev = celulaAtual->prev;
        }

        if (novo) {
            atualizaMinMaxSoCelula(novo);

            if (novo->min < MinMax[0])
                MinMax[0] = novo->min;
            else
                novo->min = MinMax[0];

            if (novo->max > MinMax[1])
                MinMax[1] = novo->max;
            else
                novo->max = MinMax[1];

            arrumaMinMaxNaRecursaoDelete(novo);

            MinMax[0] = novo->min;
            MinMax[1] = novo->max;
        }

        Balance(comparaRotacao(celulaAtual), celulaAtual, tree);

        arvore->tamanho = arvore->tamanho - 1;

        FreeLista(celulaAtual->Dados, 0);
        free(celulaAtual->Dados);
        free(celulaAtual);
    }
}

void deleteNode(Tree tree, Iten aux) {
    Arvore *arvore = tree;
    double *MinMax = calloc(2, sizeof(double));
    MinMax[0] = 999999;
    MinMax[1] = -999999;
    deleteNodeRecursive(tree, arvore->raiz, aux, MinMax);
    if (arvore->raiz)
        Balance(comparaRotacao(arvore->raiz), arvore->raiz, tree);
    free(MinMax);
}

int getBalance(Iten aux) {
    Celula *N = aux;
    if (N == NULL) return 0;
    return altura(N->left) - altura(N->right);
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

void atualizaMinMaxSoCelula(Iten node) {  //percorre a celula da avl para mudar o min e max apenas em relação a ela, sem olhar para filho direito ou esquerdo
    Celula *aux = node;

    void *atualLista = getheadLista(aux->Dados);
    aux->min = getDataX(getdataList(atualLista));
    aux->max = getDataX(getdataList(atualLista)) + getDataW(getdataList(atualLista));
    while (atualLista) {
        if (getDataX(getdataList(atualLista)) + getDataW(getdataList(atualLista)) > aux->max)
            aux->max = getDataX(getdataList(atualLista)) + getDataW(getdataList(atualLista));
        atualLista = getnextLista(atualLista);
    }
}

Posic minValueNode(Iten node) {
    Celula *current = node;

    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;

    Celula *aux = current;  //lefter
    double min = 999999;
    double max = -999999;
    while (aux != node) {  //parte de atualizar o min e max
        aux = aux->prev;

        atualizaMinMaxSoCelula(aux);

        if (aux->min < min)
            min = aux->min;
        else
            aux->min = min;

        if (aux->max > max)
            max = aux->max;
        else
            aux->max = max;
    }

    return current;
}

int comparaRotacao(Iten aux) {
    Celula *celula = aux;
    int altEsq = altura(celula->left);
    int altDir = altura(celula->right);
    if (altDir >= altEsq + 2 && altura(celula->right->left) > altura(celula->right->right)) {          //Right-Left case
        return 3;                                                                                      //C
    } else if (altEsq >= altDir + 2 && altura(celula->left->right) > altura(celula->left->left)) {     //Left-Right case
        return 4;                                                                                      //B
    } else if (altDir >= altEsq + 2 && altura(celula->right->right) >= altura(celula->right->left)) {  //Right-Right
        return 1;                                                                                      //D
    } else if (altEsq >= altDir + 2 && altura(celula->left->left) >= altura(celula->left->right)) {    //Left-Left
        return 2;                                                                                      //A
    } else {
        return 0;
    }
}

int altura(Iten CelulaAtual) {
    if (!CelulaAtual) return 0;

    return altura(AvlRight(CelulaAtual)) > altura(AvlLeft(CelulaAtual)) ? altura(AvlRight(CelulaAtual)) + 1 : altura(AvlLeft(CelulaAtual)) + 1;
}

Iten AvlRight(Iten aux) {
    Celula *celula = aux;
    if (!celula)
        return NULL;

    return celula->right;
}

Iten AvlLeft(Iten aux) {
    Celula *celula = aux;
    return celula->left;
}

int avlPrev(Iten celula) {
    Celula *aux = celula;

    if (aux->prev == NULL) {  //raiz
        return 0;
    } else if (aux == aux->prev->right) {
        return 1;
    } else if (aux == aux->prev->left) {
        return 2;
    } else {
        return -1;
    }
}

void fixMinMax(Iten celula, Tree tree) {
    if (!celula) return;

    Arvore *arvore = tree;
    Celula *p = celula;

    int verificadorMin = 0;
    int verificadorMax = 0;

    if (p->right) {
        if (p->right->min < p->min) {
            p->min = p->right->min;
            verificadorMin = 1;
        }
        if (p->right->max > p->max) {
            p->max = p->right->max;
            verificadorMax = 1;
        }
    }
    if (p->left) {
        if (p->left->min < p->min) {
            p->min = p->left->min;
            verificadorMin = 1;
        }
        if (p->left->max > p->max) {
            p->max = p->left->max;
            verificadorMax = 1;
        }
    }
    void *aux = getheadLista(p->Dados);

    if (verificadorMin == 0) {
        p->min = getDataX(getdataList(aux));
    }
    if (verificadorMax == 0) {
        p->max = getDataX(getdataList(aux)) + getDataW(getdataList(aux));
        while (aux) {
            if (getDataX(getdataList(aux)) + getDataW(getdataList(aux)) > p->max)
                p->max = getDataX(getdataList(aux)) + getDataW(getdataList(aux));
            aux = getnextLista(aux);
        }
    }
}

void rotacaoDireita(Iten celula, Tree tree) {
    if (!celula) return;

    Arvore *arvore = tree;

    Celula *p = celula;
    Celula *q, *aux;
    Celula *pai = p->prev;

    q = p->left;
    aux = q->right;
    q->right = p;
    p->left = aux;

    if (aux) {
        aux->prev = p;

        if (p->right == NULL) {
            p->max = aux->max;
            p->min = aux->min;
        } else {
            if (aux->max > p->right->max)
                p->max = aux->max;
            else
                p->max = p->right->max;

            if (aux->min < p->right->min)
                p->min = aux->min;
            else
                p->min = p->right->min;
        }
    }

    if (pai) {
        atualizaMinMaxSoCelula(pai);
        if (pai->left) {
            pai->min = pai->left->min;
            if (pai->left->max > pai->max)
                pai->max = pai->left->max;
        }

        if (pai->right) {
            if (pai->right->max > pai->max)
                pai->max = pai->right->max;
        }
    }

    if (p) {
        if (!p->right && !p->left)
            atualizaMinMaxSoCelula(p);
    }

    if (aux) {
        if (!aux->right && !aux->left)
            atualizaMinMaxSoCelula(aux);
    }

    if (avlPrev(celula) == 0) {
        arvore->raiz = q;
    } else if (avlPrev(celula) == 1) {
        p->prev->right = q;
    } else if (avlPrev(celula) == 2) {
        p->prev->left = q;
    } else {
        printf("ERRO ROTAÇÂO DIR");
    }
    q->prev = pai;
    p->prev = q;

    if (p)
        if (p->left)
            p->min = p->left->min;

    if (aux)
        if (aux->left)
            aux->min = aux->left->min;

    if (pai)
        if (pai->left)
            pai->min = pai->left->min;
}

void rotacaoEsquerda(Iten celula, Tree tree) {
    if (!celula) return;

    Arvore *arvore = tree;

    Celula *p = celula;
    Celula *q, *aux;
    Celula *pai = p->prev;

    q = p->right;
    aux = q->left;
    q->left = p;
    p->right = aux;

    if (aux) {
        aux->prev = p;

        if (p->left == NULL) {
            atualizaMinMaxSoCelula(p);
            if (p->max < aux->max)
                p->max = aux->max;
        } else {
            if (aux->max > p->left->max)
                p->max = aux->max;
            else
                p->max = p->left->max;

            p->min = p->left->min;
        }
    }

    if (pai) {
        atualizaMinMaxSoCelula(pai);
        if (pai->left) {
            pai->min = pai->left->min;
            if (pai->left->max > pai->max)
                pai->max = pai->left->max;
        }

        if (pai->right) {
            if (pai->right->max > pai->max)
                pai->max = pai->right->max;
        }
    }

    if (p) {
        if (!p->right && !p->left)
            atualizaMinMaxSoCelula(p);
    }

    if (aux) {
        if (!aux->right && !aux->left)
            atualizaMinMaxSoCelula(aux);
    }

    if (avlPrev(celula) == 0) {
        arvore->raiz = q;
    } else if (avlPrev(celula) == 1) {
        p->prev->right = q;
    } else if (avlPrev(celula) == 2) {
        p->prev->left = q;
    } else {
        printf("ERRO ROTAÇÂO LEFT");
    }
    q->prev = pai;
    p->prev = q;

    if (p)
        if (p->left)
            p->min = p->left->min;

    if (aux)
        if (aux->left)
            aux->min = aux->left->min;

    if (pai)
        if (pai->left)
            pai->min = pai->left->min;
}

//chama a função recursiva de liberar a arvore kd
void freeAvl(Tree tree) {
    Arvore *arvore = tree;
    if (!arvore->raiz) {
        return;
    }

    Celula *aux1_0 = arvore->raiz;

    freeAvlRec(aux1_0);
}

void freeAvlRec(Posic aux1_0) {
    Celula *aux = aux1_0;
    if (aux->left) {
        freeAvlRec(aux->left);
    }
    if (aux->right) {
        freeAvlRec(aux->right);
    }
    if (aux) {
        if (aux->Dados) {
            FreeLista(aux->Dados, -1);
            free(aux->Dados);
        }
        free(aux);
    }
}

void printRecursivoRec(Tree tree) {
    Arvore *arvore = tree;
    printRecursivo(arvore->raiz, 0);
}

//funcao recursiva de printar no terminal (semelhante a logica de printar no svg)
void printRecursivo(Posic galhoAtual1, int space) {
    Celula *aux = galhoAtual1;
    if (!galhoAtual1) {
        return;
    }
    space += 10;

    printRecursivo(aux->right, space);
    printf("\n");

    for (int i = 10; i < space; i++)
        printf(" ");
    void *celulaLista = getheadLista(aux->Dados);
    for (int i = 0; i < gettamanhoLista(aux->Dados); i++) {
        printf("[%s] ", getDataCep(getdataList(celulaLista)));
        celulaLista = getnextLista(celulaLista);
    }
    printf("[%.2lf] [%.2lf]", aux->min, aux->max);
    puts(" ");

    printRecursivo(aux->left, space);
}

int compareDouble(void *esquerda, void *direita) {
    double esq = getDataX(esquerda);
    double dir = getDataX(direita);
    if (esq > dir) {
        return 1;
    } else if (esq < dir) {
        return -1;
    } else {
        return 0;
    }
}

void *retornaCelulaAvlRecursivo(Tree tree, double x, Celula *aux1_0) {
    if (!aux1_0)
        return NULL;

    void *celulaLista = getheadLista(aux1_0->Dados);

    if (getDataX(getdataList(celulaLista)) < x)
        return retornaCelulaAvlRecursivo(tree, x, AvlRight(aux1_0));
    else if (getDataX(getdataList(celulaLista)) > x)
        return retornaCelulaAvlRecursivo(tree, x, AvlLeft(aux1_0));
    else if (getDataX(getdataList(celulaLista)) == x)
        return celulaLista;
}

void *retornaCelulaAvl(Tree tree, double x) {
    Arvore *arvore = tree;
    Celula *aux1_0 = arvore->raiz;

    return retornaCelulaAvlRecursivo(tree, x, aux1_0);
}

void *retornaListaAvlRecursivo(Tree tree, double x, Celula *aux1_0) {
    if (!aux1_0)
        return NULL;

    void *celulaLista = getheadLista(aux1_0->Dados);

    if (getDataX(getdataList(celulaLista)) < x)
        return retornaListaAvlRecursivo(tree, x, AvlRight(aux1_0));
    else if (getDataX(getdataList(celulaLista)) > x)
        return retornaListaAvlRecursivo(tree, x, AvlLeft(aux1_0));
    else if (getDataX(getdataList(celulaLista)) == x) {
        return aux1_0->Dados;
    }
}

void *retornaListaAvl(Tree tree, double x) {
    Arvore *arvore = tree;
    Celula *aux1_0 = arvore->raiz;

    return retornaListaAvlRecursivo(tree, x, aux1_0);
}

void imprimeSvgAvl(Tree avl, FILE *inicializaSvgSaida, Posic celulaAtual) {
    Celula *celula = celulaAtual;

    if (!celula)
        return;

    imprimeSvgAvl(avl, inicializaSvgSaida, AvlLeft(celulaAtual));
    imprimeSvgAvl(avl, inicializaSvgSaida, AvlRight(celulaAtual));

    void *celulaListaQuadra = getheadLista(getData(celula));
    while (celulaListaQuadra) {
        ImprimeRect(getDataCorC(getdataList(celulaListaQuadra)), getDataCorP(getdataList(celulaListaQuadra)), "1.0px", getDataX(getdataList(celulaListaQuadra)), getDataY(getdataList(celulaListaQuadra)), getDataW(getdataList(celulaListaQuadra)), getDataH(getdataList(celulaListaQuadra)), inicializaSvgSaida);
        celulaListaQuadra = getnextLista(celulaListaQuadra);
    }
}
