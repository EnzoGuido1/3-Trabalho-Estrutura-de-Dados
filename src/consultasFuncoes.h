#ifndef CONSULTASFUNCOES_H
#define CONSULTASFUNCOES_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "declaracoes.h"

//função correspondente a dm?, recebe como argumento um cpf, procura o cpf na hash table de pessoas, imprime os dados no txt e faz as ações necessárias no svg
void dmInterrogacao(Tree avl, Tabela quadrasHash, Tabela pessoas, char* cpf, void* Stvar, char* path4, void* listaSvg);

//função correspondente a mud, recebe como argumento um cpf e os dados de uma locação, acessa a pessoas na hash table de pessoas e muda o endereço da pessoa para essa locação, locação passa a ser locada e pessoa é também inserida na avl e hash table de quadras, faz as ações necessárias no svg
void mud(Tabela pessoas, Tabela quadrasHash, Tree avl, char* cpf, char* cep, char face, int numero, char* complexo, void* Stvar, char* path4, void* listaSvg);

//função correspondente a loc, a pessoa localizada por cpf passado no argumento aluga a locação localizada por id no argumento, mesmo procedimento da mud, faz as ações necessárias no svg
void loc(Tabela avl, Tabela pessoas, Tabela locacoes, Tabela quadrasHash, char* id, char* cpf, void* Stvar, char* path4, void* listaSvg);

//função correspondente a loc? e a dloc, caso seja loc? passa o verificadorFunção como 0, caso dloc passa o verificadorFunção como 1, função loc escreve todos os dados de uma locação passada, procura apenas na hash table de locações, na dloc o processo é o mesmo, porém a locação é removida da avl de quadras, da hash table de quadras e da hash table de locações, faz as ações necessárias no svg
void locInterrogacaoOuDloc(Tabela avl, Tabela pessoas, Tabela locacoes, Tabela quadrasHash, char* id, void* Stvar, char* path4, int verificadorFuncao, void* listaSvg);

//função correspondente a m?, recebe um cep de parametro e acessa a hash table de quadras, de acordo com esse cep retorna todos os moradores dessa quadra localizada por cep, faz as ações necessárias no svg
void mInterrogacao(Tree avl, Tabela quadrasHash, char* cep, void* Stvar, char* path4, int verificador);

//função que chama a função recursiva que corresponde a hom e mul, inicializa essa recursão com a raiz da arvore
void homOuMul(Tree avl, Tabela quadrasHash, double x, double y, double w, double h, void* Stvar, char* path4, int verificadorFuncao, void* listaSvg);

//função correspondente a hom e mul, caso hom, verificadorFunção = 0, caso mul, verificadorFunção = 1, acessa a avl e realiza uma busca de acordo com o min e o max de cada celula, todas as celulas que estão inteiramente dentro da área passada nos parametros reporta os moradores e os dados de suas moradias (homem ou mulher de acordo com o pedido), faz as alterações necessarias no svg
void homOuMulRec(Tree avl, Tabela quadrasHash, Posic celulaAtual, double x, double y, double w, double h, void* Stvar, void* qry, int verificadorFuncao, void* listaSvg);

//função correspondente a del, acessa a hash table de quadras de acordo com o cep passado, acessa o .dados dessa celula e assim acessa a avl, remove a quadra localizada por cep de ambas as estruturas, remove da lista caso tenha 2 ou mais quadras na mesma celula, remove a celula por inteiro da avl caso tenha apenas uma quadra na celula, faz as alterações necessarias no svg
void del(Tree avl, Tabela quadrasHash, char* cep, void* Stvar, char* path4, void* listaSvg);

//função que chama a função recursiva correspondete a catac, inicializa essa recursão com a raiz da arvore
void catac(Tree avl, Tabela quadrasHash, double x, double y, double w, double h, void* Stvar, char* path4, void* listaSvg);

//função correspondente a catac, percorre as celulas avl de acordo com o min e max de cada uma delas, acessa a lista de quadras de cada uma e remove as quadras da mesma maneira que a del, faz as alterações necessárias no svg
void catacRec(Tree avl, Posic celulaAtual, Tabela quadrasHash, double x, double y, double w, double h, void* Stvar, void* qry, int* verificador, void* listaSvg);

//chama a função recursiva correspondente a dmpt, inicializa a recursão com a raiz da arvore passada como argumento
void dmpt(Tree avl, char* sfx, void* Stvar, char* pathSfx);

//função correspondente a dmpt, imprime em um arquivo .dot a estrutura da arvore que posteriormente estará em formato svg, imprime o min e max de cada celula, o fator de balanceamento, a altura e 3 quadras correspondentes a essa celula
void dmptRec(Tree avl, Posic celulaAtual, char* sfx, void* Stvar, char* pathSfx, void* qry);

//função que chama a função recursiva correspondente a oloc?, iniciaza a recursão com a raiz da arvore passada como argumento
void olocInterrogacao(Tree avl, Tabela quadrasHash, double x, double y, double w, double h, void* Stvar, char* path4, void* listaSvg);

//função correspondente a oloc?, percorre a arvore de acordo com o min e max de cada celula, as celulas que estão inteiramente dentro da área são analizadas e reportado todas as locações disponíveis em cada quadra, faz as alterações necessarias no svg
void olocInterrogacaoRec(Tree avl, Tabela quadrasHash, Posic celulaAtual, double x, double y, double w, double h, void* Stvar, void* qry, void* listaSvg);

//percorre uma lista em uma posição específica da hash table passada como argumento, compara cada elemento com a função passada no argumento e retorna a celula desejada
void* PercorreLista(Tabela tabela, char* chave, char* getData(void* auxDados));

//retorna o x e y exatos para printar no svg, todas as funções que alteram no svg precisam estar exatamente na coordenada de uma quadra de acordo com o numero da mesma, portanto retorna essa posição no svg
double* calculaEndereco(Tree avl, Tabela quadrasHash, char* cep, char face, int numero);

/**/
#endif