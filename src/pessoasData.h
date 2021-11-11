#ifndef PESSOASDATA_H
#define PESSOASDATA_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "declaracoes.h"

//bloco de get, retorna o valor de um dado expecifico da struct quando chamada
//indicado no nome da função
int getDataPessoaTipoMoradia(void* Sdata);
char* getDataPessoaCpf(void* Sdata);
char* getDataPessoaNome(void* Sdata);
char* getDataPessoaSobrenome(void* Sdata);
char getDataPessoaSexo(void* Sdata);
char* getDataPessoaNascimento(void* Sdata);
void* getDataPessoaMoradia(void* Sdata);

//da calloc com espaço suficiente para todos os parametros da struct e retorna o ponteiro com esses espaços armazenados
void* callocDataPessoa(char* cpf, char* nome, char* sobrenome, char sexo, char* nascimento, void* moradia, int tipoMoradia);

//libera o espaço de uma pessoa, dando free em todos os seus dados e posteriormente em sua celula
void freeDadosPessoa(void* dados);

/**/
#endif