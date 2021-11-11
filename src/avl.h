#include "lista.h"

#ifndef AVL_H
#define AVL_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "declaracoes.h"

//retorna um ponteiro para o .data de uma celula avl (neste caso uma lista de quadras)
void *getData(void *Sdata);

//retorna a raiz da arvore
void *getHead(Tree tree);

//retorna o min de uma celula
double getMin(Posic celula);

//retorna o max de uma celula
double getMax(Posic celula);

//cria uma arvore de tamanho 0 e 0 celulas, retorna um ponteiro para ela, recebe um compare para comparar os x de cada celula e um free node para cada celula
Tree CriaArvore(int (*compare)(void *, void *), void (*freeNode)(void *));

//chama a função recursiva de inserir elementos na avl, inicializa a função chamada com a raiz da arvore
void InsereElementoRec(Tree tree, Iten dados);

//função recursiva de inserir elementos na avl, recebe como parametro um void* dados que serve como dados da celula, para analizar o x e inseri-la na posição correta, aumentando o tamanho da arvore, arrumando os ponteiros prev right e left e corrigindo os minimos e maximos
void InsereElemento(Tree list, Iten dados, Iten raizAtual, void *currentAux, int profundidadeGlobal);

//balanceia um nó da arvore, recebe como parametro a celula desbalanceada e realiza as rotações necessárias, altera as referencias necessarias para o pai, filho direito e filho esquerdo
void Balance(int condicional, Posic celulaDesbalanceada, Tree arvore);

//arruma os min e max de uma celula avl na volta da recursão, analisando seus filhos direito e esquerdo, não alterando referencias
void arrumaMinMaxNaRecursaoDelete(Iten aux);

//deleta um nó da arvore recursivamente, recebe como parametro um void* aux que serve como dados para procurar o x da celula a ser removido, altera as referencias necessarias para o pai, filho direito e filho esquerdo
void deleteNode(Tree tree, Iten aux);

//compara o caso específico de rotação da celula passada, se é caso left left, left right, right left ou right right
int comparaRotacao(Iten aux);

//retorna a altura de uma celula recursivamente, analisando todos os possíveis filhos direitos e esquerdos da mesma
int altura(Iten folha);

//retorna a celula a direita da celula passada como argumento, caso não exista retorna NULL
Iten AvlRight(Iten aux);

//retorna a celula a esquerda da celula passada como argumento, caso não exista retorna NULL
Iten AvlLeft(Iten aux);

//retorna se celula anterior (pai) da celula passada como argumento é pai direito retorna 1 ou pai esquerdo retorna 2, caso não tenha pai (raiz), retorna 0
int avlPrev(Iten celula);

//conserta o min e max da celula avaliando os filhos direito e esquerdo da mesma, caso tenha filho esquerdo conserta o min e max e caso tenha filho direito conserta apenas o max
void fixMinMax(Iten celula, Tree tree);

//faz uma rotação direita na celula, ajustando as referencias de ponteiro pra right left e prev necessarios
void rotacaoDireita(Iten celula, Tree tree);

//faz uma rotação esquerda na celula, ajustando as referencias de ponteiro pra right left e prev necessarios
void rotacaoEsquerda(Iten celula, Tree tree);

//retorna o balanceamento de uma celula, caso esteja balanceada retorna -1, 0 ou 1, caso esteja desbalanceada retorna qualquer outro valor, faz essa operação analizando a quantidade de filhos direitos e esquerdos de uma celula, os filhos dos filhos e assim por diante
int getBalance(Iten aux);

//retorna o maior valor entre a e b
int max(int a, int b);

//atualiza o min e maximo de uma celula apenas de uma celula, sem considerar seus filhos, de acordo com um parametro passado na celula
void atualizaMinMaxSoCelula(Iten node);

//compara o menor valor da arvore para atualizar o min e max de uma celula passada como parametro
Posic minValueNode(Iten node);

//chama a funcao recursiva inicializando com a raiz da arvore que ira liberar toda a memória alocada na arvore
void freeAvl(Tree tree);

//funcao recursiva para liberar toda a memória da arvore, começa pelas folhas e vai retornando na recursão até a raiz e por fim é liberada a memoria do ponteiro para arvore
void freeAvlRec(Posic aux1_0);

//chama a funcao recursiva inicializando com a raiz da arvore que ira printar no terminal a estrutura da arvore
void printRecursivoRec(Tree tree);

//funcao recursiva para printar no terminal toda a estrutura da arvore, começando pelos nós mais a esquerda, voltando na recursão e posteriormente indo aos filhos direitos
void printRecursivo(Posic galhoAtual1, int space);

//função de comparação entre dois valores passados (o x da arvore), que é armazenado como void*
int compareDouble(void *esquerda, void *direita);

//faz uma busca recursiva na arvore retornando a celula Avl com o respectivo x passado no argumento
void *retornaCelulaAvl(Tree tree, double x);

//faz uma busca recursiva na arvore retornando o ponteiro para dados dessa celula, no caso uma lista contendo todas as quadras que compartilham o mesmo x ancora
void *retornaListaAvl(Tree tree, double x);

//funcao recursiva que percorre toda a arvore, acessa seu ponteiro para dados e imprime de acordo com os dados no svg
void imprimeSvgAvl(Tree avl, FILE *inicializaSvgSaida, Posic celulaAtual);

/**/
#endif
