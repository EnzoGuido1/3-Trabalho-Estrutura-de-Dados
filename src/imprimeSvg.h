#ifndef IMPRIMESVG_H
#define IMPRIMESVG_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "declaracoes.h"

//imprime um retangulo no svg de acordo como os parametros passados
void ImprimeRect(char* corc, char* corp, char* sw, double x, double y, double w, double h, void* path);

//imprime uma linha no svg de acordo como os parametros passados
void ImprimeLine(char* cor, double x1, double x2, double y1, double y2, void* path);

//imprime um circulo no svg de acordo como os parametros passados
void ImprimeCircle(double x, double y, double w, double h, double grossura, char* corc, char* corp, void* path);

/**/
#endif