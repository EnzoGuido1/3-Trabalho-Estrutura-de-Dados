CC = gcc
TS = -g -fstack-protector-all -std=c99

all: t1
	rm *.o

t1: main.o avl.o hashTable.o lista.o parametrosData.o leitura.o quadrasData.o pessoasData.o locacoesData.o consultasFuncoes.o imprimeSvg.o
	$(CC) $(TS) main.o avl.o hashTable.o lista.o parametrosData.o leitura.o quadrasData.o pessoasData.o locacoesData.o consultasFuncoes.o imprimeSvg.o -o t1 -lm

main1.o: main.c avl.h hashTable.h lista.h parametrosData.h leitura.h quadrasData.h pessoasData.h locacoesData.h consultasFuncoes.h declaracoes.h imprimeSvg.h
	$(CC) $(TS) -c main.c

avl.o: avl.c avl.h hashTable.h lista.h parametrosData.h leitura.h quadrasData.h pessoasData.h locacoesData.h consultasFuncoes.h declaracoes.h imprimeSvg.h
	$(CC) $(TS) -c avl.c

hashTable.o: hashTable.c hashTable.h avl.h lista.h parametrosData.h leitura.h quadrasData.h pessoasData.h locacoesData.h consultasFuncoes.h declaracoes.h imprimeSvg.h
	$(CC) $(TS) -c hashTable.c

lista.o: lista.c lista.h avl.h hashTable.h parametrosData.h leitura.h quadrasData.h pessoasData.h locacoesData.h consultasFuncoes.h declaracoes.h imprimeSvg.h
	$(CC) $(TS) -c lista.c

parametrosData.o: parametrosData.c parametrosData.h avl.h hashTable.h lista.h leitura.h quadrasData.h pessoasData.h locacoesData.h consultasFuncoes.h declaracoes.h imprimeSvg.h
	$(CC) $(TS) -c parametrosData.c

leitura.o: leitura.c leitura.h avl.h hashTable.h lista.h parametrosData.h quadrasData.h pessoasData.h locacoesData.h consultasFuncoes.h declaracoes.h imprimeSvg.h
	$(CC) $(TS) -c leitura.c

quadrasData.o: quadrasData.c quadrasData.h avl.h hashTable.h lista.h parametrosData.h leitura.h pessoasData.h locacoesData.h consultasFuncoes.h declaracoes.h imprimeSvg.h
	$(CC) $(TS) -c quadrasData.c

pessoasData.o: pessoasData.c pessoasData.h avl.h hashTable.h lista.h parametrosData.h leitura.h quadrasData.h locacoesData.h consultasFuncoes.h declaracoes.h imprimeSvg.h
	$(CC) $(TS) -c pessoasData.c

locacoesData.o: locacoesData.c locacoesData.h avl.h hashTable.h lista.h parametrosData.h leitura.h quadrasData.h pessoasData.h consultasFuncoes.h declaracoes.h imprimeSvg.h
	$(CC) $(TS) -c locacoesData.c

consultasFuncoes.o: consultasFuncoes.c consultasFuncoes.h avl.h hashTable.h lista.h parametrosData.h leitura.h quadrasData.h pessoasData.h locacoesData.h declaracoes.h imprimeSvg.h
	$(CC) $(TS) -c consultasFuncoes.c

imprimeSvg.o: imprimeSvg.c imprimeSvg.h avl.h hashTable.h lista.h parametrosData.h leitura.h quadrasData.h pessoasData.h locacoesData.h consultasFuncoes.h declaracoes.h
	$(CC) $(TS) -c imprimeSvg.c
