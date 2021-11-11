#ifndef LEITURA_H
#define LEITURA_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "declaracoes.h"

//concatena path1 (path de entrada) com path2 (nome do arquivo), faz as alterações necessárias (como incluir ponto ou barra)
char *concertaPath(char *path1, char *path2, int verificadorPath1);

//concatena path1 (path de saida) com path2 (nome do arquivo), faz as alterações necessárias (como incluir ponto ou barra)
char *concertaPathOutput(char *path1, char *path2);

//realiza a leitura dos parametros no argc argv e aloca tamanho exato para armazenar cada parametro
void leituraParametros(int argc, char **argv, void *Stvar);

//realiza a leitura, inicializa o svg e realiza as funções, tudo de acordo com o arquivo .geo passado anteriormente
void *leituraGeo(Tree avl, void *Stvar);

//realiza a leitura e realiza as funções, tudo de acordo com o arquivo .pm passado anteriormente
void leituraPm(Tree avl, Tabela pessoas, Tabela locacoes, Tabela quadrasHash, void *Stvar);

//realiza a leitura, inicializa o svg, o txt e realiza as funções, tudo de acordo com o arquivo .qry passado anteriormente
char *leituraQry(Tree avl, Tabela pessoas, Tabela locacoes, Tabela quadrasHash, void *listaSvg, void *Stvar);

/**/
#endif