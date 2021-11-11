#include "leitura.h"

#include "avl.h"
#include "consultasFuncoes.h"
#include "declaracoes.h"
#include "hashTable.h"
#include "imprimeSvg.h"
#include "lista.h"
#include "locacoesData.h"
#include "parametrosData.h"
#include "pessoasData.h"
#include "quadrasData.h"

//set para os parametros passados
void setVarEntrada(void *Svar, char *Entrada);
void setVarSaida(void *Svar, char *Saida);
void setVarGeo(void *Svar, char *Geo);
void setVarQry(void *Svar, char *Qry);
void setVarPm(void *Svar, char *Pm);
void setVarEntradaVerifica(void *Svar, int cont);
void setVarSaidaVerifica(void *Svar, int cont);
void setVarGeoVerifica(void *Svar, int cont);
void setVarQryVerifica(void *Svar, int cont);
void setVarPmVerifica(void *Svar, int cont);
void setVarNx(void *Svar, int cont);

//set para as structs de dados quadras
void setDataCep(void *Sdata, char *Scep);
void setDataCorC(void *Sdata, char *ScorC);
void setDataCorP(void *Sdata, char *ScorP);
void setDataX(void *Sdata, double Sx);
void setDataY(void *Sdata, double Sy);
void setDataW(void *Sdata, double Sw);
void setDataH(void *Sdata, double Sh);
void setDataPessoasLista(void *Sdata, void *SpessoasLista);
void setDataLocacoesLista(void *Sdata, void *SlocacoesLista);
void *setDataLocacoes(Tabela locacoes, int num, int complexo, char face, char *cep, char *id, double area, double vMensais, int tipoLocacao);

//set para as structs de dados pessoas
void setDataPessoaCpf(void *Sdata, char *Scpf);
void setDataPessoaNome(void *Sdata, char *Snome);
void setDataPessoaSobrenome(void *Sdata, char *Ssobrenome);
void setDataPessoaSexo(void *Sdata, char Ssexo);
void setDataPessoaNascimento(void *Sdata, char *Snascimento);
void setDataPessoaMoradia(void *Sdata, void *moradia);
void setDataPessoaTipoMoradia(void *Sdata, int tipoMoradia);

//set para as structs de dados locacoes
void setDataNumeroLocacao(void *Sdata, int Snum);
void setDataComplexoLocacao(void *Sdata, char *Scomplexo);
void setDataFaceLocacao(void *Sdata, char Sface);
void setDataCepLocacao(void *Sdata, char *Scep);
void setDataIdLocacao(void *Sdata, char *Sid);
void setDataAreaLocacao(void *Sdata, double Sarea);
void setDatavMensaisLocacao(void *Sdata, double SvMensais);
void setDataTipoLocacao(void *Sdata, int StipoLocacao);

char *concertaPath(char *path1, char *path2, int verificadorPath1) {
    char *path;
    if (verificadorPath1 == 1) {  //faz o ajuste do path de leitura
        path = calloc(strlen(path1) + strlen(path2) + 2, sizeof(char));
        strcpy(path, path1);
        strcat(path, "/");
        strcat(path, path2);
    } else {
        path = calloc(strlen(path2) + 1, sizeof(char));
        strcpy(path, path2);
    }
    return path;
}

char *concertaPathOutput(char *path1, char *path2) {
    char *path;
    path = calloc(strlen(path1) + strlen(path2) + 2, sizeof(char));
    strcpy(path, path1);
    strcat(path, "/");
    int verificador = 0;
    for (int i = 0; i < strlen(path2); i++) {
        if (path2[i] == '/')
            verificador = 1;
    }
    char path5[500] = " ";
    int cont = 0;
    for (int j = 0; j < strlen(path2); j++) {
        if (path2[j] == '.')
            break;
        if (verificador == 0) {
            path5[cont] = path2[j];
            cont++;
        }
        if (path2[j] == '/')
            verificador = 0;
    }
    strcat(path, path5);
    return path;
}

void leituraParametros(int argc, char **argv, void *Stvar) {
    setVarEntradaVerifica(Stvar, 0);
    setVarGeoVerifica(Stvar, 0);
    setVarQryVerifica(Stvar, 0);
    setVarSaidaVerifica(Stvar, 0);
    setVarPmVerifica(Stvar, 0);

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-e")) {
            setVarEntrada(Stvar, argv[i + 1]);
            setVarEntradaVerifica(Stvar, 1);
        }
        if (!strcmp(argv[i], "-f")) {
            setVarGeo(Stvar, argv[i + 1]);
            setVarGeoVerifica(Stvar, 1);
        }
        if (!strcmp(argv[i], "-o")) {
            setVarSaida(Stvar, argv[i + 1]);
            setVarSaidaVerifica(Stvar, 1);
        }
        if (!strcmp(argv[i], "-q")) {
            setVarQry(Stvar, argv[i + 1]);
            setVarQryVerifica(Stvar, 1);
        }
        if (!strcmp(argv[i], "-pm")) {
            setVarPm(Stvar, argv[i + 1]);
            setVarPmVerifica(Stvar, 1);
        }
    }
}

void *leituraGeo(Tree avl, void *Stvar) {
    void *dados, *dados2;
    void *quadrasHash;
    int nx;
    char funcao[100], cep[100], corc[30], corp[30], sw[30];
    double x, y, w, h;  //sw == stroke width

    char *svgGeo = concertaPathOutput(getVarSaida(Stvar), getVarGeo(Stvar));
    strcat(svgGeo, ".svg");
    FILE *inicializaSvg = fopen(svgGeo, "w");
    fprintf(inicializaSvg, "<svg xmlns=\"http://www.w3.org/2000/svg\">  <!--ENZO GUIDO-->");

    char *path2 = concertaPath(getVarEntrada(Stvar), getVarGeo(Stvar), getVarEntradaVerifica(Stvar));

    FILE *geo = fopen(path2, "r");

    while (fscanf(geo, "%s", funcao) != -1) {
        if (!strcmp(funcao, "nx")) {
            fscanf(geo, "%d", &nx);
            setVarNx(Stvar, nx / 3);

            quadrasHash = criaTabela(getVarNx(Stvar));

        } else if (!strcmp(funcao, "cq")) {  //leitura comando cq
            fscanf(geo, "%s", funcao);       // seta a grossura da borda da quadra
            strcpy(sw, funcao);

            fscanf(geo, "%s", funcao);  //leitura cor de preenchimento
            if (!strcmp(funcao, "@")) {
                strcpy(corp, "none");
            } else {
                strcpy(corp, funcao);
            }

            fscanf(geo, "%s", funcao);  //leitura cor de contorno
            if (!strcmp(funcao, "@")) {
                strcpy(corc, "none");
            } else {
                strcpy(corc, funcao);
            }

        } else if (!strcmp(funcao, "q")) {
            fscanf(geo, "%s", funcao);
            strcpy(cep, funcao);

            fscanf(geo, "%lf", &x);
            fscanf(geo, "%lf", &y);
            fscanf(geo, "%lf", &w);
            fscanf(geo, "%lf", &h);

            dados = callocDataQuadra(cep, corc, corp, x, y, w, h);

            setDataPessoasLista(dados, CriaLista());
            setDataLocacoesLista(dados, CriaLista());

            InsereElementoRec(avl, dados);

            dados2 = callocDataQuadra(cep, corc, corp, x, y, w, h);

            setDataPessoasLista(dados2, NULL);
            setDataLocacoesLista(dados2, NULL);

            insereRegistro(quadrasHash, cep, dados2);

            ImprimeRect(corc, corp, sw, x, y, w, h, inicializaSvg);
        }
    }
    fprintf(inicializaSvg, "\n</svg>");

    fclose(geo);
    fclose(inicializaSvg);

    free(path2);
    free(svgGeo);

    return quadrasHash;
}

void leituraPm(Tree avl, Tabela pessoas, Tabela locacoes, Tabela quadrasHash, void *Stvar) {
    if (getVarPmVerifica(Stvar) == 0) {
        return;
    }

    void *dados, *moradia;
    int numero;
    char face, sexo;
    char complexo[100], funcao[100], id[100], cpf[100], cep[100], nome[100], sobrenome[100], nascimento[15];
    double x;

    char *path2 = concertaPath(getVarEntrada(Stvar), getVarPm(Stvar), getVarEntradaVerifica(Stvar));

    FILE *pm = fopen(path2, "r");

    while (fscanf(pm, "%s", funcao) != -1) {
        if (!strcmp(funcao, "p")) {
            fscanf(pm, "%s", funcao);
            strcpy(cpf, funcao);
            fscanf(pm, "%s", funcao);
            strcpy(nome, funcao);
            fscanf(pm, "%s", funcao);
            strcpy(sobrenome, funcao);
            fscanf(pm, "%s", &sexo);
            fscanf(pm, "%s", funcao);
            strcpy(nascimento, funcao);

            moradia = NULL;

            dados = callocDataPessoa(cpf, nome, sobrenome, sexo, nascimento, NULL, 0);
            insereRegistro(pessoas, cpf, dados);

        } else if (!strcmp(funcao, "m")) {  //leitura comando cq
            fscanf(pm, "%s", funcao);
            strcpy(cpf, funcao);
            fscanf(pm, "%s", funcao);
            strcpy(cep, funcao);
            fscanf(pm, "%s", &face);
            fscanf(pm, "%d", &numero);
            fscanf(pm, "%s", funcao);
            strcpy(complexo, funcao);

            dados = callocDataLocacoes(numero, complexo, face, cep, "NULL", -1, -1, 2, cpf);

            void *celulaPessoa = PercorreLista(pessoas, cpf, getDataPessoaCpf);

            if (celulaPessoa != NULL) {
                setDataPessoaTipoMoradia(getdataList(celulaPessoa), 2);

                setDataPessoaMoradia(getdataList(celulaPessoa), dados);

                void *celulaQuadra = PercorreLista(quadrasHash, cep, getDataCep);

                if (celulaQuadra != NULL) {
                    x = getDataX(getdataList(celulaQuadra));
                    void *celulaTree = retornaCelulaAvl(avl, x);

                    while (strcmp(getDataCep(getdataList(celulaTree)), cep)) {
                        celulaTree = getnextLista(celulaTree);
                    }

                    void *dados2 = callocDataPessoa(getDataPessoaCpf(getdataList(celulaPessoa)), getDataPessoaNome(getdataList(celulaPessoa)), getDataPessoaSobrenome(getdataList(celulaPessoa)), getDataPessoaSexo(getdataList(celulaPessoa)), getDataPessoaNascimento(getdataList(celulaPessoa)), getDataPessoaMoradia(getdataList(celulaPessoa)), 2);
                    InsereElementoLista(getDataPessoasLista(getdataList(celulaTree)), dados2);
                }

            } else {
                printf("\nFunção m cpf - %s\nPessoa com esse cpf não foi encontradra nos dados do programa\n", cpf);
                free(dados);
            }
        }
    }
    fclose(pm);

    free(path2);
}

char *leituraQry(Tree avl, Tabela pessoas, Tabela locacoes, Tabela quadrasHash, void *listaSvg, void *Stvar) {
    if (getVarQryVerifica(Stvar) == 0)
        return NULL;

    void *dados;
    char funcao[100], cpf[100], complexo[100], cep[100], id[100], face, sfx[200];
    int numero;
    double area, vMensais, x, y, w, h;

    char *path2 = concertaPath(getVarEntrada(Stvar), getVarQry(Stvar), getVarEntradaVerifica(Stvar));
    char *path3 = concertaPathOutput(getVarSaida(Stvar), getVarGeo(Stvar));
    char path4[500] = " ";  //path com o nome correto da saída do txt do qry
    strcpy(path4, path3);
    free(path3);
    strcat(path4, "-");
    path3 = getVarQry(Stvar);
    int verificador = 0;
    for (int i = 0; i < strlen(getVarQry(Stvar)); i++) {
        if (path3[i] == '/')
            verificador = 1;
    }
    char path5[500] = " ";
    int cont = 0;
    for (int j = 0; j < strlen(path3); j++) {
        if (path3[j] == '.')
            break;
        if (verificador == 0) {
            path5[cont] = path3[j];
            cont++;
        }
        if (path3[j] == '/')
            verificador = 0;
    }
    strcat(path4, path5);
    char *saidaGeo = calloc(strlen(path4) + 10, sizeof(char));
    strcpy(saidaGeo, path4);
    strcat(saidaGeo, ".svg");
    strcat(path4, ".txt");

    FILE *inicializaTxt = fopen(path4, "w");
    fprintf(inicializaTxt, "---------Enzo Guido---------\n\n");
    fclose(inicializaTxt);

    FILE *qry = fopen(path2, "r");

    while (fscanf(qry, "%s", funcao) != -1) {
        if (!strcmp(funcao, "dm?")) {
            fscanf(qry, "%s", funcao);
            strcpy(cpf, funcao);

            dmInterrogacao(avl, quadrasHash, pessoas, cpf, Stvar, path4, listaSvg);
        } else if (!strcmp(funcao, "mud")) {
            fscanf(qry, "%s", funcao);
            strcpy(cpf, funcao);
            fscanf(qry, "%s", funcao);
            strcpy(cep, funcao);
            fscanf(qry, "%s", &face);
            fscanf(qry, "%d", &numero);
            fscanf(qry, "%s", funcao);
            strcpy(complexo, funcao);

            mud(pessoas, quadrasHash, avl, cpf, cep, face, numero, complexo, Stvar, path4, listaSvg);
        } else if (!strcmp(funcao, "oloc")) {
            fscanf(qry, "%s", funcao);
            strcpy(id, funcao);
            fscanf(qry, "%s", funcao);
            strcpy(cep, funcao);
            fscanf(qry, "%s", &face);
            fscanf(qry, "%d", &numero);
            fscanf(qry, "%s", funcao);
            strcpy(complexo, funcao);
            fscanf(qry, "%lf", &area);
            fscanf(qry, "%lf", &vMensais);

            strcpy(cpf, "NULL");  //CASO FAÇA PROCURA DE PESSOAS ALUGANDO ESSA LOCAÇÃO, FAÇA STRCMP DE GETDATAINQUILINOLOCACAO COM "NULL"
                                  //SE GETDATAINQUILINOLOCACAO == "NULL" A PALAVRA NULL NÃO O VOID* NULL NÃO TEM PESSOA ALUGANDO ESSA LOCACAO

            dados = callocDataLocacoes(numero, complexo, face, cep, id, area, vMensais, 0, cpf);

            insereRegistro(locacoes, id, dados);

            void *celulaQuadra = PercorreLista(quadrasHash, cep, getDataCep);

            if (celulaQuadra != NULL) {
                // puts("passou2");
                double x = getDataX(getdataList(celulaQuadra));
                void *celulaTree = retornaCelulaAvl(avl, x);

                while (strcmp(getDataCep(getdataList(celulaTree)), cep)) {
                    celulaTree = getnextLista(celulaTree);
                }
                void *dados2 = callocDataLocacoes(numero, complexo, face, cep, id, area, vMensais, 1, "NULL");
                InsereElementoLista(getDataLocacoesLista(getdataList(celulaTree)), dados2);
            }

        } else if (!strcmp(funcao, "loc")) {
            fscanf(qry, "%s", funcao);
            strcpy(id, funcao);
            fscanf(qry, "%s", funcao);
            strcpy(cpf, funcao);

            loc(avl, pessoas, locacoes, quadrasHash, id, cpf, Stvar, path4, listaSvg);
        } else if (!strcmp(funcao, "loc?")) {
            fscanf(qry, "%s", funcao);
            strcpy(id, funcao);

            locInterrogacaoOuDloc(avl, pessoas, locacoes, quadrasHash, id, Stvar, path4, 0, listaSvg);
        } else if (!strcmp(funcao, "dloc")) {
            fscanf(qry, "%s", funcao);
            strcpy(id, funcao);

            locInterrogacaoOuDloc(avl, pessoas, locacoes, quadrasHash, id, Stvar, path4, 1, listaSvg);
        } else if (!strcmp(funcao, "m?")) {
            fscanf(qry, "%s", funcao);
            strcpy(cep, funcao);

            mInterrogacao(avl, quadrasHash, cep, Stvar, path4, 0);  //zero para verificador que a função foi chamada para pela leitura do qry na m?
        } else if (!strcmp(funcao, "hom")) {
            fscanf(qry, "%lf", &x);
            fscanf(qry, "%lf", &y);
            fscanf(qry, "%lf", &w);
            fscanf(qry, "%lf", &h);

            homOuMul(avl, quadrasHash, x, y, w, h, Stvar, path4, 0, listaSvg);
        } else if (!strcmp(funcao, "mul")) {
            fscanf(qry, "%lf", &x);
            fscanf(qry, "%lf", &y);
            fscanf(qry, "%lf", &w);
            fscanf(qry, "%lf", &h);

            homOuMul(avl, quadrasHash, x, y, w, h, Stvar, path4, 1, listaSvg);
        } else if (!strcmp(funcao, "del")) {
            fscanf(qry, "%s", funcao);
            strcpy(cep, funcao);

            del(avl, quadrasHash, cep, Stvar, path4, listaSvg);
        } else if (!strcmp(funcao, "catac")) {
            fscanf(qry, "%lf", &x);
            fscanf(qry, "%lf", &y);
            fscanf(qry, "%lf", &w);
            fscanf(qry, "%lf", &h);

            catac(avl, quadrasHash, x, y, w, h, Stvar, path4, listaSvg);
        } else if (!strcmp(funcao, "dmpt")) {
            fscanf(qry, "%s", funcao);
            strcpy(sfx, funcao);

            path3 = concertaPathOutput(getVarSaida(Stvar), getVarGeo(Stvar));
            char pathSfx[500] = " ";
            strcpy(pathSfx, path3);
            strcat(pathSfx, "-");
            strcat(pathSfx, sfx);
            strcat(pathSfx, ".dot");

            dmpt(avl, sfx, Stvar, pathSfx);

            free(path3);
        } else if (!strcmp(funcao, "oloc?")) {
            fscanf(qry, "%lf", &x);
            fscanf(qry, "%lf", &y);
            fscanf(qry, "%lf", &w);
            fscanf(qry, "%lf", &h);

            olocInterrogacao(avl, quadrasHash, x, y, w, h, Stvar, path4, listaSvg);
        }
    }
    fclose(qry);

    free(path2);

    return saidaGeo;
}
