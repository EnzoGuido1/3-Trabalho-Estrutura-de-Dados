#include "consultasFuncoes.h"

#include "avl.h"
#include "declaracoes.h"
#include "hashTable.h"
#include "imprimeSvg.h"
#include "leitura.h"
#include "lista.h"
#include "locacoesData.h"
#include "parametrosData.h"
#include "pessoasData.h"
#include "quadrasData.h"

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
void setDataInquilinoLocacao(void *Sdata, char *Sinquilino);

void dmInterrogacao(Tree avl, Tabela quadrasHash, Tabela pessoas, char *cpf, void *Stvar, char *path4, void *listaSvg) {
    void *celulaPessoa = PercorreLista(pessoas, cpf, getDataPessoaCpf);

    FILE *qry = fopen(path4, "a");

    if (celulaPessoa == NULL) {
        fprintf(qry, "Funcao dm? - cpf %s {\n\nEssa pessoa não consta nos dados do programa\n\n}\n\n", cpf);
        fclose(qry);

        return;
    } else
        fprintf(qry, "Funcao dm? - cpf %s {\n\nDados da pessoa:\ncpf: %s\tnome: %s\tsobrenome: %s\tsexo: %c\tdata de nascimento: %s\n", getDataPessoaCpf(getdataList(celulaPessoa)), getDataPessoaCpf(getdataList(celulaPessoa)), getDataPessoaNome(getdataList(celulaPessoa)), getDataPessoaSobrenome(getdataList(celulaPessoa)), getDataPessoaSexo(getdataList(celulaPessoa)), getDataPessoaNascimento(getdataList(celulaPessoa)));

    if (getDataPessoaTipoMoradia(getdataList(celulaPessoa)) == 0)
        fprintf(qry, "Dados da moradia:\npessoa não mora em lugar algum\n\n}\n\n");

    else if (getDataPessoaTipoMoradia(getdataList(celulaPessoa)) == 1)
        fprintf(qry, "Dados da moradia:\npessoa mora de aluguel no cep: %s\tface: %c\tnumero: %d\tcomplemento: %s\n\n}\n\n", getDataCepLocacao(getDataPessoaMoradia(getdataList(celulaPessoa))), getDataFaceLocacao(getDataPessoaMoradia(getdataList(celulaPessoa))), getDataNumeroLocacao(getDataPessoaMoradia(getdataList(celulaPessoa))), getDataComplexoLocacao(getDataPessoaMoradia(getdataList(celulaPessoa))));

    else if (getDataPessoaTipoMoradia(getdataList(celulaPessoa)) == 2)
        fprintf(qry, "Dados da moradia:\npessoa mora em uma casa própria no cep: %s\nface: %c\nnumero: %d\ncomplemento: %s\n\n}\n\n", getDataCepLocacao(getDataPessoaMoradia(getdataList(celulaPessoa))), getDataFaceLocacao(getDataPessoaMoradia(getdataList(celulaPessoa))), getDataNumeroLocacao(getDataPessoaMoradia(getdataList(celulaPessoa))), getDataComplexoLocacao(getDataPessoaMoradia(getdataList(celulaPessoa))));

    fclose(qry);
    if (getDataPessoaTipoMoradia(getdataList(celulaPessoa)) != 0) {
        char teste[1000];
        double *endereco = calculaEndereco(avl, quadrasHash, getDataCepLocacao(getDataPessoaMoradia(getdataList(celulaPessoa))), getDataFaceLocacao(getDataPessoaMoradia(getdataList(celulaPessoa))), getDataNumeroLocacao(getDataPessoaMoradia(getdataList(celulaPessoa))));
        sprintf(teste, "\n\t<line x1=\" %.2lf \" x2=\" %.2lf \" y1=\" %.2lf \" y2=\" %.2lf \" stroke=\" %s \" stroke-width=\"1px\" />", endereco[0], endereco[0], endereco[1], (-10.0 - endereco[1]), "blue");
        char *teste2 = calloc(strlen(teste) + 2, sizeof(char));
        strcpy(teste2, teste);
        InsereElementoLista(listaSvg, teste2);
        sprintf(teste, "\n\t<text x=\"%lf\" y=\"%lf\" font-size=\"5\">cpf - %s nome - %s cep - %s face - %c numero - %d complemento - %s</text>", endereco[0] + 1, (-10.0 - endereco[1]) + 1, getDataPessoaCpf(getdataList(celulaPessoa)), getDataPessoaNome(getdataList(celulaPessoa)), getDataCepLocacao(getDataPessoaMoradia(getdataList(celulaPessoa))), getDataFaceLocacao(getDataPessoaMoradia(getdataList(celulaPessoa))), getDataNumeroLocacao(getDataPessoaMoradia(getdataList(celulaPessoa))), getDataComplexoLocacao(getDataPessoaMoradia(getdataList(celulaPessoa))));
        teste2 = calloc(strlen(teste) + 2, sizeof(char));
        strcpy(teste2, teste);
        InsereElementoLista(listaSvg, teste2);
        free(endereco);
    }
}

void mud(Tabela pessoas, Tabela quadrasHash, Tree avl, char *cpf, char *cep, char face, int numero, char *complexo, void *Stvar, char *path4, void *listaSvg) {
    void *celulaPessoa = PercorreLista(pessoas, cpf, getDataPessoaCpf);

    double *enderecoA;
    double *enderecoB;

    FILE *qry = fopen(path4, "a");

    if (celulaPessoa == NULL) {
        fprintf(qry, "Funcao mud - cpf %s cep %s face %c numero %d complemento %s {\n\nEssa pessoa não consta nos dados do programa\n\n}\n\n", cpf, cep, face, numero, complexo);

        fclose(qry);
        return;
    } else
        fprintf(qry, "Funcao mud - cpf %s cep %s face %c numero %d complemento %s {\n\nDados da pessoa:\ncpf: %s\tnome: %s\tsobrenome: %s\tsexo: %c\tdata de nascimento: %s\n", getDataPessoaCpf(getdataList(celulaPessoa)), cep, face, numero, complexo, getDataPessoaCpf(getdataList(celulaPessoa)), getDataPessoaNome(getdataList(celulaPessoa)), getDataPessoaSobrenome(getdataList(celulaPessoa)), getDataPessoaSexo(getdataList(celulaPessoa)), getDataPessoaNascimento(getdataList(celulaPessoa)));

    if (getDataPessoaTipoMoradia(getdataList(celulaPessoa)) == 0)
        fprintf(qry, "Dados da antiga moradia:\npessoa não morava em lugar algum\n");
    else if (getDataPessoaTipoMoradia(getdataList(celulaPessoa)) == 1)
        fprintf(qry, "Dados da antiga moradia:\npessoa morava de aluguel no cep: %s\tface: %c\tnumero: %d\tcomplemento: %s\n", getDataCepLocacao(getDataPessoaMoradia(getdataList(celulaPessoa))), getDataFaceLocacao(getDataPessoaMoradia(getdataList(celulaPessoa))), getDataNumeroLocacao(getDataPessoaMoradia(getdataList(celulaPessoa))), getDataComplexoLocacao(getDataPessoaMoradia(getdataList(celulaPessoa))));
    else if (getDataPessoaTipoMoradia(getdataList(celulaPessoa)) == 2)
        fprintf(qry, "Dados da antiga moradia:\npessoa morava em uma casa própria no cep: %s\tface: %c\tnumero: %d\tcomplemento: %s\n", getDataCepLocacao(getDataPessoaMoradia(getdataList(celulaPessoa))), getDataFaceLocacao(getDataPessoaMoradia(getdataList(celulaPessoa))), getDataNumeroLocacao(getDataPessoaMoradia(getdataList(celulaPessoa))), getDataComplexoLocacao(getDataPessoaMoradia(getdataList(celulaPessoa))));

    int verificadorSvg = getDataPessoaTipoMoradia(getdataList(celulaPessoa));

    if (getDataPessoaTipoMoradia(getdataList(celulaPessoa)) == 0) {
        void *dados = callocDataLocacoes(numero, complexo, face, cep, "NULL", -1, -1, 2, cpf);
        setDataPessoaTipoMoradia(getdataList(celulaPessoa), 2);
        setDataPessoaMoradia(getdataList(celulaPessoa), dados);
    } else {  //endereço do print do svg
        enderecoA = calculaEndereco(avl, quadrasHash, getDataCepLocacao(getDataPessoaMoradia(getdataList(celulaPessoa))), getDataFaceLocacao(getDataPessoaMoradia(getdataList(celulaPessoa))), getDataNumeroLocacao(getDataPessoaMoradia(getdataList(celulaPessoa))));
    }

    setDataCepLocacao(getDataPessoaMoradia(getdataList(celulaPessoa)), cep);
    setDataFaceLocacao(getDataPessoaMoradia(getdataList(celulaPessoa)), face);
    setDataNumeroLocacao(getDataPessoaMoradia(getdataList(celulaPessoa)), numero);
    setDataComplexoLocacao(getDataPessoaMoradia(getdataList(celulaPessoa)), complexo);

    fprintf(qry, "Dados da nova moradia:\npessoa passa a morar no cep: %s\tface: %c\tnumero: %d\tcomplemento: %s\n\n}\n\n", getDataCepLocacao(getDataPessoaMoradia(getdataList(celulaPessoa))), getDataFaceLocacao(getDataPessoaMoradia(getdataList(celulaPessoa))), getDataNumeroLocacao(getDataPessoaMoradia(getdataList(celulaPessoa))), getDataComplexoLocacao(getDataPessoaMoradia(getdataList(celulaPessoa))));

    if (verificadorSvg == 0) {
        enderecoA = calloc(2, sizeof(double));
        enderecoA[0] = enderecoB[0];
        enderecoA[1] = enderecoB[1];
    }
    char teste[1000];
    enderecoB = calculaEndereco(avl, quadrasHash, getDataCepLocacao(getDataPessoaMoradia(getdataList(celulaPessoa))), getDataFaceLocacao(getDataPessoaMoradia(getdataList(celulaPessoa))), getDataNumeroLocacao(getDataPessoaMoradia(getdataList(celulaPessoa))));
    sprintf(teste, "\n\t<line x1=\" %.2lf \" x2=\" %.2lf \" y1=\" %.2lf \" y2=\" %.2lf \" stroke=\" %s \" stroke-width=\"3px\" />", enderecoA[0], enderecoB[0], enderecoA[1], enderecoB[1], "red");
    char *teste2 = calloc(strlen(teste) + 2, sizeof(char));
    strcpy(teste2, teste);
    InsereElementoLista(listaSvg, teste2);
    sprintf(teste, "\n\t<circle cx=\"%.2lf\" cy=\"%.2lf\" r=\"4\" stroke=\"white\" stroke-width=\"2\" fill=\"red\" opacity=\"1\"/>", enderecoA[0], enderecoA[1]);
    teste2 = calloc(strlen(teste) + 2, sizeof(char));
    strcpy(teste2, teste);
    InsereElementoLista(listaSvg, teste2);
    sprintf(teste, "\n\t<circle cx=\"%.2lf\" cy=\"%.2lf\" r=\"4\" stroke=\"white\" stroke-width=\"2\" fill=\"blue\" opacity=\"1\"/>", enderecoB[0], enderecoB[1]);
    teste2 = calloc(strlen(teste) + 2, sizeof(char));
    strcpy(teste2, teste);
    InsereElementoLista(listaSvg, teste2);
    free(enderecoA);
    free(enderecoB);

    fclose(qry);
}

//achar o cep da locação com base no id buscando na hash table de locações, acha o cep da locação
//busca na hash table de quadras, acha o x, busca na avl de quadras, da calloc em dados e em seguida adiciona
//a pessoa na lista de pessoas da quadra
void loc(Tabela avl, Tabela pessoas, Tabela locacoes, Tabela quadrasHash, char *id, char *cpf, void *Stvar, char *path4, void *listaSvg) {
    void *celulaPessoa = PercorreLista(pessoas, cpf, getDataPessoaCpf);

    FILE *qry = fopen(path4, "a");

    if (celulaPessoa == NULL) {
        fprintf(qry, "Funcao loc - id %s cpf %s {\n\nEssa pessoa não consta nos dados do programa\n\n}\n\n", id, cpf);

        fclose(qry);
        return;
    }

    void *celulaLocacao = PercorreLista(locacoes, id, getDataIdLocacao);

    if (celulaLocacao == NULL) {
        fprintf(qry, "Funcao loc - id %s cpf %s {\n\nEssa locação não consta nos dados do programa\n\n}\n\n", id, cpf);

        fclose(qry);
        return;
    } else if (getDataTipoLocacao(getdataList(celulaLocacao)) == -1) {
        fprintf(qry, "Funcao loc - id %s cpf %s {\n\nUm locatário ja encerrou essa locação, portanto a oferta foi removida\n\n}\n\n", id, cpf);

        fclose(qry);
        return;
    }
    fprintf(qry, "Funcao loc - id %s cpf %s {\n\nDados da pessoa:\ncpf: %s\tnome: %s\tsobrenome: %s\tsexo: %c\tdata de nascimento: %s\n", id, cpf, getDataPessoaCpf(getdataList(celulaPessoa)), getDataPessoaNome(getdataList(celulaPessoa)), getDataPessoaSobrenome(getdataList(celulaPessoa)), getDataPessoaSexo(getdataList(celulaPessoa)), getDataPessoaNascimento(getdataList(celulaPessoa)));

    if (getDataPessoaTipoMoradia(getdataList(celulaPessoa)) == 0)
        fprintf(qry, "Dados da antiga moradia:\npessoa não morava em lugar algum\n");
    else {
        fprintf(qry, "Dados da antiga moradia:\npessoa morava no cep: %s\tface: %c\tnumero: %d\tcomplemento: %s\n", getDataCepLocacao(getDataPessoaMoradia(getdataList(celulaPessoa))), getDataFaceLocacao(getDataPessoaMoradia(getdataList(celulaPessoa))), getDataNumeroLocacao(getDataPessoaMoradia(getdataList(celulaPessoa))), getDataComplexoLocacao(getDataPessoaMoradia(getdataList(celulaPessoa))));

        char *delete = getDataPessoaCpf(getdataList(celulaPessoa));

        void *quadraPessoaDelete = PercorreLista(quadrasHash, getDataCepLocacao(getDataPessoaMoradia(getdataList(celulaPessoa))), getDataCep);

        double deletex = getDataX(getdataList(quadraPessoaDelete));
        void *celulaTreeDelete = retornaCelulaAvl(avl, deletex);
        while (strcmp(getDataCep(getdataList(celulaTreeDelete)), getDataCepLocacao(getDataPessoaMoradia(getdataList(celulaPessoa))))) {
            celulaTreeDelete = getnextLista(celulaTreeDelete);
        }
        RemoveCelulaListaPorData(getDataPessoasLista(getdataList(celulaTreeDelete)), getDataPessoaCpf(getdataList(celulaPessoa)), getDataPessoaCpf);
    }
    //o ponteiro que existe dentro da celula Pessoa para a referencia da sua moradia, ou seja
    //a struct de celula Locacao que ela armazena, muda seus dados
    //portanto de acordo com o id de locação passado, eu acesso a celula Locacao deste id, pego seus dados
    //e faço com que o ponteiro da celula pessoa que contém os dados da sua moradia mudem para os dados da sua nova locação
    //isso tudo dentro da hash table pessoas (pessoas.moradia) moradia = void* que recebe um tipo locações*, com os dados de sua moradia
    if (!getDataPessoaMoradia(getdataList(celulaPessoa))) {
        void *dados = callocDataLocacoes(getDataNumeroLocacao(getdataList(celulaLocacao)), getDataComplexoLocacao(getdataList(celulaLocacao)), getDataFaceLocacao(getdataList(celulaLocacao)), getDataCepLocacao(getdataList(celulaLocacao)), getDataIdLocacao(getdataList(celulaLocacao)), getDataAreaLocacao(getdataList(celulaLocacao)), getDatavMensaisLocacao(getdataList(celulaLocacao)), 1, cpf);
        setDataPessoaMoradia(getdataList(celulaPessoa), dados);
    } else {
        setDataTipoLocacao(getDataPessoaMoradia(getdataList(celulaPessoa)), 1);
        setDataIdLocacao(getDataPessoaMoradia(getdataList(celulaPessoa)), getDataIdLocacao(getdataList(celulaLocacao)));
        setDataCepLocacao(getDataPessoaMoradia(getdataList(celulaPessoa)), getDataCepLocacao(getdataList(celulaLocacao)));
        setDataFaceLocacao(getDataPessoaMoradia(getdataList(celulaPessoa)), getDataFaceLocacao(getdataList(celulaLocacao)));
        setDataNumeroLocacao(getDataPessoaMoradia(getdataList(celulaPessoa)), getDataNumeroLocacao(getdataList(celulaLocacao)));
        setDataComplexoLocacao(getDataPessoaMoradia(getdataList(celulaPessoa)), getDataComplexoLocacao(getdataList(celulaLocacao)));
        setDataAreaLocacao(getDataPessoaMoradia(getdataList(celulaPessoa)), getDataAreaLocacao(getdataList(celulaLocacao)));
        setDatavMensaisLocacao(getDataPessoaMoradia(getdataList(celulaPessoa)), getDatavMensaisLocacao(getdataList(celulaLocacao)));
    }

    setDataTipoLocacao(getdataList(celulaLocacao), 1);  //seta a locação do id passado para 1 (alugado), na hash table locações
    setDataInquilinoLocacao(getdataList(celulaLocacao), cpf);
    setDataPessoaTipoMoradia(getdataList(celulaPessoa), 1);

    fprintf(qry, "Dados da nova moradia:\npessoa passa a morar no cep: %s\tface: %c\tnumero: %d\tcomplemento: %s\n\n}\n\n", getDataCepLocacao(getDataPessoaMoradia(getdataList(celulaPessoa))), getDataFaceLocacao(getDataPessoaMoradia(getdataList(celulaPessoa))), getDataNumeroLocacao(getDataPessoaMoradia(getdataList(celulaPessoa))), getDataComplexoLocacao(getDataPessoaMoradia(getdataList(celulaPessoa))));

    char teste[1000];
    double *endereco = calculaEndereco(avl, quadrasHash, getDataCepLocacao(getDataPessoaMoradia(getdataList(celulaPessoa))), getDataFaceLocacao(getDataPessoaMoradia(getdataList(celulaPessoa))), getDataNumeroLocacao(getDataPessoaMoradia(getdataList(celulaPessoa))));
    sprintf(teste, "\n\t<line x1=\" %.2lf \" x2=\" %.2lf \" y1=\" %.2lf \" y2=\" %.2lf \" stroke=\" %s \" stroke-width=\"1px\" />", endereco[0], endereco[0], endereco[1], (-10.0 - endereco[1]), "yellow");
    char *teste2 = calloc(strlen(teste) + 2, sizeof(char));
    strcpy(teste2, teste);
    InsereElementoLista(listaSvg, teste2);
    sprintf(teste, "\n\t<text x=\"%lf\" y=\"%lf\" font-size=\"5\">cpf - %s nome - %s cep - %s face - %c numero - %d complemento - %s</text>", endereco[0] + 1, (-10.0 - endereco[1]) + 1, getDataPessoaCpf(getdataList(celulaPessoa)), getDataPessoaNome(getdataList(celulaPessoa)), getDataCepLocacao(getDataPessoaMoradia(getdataList(celulaPessoa))), getDataFaceLocacao(getDataPessoaMoradia(getdataList(celulaPessoa))), getDataNumeroLocacao(getDataPessoaMoradia(getdataList(celulaPessoa))), getDataComplexoLocacao(getDataPessoaMoradia(getdataList(celulaPessoa))));
    teste2 = calloc(strlen(teste) + 2, sizeof(char));
    strcpy(teste2, teste);
    InsereElementoLista(listaSvg, teste2);
    free(endereco);

    void *celulaQuadra = PercorreLista(quadrasHash, getDataCepLocacao(getDataPessoaMoradia(getdataList(celulaPessoa))), getDataCep);

    if (celulaQuadra != NULL) {
        double x = getDataX(getdataList(celulaQuadra));
        void *celulaTree = retornaCelulaAvl(avl, x);

        while (strcmp(getDataCep(getdataList(celulaTree)), getDataCepLocacao(getDataPessoaMoradia(getdataList(celulaPessoa))))) {
            celulaTree = getnextLista(celulaTree);
        }
        void *dados2 = callocDataPessoa(getDataPessoaCpf(getdataList(celulaPessoa)), getDataPessoaNome(getdataList(celulaPessoa)), getDataPessoaSobrenome(getdataList(celulaPessoa)), getDataPessoaSexo(getdataList(celulaPessoa)), getDataPessoaNascimento(getdataList(celulaPessoa)), getDataPessoaMoradia(getdataList(celulaPessoa)), 1);
        InsereElementoLista(getDataPessoasLista(getdataList(celulaTree)), dados2);
        RemoveCelulaListaPorData(getDataLocacoesLista(getdataList(celulaTree)), getDataCepLocacao(getdataList(celulaLocacao)), getDataCepLocacao);  //como a locação foi comprada pela pessoa acima, remove os dados da locação sem dono na lista de locacoes da arvore avl
    }

    fclose(qry);
}

//essa função compartilha a exata mesma estrutura da dloc, portanto a dloc será feita aqui também
//com a diferença de que a loc? passa um verificadorFuncao, caso a função desejada seja a loc?
//verificadorFuncao == 0; caso a função desejada seja dloc verificadorFuncao == 1;
//e caso a função desejada seja a dloc, getDataTipoLocação = -1;
void locInterrogacaoOuDloc(Tabela avl, Tabela pessoas, Tabela locacoes, Tabela quadrasHash, char *id, void *Stvar, char *path4, int verificadorFuncao, void *listaSvg) {
    void *celulaLocacao = PercorreLista(locacoes, id, getDataIdLocacao);

    FILE *qry = fopen(path4, "a");

    if (celulaLocacao == NULL) {
        if (verificadorFuncao == 0)
            fprintf(qry, "Funcao loc?");
        else if (verificadorFuncao == 1)
            fprintf(qry, "Funcao dloc");
        fprintf(qry, " - id %s {\n\nEssa locação não consta nos dados do programa\n\n}\n\n", id);

        fclose(qry);
        return;
    }

    if (getDataTipoLocacao(getdataList(celulaLocacao)) == -1) {
        if (verificadorFuncao == 0) {
            fprintf(qry, "Funcao loc?");
        } else if (verificadorFuncao == 1)
            fprintf(qry, "Funcao dloc");
        fprintf(qry, " - id %s {\n\nUm locatário ja encerrou essa locação, portanto a oferta foi removida\n\n}\n\n", id);

        char teste[1000];
        double *endereco = calculaEndereco(avl, quadrasHash, getDataCepLocacao(getdataList(celulaLocacao)), getDataFaceLocacao(getdataList(celulaLocacao)), getDataNumeroLocacao(getdataList(celulaLocacao)));
        sprintf(teste, "\n\t<text x=\"%lf\" y=\"%lf\" font-size=\"5\">#</text>", endereco[0], endereco[1]);
        void *teste2 = calloc(strlen(teste) + 2, sizeof(char));
        strcpy(teste2, teste);
        InsereElementoLista(listaSvg, teste2);
        free(endereco);

        fclose(qry);
        return;
    }

    if (verificadorFuncao == 0)
        fprintf(qry, "Funcao loc?");
    else if (verificadorFuncao == 1)
        fprintf(qry, "Funcao dloc");
    fprintf(qry, " - id %s {\n\nDados da moradia:\ncep: %s\tface: %c\tnumero: %d\tcomplemento: %s\tarea: %2.lf\tvalor mensal: %.2lf\n", id, getDataCepLocacao(getdataList(celulaLocacao)), getDataFaceLocacao(getdataList(celulaLocacao)), getDataNumeroLocacao(getdataList(celulaLocacao)), getDataComplexoLocacao(getdataList(celulaLocacao)), getDataAreaLocacao(getdataList(celulaLocacao)), getDatavMensaisLocacao(getdataList(celulaLocacao)));

    void *celulaPessoa = PercorreLista(pessoas, getDataInquilinoLocacao(getdataList(celulaLocacao)), getDataPessoaCpf);

    int verificador = 0;  //verificador para ver se alguem aluga a locação, caso sim, eu seto o tipo locacao dessa moradia como -1 e o tipo moradia da pessoa como 0, depois deleto a locação da lista de locações da avl

    if (getDataTipoLocacao(getdataList(celulaLocacao)) != 0) {
        if (verificadorFuncao == 1)
            fprintf(qry, "Dados da pessoa encerrando a locação da moradia id %s:\ncpf: %s\tnome: %s\tsobrenome: %s\tsexo: %c\tdata de nascimento: %s\n\n}\n\n", id, getDataPessoaCpf(getdataList(celulaPessoa)), getDataPessoaNome(getdataList(celulaPessoa)), getDataPessoaSobrenome(getdataList(celulaPessoa)), getDataPessoaSexo(getdataList(celulaPessoa)), getDataPessoaNascimento(getdataList(celulaPessoa)));
        else if (verificadorFuncao == 0)
            fprintf(qry, "Dados da pessoa alugando a locação da moradia id %s:\ncpf: %s\tnome: %s\tsobrenome: %s\tsexo: %c\tdata de nascimento: %s\n\n}\n\n", id, getDataPessoaCpf(getdataList(celulaPessoa)), getDataPessoaNome(getdataList(celulaPessoa)), getDataPessoaSobrenome(getdataList(celulaPessoa)), getDataPessoaSexo(getdataList(celulaPessoa)), getDataPessoaNascimento(getdataList(celulaPessoa)));

        char teste[1000];
        double *endereco = calculaEndereco(avl, quadrasHash, getDataCepLocacao(getdataList(celulaLocacao)), getDataFaceLocacao(getdataList(celulaLocacao)), getDataNumeroLocacao(getdataList(celulaLocacao)));
        sprintf(teste, "\n\t<text x=\"%lf\" y=\"%lf\" font-size=\"5\">*</text>", endereco[0], endereco[1]);
        void *teste2 = calloc(strlen(teste) + 2, sizeof(char));
        strcpy(teste2, teste);
        InsereElementoLista(listaSvg, teste2);
        free(endereco);
        verificador = 1;
    } else {
        fprintf(qry, "Essa locação não está sendo alugada por ninguém\n\n}\n\n");
        char teste[1000];
        double *endereco = calculaEndereco(avl, quadrasHash, getDataCepLocacao(getdataList(celulaLocacao)), getDataFaceLocacao(getdataList(celulaLocacao)), getDataNumeroLocacao(getdataList(celulaLocacao)));
        sprintf(teste, "\n\t<text x=\"%lf\" y=\"%lf\" font-size=\"5\">$</text>", endereco[0], endereco[1]);
        void *teste2 = calloc(strlen(teste) + 2, sizeof(char));
        strcpy(teste2, teste);
        InsereElementoLista(listaSvg, teste2);
        free(endereco);
    }
    if (verificadorFuncao == 1) {
        setDataTipoLocacao(getdataList(celulaLocacao), -1);

        if (getDataTipoLocacao(getdataList(celulaLocacao)) != 0 && verificador == 1) {
            setDataPessoaTipoMoradia(getdataList(celulaPessoa), 0);
            void *celulaQuadra = PercorreLista(quadrasHash, getDataCepLocacao(getdataList(celulaLocacao)), getDataCep);

            if (celulaQuadra != NULL) {
                double x = getDataX(getdataList(celulaQuadra));
                void *celulaTree = retornaCelulaAvl(avl, x);

                while (strcmp(getDataCep(getdataList(celulaTree)), getDataCepLocacao(getdataList(celulaLocacao))))
                    celulaTree = getnextLista(celulaTree);

                RemoveCelulaListaPorData(getDataPessoasLista(getdataList(celulaTree)), getDataPessoaCpf(getdataList(celulaPessoa)), getDataPessoaCpf);
            }
        }
    }

    fclose(qry);
}

void mInterrogacao(Tree avl, Tabela quadrasHash, char *cep, void *Stvar, char *path4, int verificador) {
    void *celulaQuadra = PercorreLista(quadrasHash, cep, getDataCep);

    FILE *qry = fopen(path4, "a");

    if (celulaQuadra == NULL) {
        if (verificador == 0)
            fprintf(qry, "Função m? - cep %s {\n\nEssa quadra não consta nos dados do programa\n\n}\n\n", cep);
        else if (verificador == 1)
            fprintf(qry, "Função del - cep %s {\n\nEssa quadra não consta nos dados do programa\n\n}\n\n", cep);

        fclose(qry);
        return;

    } else {
        double x = getDataX(getdataList(celulaQuadra));
        void *celulaTree = retornaCelulaAvl(avl, x);

        while (strcmp(getDataCep(getdataList(celulaTree)), cep)) {
            celulaTree = getnextLista(celulaTree);
        }

        void *listaPessoasQuadra = getDataPessoasLista(getdataList(celulaTree));
        void *listaLocacoesQuadra = getDataLocacoesLista(getdataList(celulaTree));
        if (!getheadLista(listaPessoasQuadra)) {
            if (verificador == 1) {
                if (!getheadLista(listaLocacoesQuadra)) {
                    fprintf(qry, "Função del - cep %s {\n\nEssa quadra não contém moradores nem locações\n\n}\n\n", cep);

                    fclose(qry);
                    return;
                }
            } else {
                fprintf(qry, "Função m? - cep %s {\n\nEssa quadra não contém moradores\n\n}\n\n", cep);

                fclose(qry);
                return;
            }
        }

        void *celulaPessoaQuadra = getheadLista(listaPessoasQuadra);
        void *celulaLocacaoQuadra = getheadLista(listaLocacoesQuadra);
        if (verificador == 0)
            fprintf(qry, "Função m? - cep %s {\n\n", cep);
        else if (verificador == 1)
            fprintf(qry, "Função del - cep %s {\n\n", cep);

        while (celulaPessoaQuadra) {
            fprintf(qry, "Dados do morador:\ncpf: %s\tnome: %s\tsobrenome: %s\tsexo: %c\tdata de nascimento: %s\n", getDataPessoaCpf(getdataList(celulaPessoaQuadra)), getDataPessoaNome(getdataList(celulaPessoaQuadra)), getDataPessoaSobrenome(getdataList(celulaPessoaQuadra)), getDataPessoaSexo(getdataList(celulaPessoaQuadra)), getDataPessoaNascimento(getdataList(celulaPessoaQuadra)));

            if (getDataPessoaTipoMoradia(getdataList(celulaPessoaQuadra)) != 0) {
                void *celulaMoradiaQuadra = getDataPessoaMoradia(getdataList(celulaPessoaQuadra));

                if (getDataPessoaTipoMoradia(getdataList(celulaPessoaQuadra)) == 1)
                    fprintf(qry, "Dados de sua moradia:\nid: %s\tcep: %s\tface: %c\tnumero: %d\tcomplemento: %s\tarea: %2.lf\tvalor mensal: %.2lf", getDataIdLocacao(celulaMoradiaQuadra), getDataCepLocacao(celulaMoradiaQuadra), getDataFaceLocacao(celulaMoradiaQuadra), getDataNumeroLocacao(celulaMoradiaQuadra), getDataComplexoLocacao(celulaMoradiaQuadra), getDataAreaLocacao(celulaMoradiaQuadra), getDatavMensaisLocacao(celulaMoradiaQuadra));

                else if (getDataPessoaTipoMoradia(getdataList(celulaPessoaQuadra)) == 2)
                    fprintf(qry, "Dados de sua moradia:\ncep: %s\tface: %c\tnumero: %d\tcomplemento: %s", getDataCepLocacao(celulaMoradiaQuadra), getDataFaceLocacao(celulaMoradiaQuadra), getDataNumeroLocacao(celulaMoradiaQuadra), getDataComplexoLocacao(celulaMoradiaQuadra));
            }

            fprintf(qry, "\n\n");
            celulaPessoaQuadra = getnextLista(celulaPessoaQuadra);
        }

        if (verificador == 1) {
            while (celulaLocacaoQuadra) {
                fprintf(qry, "Dados de uma locação (sem morador):\nid: %s\tcep: %s\tface: %c\tnumero: %d\tcomplemento: %s\tarea: %.2lf\tvalor mensal: %.2lf\n\n", getDataIdLocacao(getdataList(celulaLocacaoQuadra)), getDataCepLocacao(getdataList(celulaLocacaoQuadra)), getDataFaceLocacao(getdataList(celulaLocacaoQuadra)), getDataNumeroLocacao(getdataList(celulaLocacaoQuadra)), getDataComplexoLocacao(getdataList(celulaLocacaoQuadra)), getDataAreaLocacao(getdataList(celulaLocacaoQuadra)), getDatavMensaisLocacao(getdataList(celulaLocacaoQuadra)));
                celulaLocacaoQuadra = getnextLista(celulaLocacaoQuadra);
            }
        }

        fprintf(qry, "}\n\n");
    }

    fclose(qry);
}

void homOuMul(Tree avl, Tabela quadrasHash, double x, double y, double w, double h, void *Stvar, char *path4, int verificadorFuncao, void *listaSvg) {
    void *celulaAvl = getHead(avl);
    FILE *qry = fopen(path4, "a");

    if (verificadorFuncao == 0) {
        fprintf(qry, "Função hom - x %.2lf y %.2lf w %.2lf h %.2lf  {\n\n", x, y, w, h);
    } else if (verificadorFuncao == 1) {
        fprintf(qry, "Função mul - x %.2lf y %.2lf w %.2lf h %.2lf  {\n\n", x, y, w, h);
    }

    homOuMulRec(avl, quadrasHash, celulaAvl, x, y, w, h, Stvar, qry, verificadorFuncao, listaSvg);

    fprintf(qry, "}\n\n");
    fclose(qry);
}

void homOuMulRec(Tree avl, Tabela quadrasHash, Posic celulaAtual, double x, double y, double w, double h, void *Stvar, void *qry, int verificadorFuncao, void *listaSvg) {
    if (!celulaAtual) {
        return;
    }

    void *celulaAvl = celulaAtual;
    if (getMin(celulaAvl) <= x + w && getMax(celulaAvl) >= x) {
        // puts("passou");
        homOuMulRec(avl, quadrasHash, AvlLeft(celulaAvl), x, y, w, h, Stvar, qry, verificadorFuncao, listaSvg);
        homOuMulRec(avl, quadrasHash, AvlRight(celulaAvl), x, y, w, h, Stvar, qry, verificadorFuncao, listaSvg);
    }

    void *celulaListaQuadra = getheadLista(getData(celulaAvl));
    while (celulaListaQuadra) {
        if (getDataX(getdataList(celulaListaQuadra)) >= x && getDataX(getdataList(celulaListaQuadra)) + getDataW(getdataList(celulaListaQuadra)) <= x + w) {
            if (getDataY(getdataList(celulaListaQuadra)) >= y && getDataY(getdataList(celulaListaQuadra)) + getDataH(getdataList(celulaListaQuadra)) <= y + h) {
                void *listaPessoasQuadra = getDataPessoasLista(getdataList(celulaListaQuadra));
                void *celulaPessoaQuadra = getheadLista(listaPessoasQuadra);
                while (celulaPessoaQuadra) {
                    if (verificadorFuncao == 0) {
                        if (getDataPessoaSexo(getdataList(celulaPessoaQuadra)) == 'M') {
                            fprintf(qry, "Dados do morador:\ncpf: %s\tnome: %s\tsobrenome: %s\tsexo: %c\tdata de nascimento: %s\n", getDataPessoaCpf(getdataList(celulaPessoaQuadra)), getDataPessoaNome(getdataList(celulaPessoaQuadra)), getDataPessoaSobrenome(getdataList(celulaPessoaQuadra)), getDataPessoaSexo(getdataList(celulaPessoaQuadra)), getDataPessoaNascimento(getdataList(celulaPessoaQuadra)));
                            if (getDataPessoaTipoMoradia(getdataList(celulaPessoaQuadra)) == 0)
                                fprintf(qry, "Dados da moradia: pessoa não mora em lugar algum\n");

                            else if (getDataPessoaTipoMoradia(getdataList(celulaPessoaQuadra)) == 1)
                                fprintf(qry, "Dados da moradia:\npessoa mora de aluguel no cep: %s\tface: %c\tnumero: %d\tcomplemento: %s\n", getDataCepLocacao(getDataPessoaMoradia(getdataList(celulaPessoaQuadra))), getDataFaceLocacao(getDataPessoaMoradia(getdataList(celulaPessoaQuadra))), getDataNumeroLocacao(getDataPessoaMoradia(getdataList(celulaPessoaQuadra))), getDataComplexoLocacao(getDataPessoaMoradia(getdataList(celulaPessoaQuadra))));

                            else if (getDataPessoaTipoMoradia(getdataList(celulaPessoaQuadra)) == 2)
                                fprintf(qry, "Dados da moradia:\npessoa mora em uma casa própria no cep: %s\tface: %c\tnumero: %d\tcomplemento: %s\n", getDataCepLocacao(getDataPessoaMoradia(getdataList(celulaPessoaQuadra))), getDataFaceLocacao(getDataPessoaMoradia(getdataList(celulaPessoaQuadra))), getDataNumeroLocacao(getDataPessoaMoradia(getdataList(celulaPessoaQuadra))), getDataComplexoLocacao(getDataPessoaMoradia(getdataList(celulaPessoaQuadra))));
                            fprintf(qry, "\n");

                            if (getDataPessoaTipoMoradia(getdataList(celulaPessoaQuadra)) != 0) {
                                char teste[1000];
                                double *endereco = calculaEndereco(avl, quadrasHash, getDataCepLocacao(getDataPessoaMoradia(getdataList(celulaPessoaQuadra))), getDataFaceLocacao(getDataPessoaMoradia(getdataList(celulaPessoaQuadra))), getDataNumeroLocacao(getDataPessoaMoradia(getdataList(celulaPessoaQuadra))));
                                sprintf(teste, "\n\t<ellipse cx=\"%.2lf\" cy=\"%.2lf\" rx=\"2.5\" ry=\"4\" fill=\"%s\"/>", endereco[0], endereco[1], "darkblue");
                                char *teste2 = calloc(strlen(teste) + 2, sizeof(char));
                                strcpy(teste2, teste);
                                InsereElementoLista(listaSvg, teste2);
                                free(endereco);
                            }
                        }
                    }
                    if (verificadorFuncao == 1) {
                        if (getDataPessoaSexo(getdataList(celulaPessoaQuadra)) == 'F') {
                            fprintf(qry, "Dados do morador:\ncpf: %s\tnome: %s\tsobrenome: %s\tsexo: %c\tdata de nascimento: %s\n", getDataPessoaCpf(getdataList(celulaPessoaQuadra)), getDataPessoaNome(getdataList(celulaPessoaQuadra)), getDataPessoaSobrenome(getdataList(celulaPessoaQuadra)), getDataPessoaSexo(getdataList(celulaPessoaQuadra)), getDataPessoaNascimento(getdataList(celulaPessoaQuadra)));
                            if (getDataPessoaTipoMoradia(getdataList(celulaPessoaQuadra)) == 0)
                                fprintf(qry, "Dados da moradia: pessoa não mora em lugar algum\n");

                            else if (getDataPessoaTipoMoradia(getdataList(celulaPessoaQuadra)) == 1)
                                fprintf(qry, "Dados da moradia:\npessoa mora de aluguel no cep: %s\tface: %c\tnumero: %d\tcomplemento: %s\n", getDataCepLocacao(getDataPessoaMoradia(getdataList(celulaPessoaQuadra))), getDataFaceLocacao(getDataPessoaMoradia(getdataList(celulaPessoaQuadra))), getDataNumeroLocacao(getDataPessoaMoradia(getdataList(celulaPessoaQuadra))), getDataComplexoLocacao(getDataPessoaMoradia(getdataList(celulaPessoaQuadra))));

                            else if (getDataPessoaTipoMoradia(getdataList(celulaPessoaQuadra)) == 2)
                                fprintf(qry, "Dados da moradia:\npessoa mora em uma casa própria no cep: %s\tface: %c\tnumero: %d\tcomplemento: %s\n", getDataCepLocacao(getDataPessoaMoradia(getdataList(celulaPessoaQuadra))), getDataFaceLocacao(getDataPessoaMoradia(getdataList(celulaPessoaQuadra))), getDataNumeroLocacao(getDataPessoaMoradia(getdataList(celulaPessoaQuadra))), getDataComplexoLocacao(getDataPessoaMoradia(getdataList(celulaPessoaQuadra))));
                            fprintf(qry, "\n");

                            if (getDataPessoaTipoMoradia(getdataList(celulaPessoaQuadra)) != 0) {
                                char teste[1000];
                                double *endereco = calculaEndereco(avl, quadrasHash, getDataCepLocacao(getDataPessoaMoradia(getdataList(celulaPessoaQuadra))), getDataFaceLocacao(getDataPessoaMoradia(getdataList(celulaPessoaQuadra))), getDataNumeroLocacao(getDataPessoaMoradia(getdataList(celulaPessoaQuadra))));
                                sprintf(teste, "\n\t<ellipse cx=\"%.2lf\" cy=\"%.2lf\" rx=\"2.5\" ry=\"4\" fill=\"%s\"/>", endereco[0], endereco[1], "deeppink");
                                char *teste2 = calloc(strlen(teste) + 2, sizeof(char));
                                strcpy(teste2, teste);
                                InsereElementoLista(listaSvg, teste2);
                                free(endereco);
                            }
                        }
                    }
                    celulaPessoaQuadra = getnextLista(celulaPessoaQuadra);
                }
            }
        }
        celulaListaQuadra = getnextLista(celulaListaQuadra);
    }
}

void del(Tree avl, Tabela quadrasHash, char *cep, void *Stvar, char *path4, void *listaSvg) {
    mInterrogacao(avl, quadrasHash, cep, Stvar, path4, 1);

    void *celulaQuadra = PercorreLista(quadrasHash, cep, getDataCep);

    FILE *qry = fopen(path4, "a");

    if (celulaQuadra == NULL) {
        fclose(qry);
        return;

    } else {
        double x = getDataX(getdataList(celulaQuadra));
        void *celulaTree = retornaListaAvl(avl, x);
        void *celulaTreeFree = retornaCelulaAvl(avl, x);
        while (celulaTreeFree) {
            if (!celulaTreeFree)
                break;
            if (strcmp(getDataCep(getdataList(celulaTreeFree)), cep))
                celulaTreeFree = getnextLista(celulaTreeFree);
            else
                break;
        }

        if (!celulaTreeFree)
            puts("ERRO NA DEL");

        void *lista = getRegistro(quadrasHash, cep);
        RemoveCelulaListaPorData(lista, cep, getDataCep);

        char teste[1000];
        sprintf(teste, "\n\t<line x1=\" %.2lf \" x2=\" %.2lf \" y1=\" %.2lf \" y2=\" %.2lf \" stroke=\" %s \" stroke-width=\"1px\" />", getDataX(getdataList(celulaTreeFree)) + (getDataW(getdataList(celulaTreeFree)) / 2), getDataX(getdataList(celulaTreeFree)) + (getDataW(getdataList(celulaTreeFree)) / 2), getDataY(getdataList(celulaTreeFree)) + (getDataH(getdataList(celulaTreeFree)) / 2), -10.0 - (getDataH(getdataList(celulaTreeFree)) / 2), "green");
        char *teste2 = calloc(strlen(teste) + 2, sizeof(char));
        strcpy(teste2, teste);
        InsereElementoLista(listaSvg, teste2);
        sprintf(teste, "\n\t<text x=\"%lf\" y=\"%lf\" font-size=\"5\">cep - %s</text>", getDataX(getdataList(celulaTreeFree)) + (getDataW(getdataList(celulaTreeFree)) / 2), -10.0 - (getDataH(getdataList(celulaTreeFree)) / 2), getDataCep(getdataList(celulaTreeFree)));
        teste2 = calloc(strlen(teste) + 2, sizeof(char));
        strcpy(teste2, teste);
        InsereElementoLista(listaSvg, teste2);

        if (gettamanhoLista(celulaTree) == 1) {
            FreeLista(getDataPessoasLista(getdataList(celulaTreeFree)), 0);
            free(getDataPessoasLista(getdataList(celulaTreeFree)));
            FreeLista(getDataLocacoesLista(getdataList(celulaTreeFree)), 0);
            free(getDataLocacoesLista(getdataList(celulaTreeFree)));
            deleteNode(avl, getdataList(getheadLista(celulaTree)));
        } else {
            FreeLista(getDataPessoasLista(getdataList(celulaTreeFree)), 0);
            free(getDataPessoasLista(getdataList(celulaTreeFree)));
            FreeLista(getDataLocacoesLista(getdataList(celulaTreeFree)), 0);
            free(getDataLocacoesLista(getdataList(celulaTreeFree)));
            RemoveCelulaListaPorData(celulaTree, cep, getDataCep);
        }
    }

    fclose(qry);
}

void catac(Tree avl, Tabela quadrasHash, double x, double y, double w, double h, void *Stvar, char *path4, void *listaSvg) {
    void *celulaAvl = getHead(avl);
    FILE *qry = fopen(path4, "a");

    int *verificador = calloc(1, sizeof(int));
    *verificador = 0;

    char teste[1000];
    sprintf(teste, "\n\t<rect x=\"%.2lf\" y=\"%.2lf\" width=\"%.2lf\" height=\"%.2lf\" stroke=\"%s\" stroke-width=\"1px\" fill=\"%s\" opacity=\"0.5\"/>", x, y, w, h, "#AA0044", "#AB37C8");
    char *teste2 = calloc(strlen(teste) + 2, sizeof(char));
    strcpy(teste2, teste);
    InsereElementoLista(listaSvg, teste2);

    fprintf(qry, "Função catac - x %.2lf y %.2lf w %.2lf h %.2lf  {\n", x, y, w, h);

    catacRec(avl, celulaAvl, quadrasHash, x, y, w, h, Stvar, qry, verificador, listaSvg);

    if (*verificador == 0)
        fprintf(qry, "\nNenhuma quadra se encaixa nos parametros passados\n");

    fprintf(qry, "\n}\n\n");
    fclose(qry);
    free(verificador);
}

void catacRec(Tree avl, Posic celulaAtual, Tabela quadrasHash, double x, double y, double w, double h, void *Stvar, void *qry, int *verificador, void *listaSvg) {
    if (!celulaAtual) {
        return;
    }

    int verificadorCelulaRemovida = 0;

    if (AvlLeft(celulaAtual)) {
        if (getMax(AvlLeft(celulaAtual)) >= x && getMin(AvlLeft(celulaAtual)) <= x + w)
            catacRec(avl, AvlLeft(celulaAtual), quadrasHash, x, y, w, h, Stvar, qry, verificador, listaSvg);
    }

    if (AvlRight(celulaAtual)) {
        if (getMax(AvlRight(celulaAtual)) >= x && getMin(AvlRight(celulaAtual)) <= x + w)
            catacRec(avl, AvlRight(celulaAtual), quadrasHash, x, y, w, h, Stvar, qry, verificador, listaSvg);
    }

    void *celulaListaQuadra = getheadLista(getData(celulaAtual));
    while (celulaListaQuadra) {
        void *celulaListaQuadraAux;
        if (getnextLista(celulaListaQuadra))
            celulaListaQuadraAux = getnextLista(celulaListaQuadra);
        else
            celulaListaQuadraAux = NULL;
        if (getDataX(getdataList(celulaListaQuadra)) >= x && getDataX(getdataList(celulaListaQuadra)) + getDataW(getdataList(celulaListaQuadra)) <= x + w) {
            if (getDataY(getdataList(celulaListaQuadra)) >= y && getDataY(getdataList(celulaListaQuadra)) + getDataH(getdataList(celulaListaQuadra)) <= y + h) {
                *verificador = 1;
                fprintf(qry, "\nQuadra do cep %s [\n", getDataCep(getdataList(celulaListaQuadra)));
                void *listaPessoasQuadra = getDataPessoasLista(getdataList(celulaListaQuadra));
                void *celulaPessoaQuadra = getheadLista(listaPessoasQuadra);
                if (!celulaPessoaQuadra)
                    fprintf(qry, "Quadra não tem morador\n");
                else {
                    while (celulaPessoaQuadra) {
                        fprintf(qry, "Dados de um morador:\ncpf: %s\tnome: %s\tsobrenome: %s\tsexo: %c\tdata de nascimento: %s\n", getDataPessoaCpf(getdataList(celulaPessoaQuadra)), getDataPessoaNome(getdataList(celulaPessoaQuadra)), getDataPessoaSobrenome(getdataList(celulaPessoaQuadra)), getDataPessoaSexo(getdataList(celulaPessoaQuadra)), getDataPessoaNascimento(getdataList(celulaPessoaQuadra)));
                        if (getDataPessoaTipoMoradia(getdataList(celulaPessoaQuadra)) == 0)
                            fprintf(qry, "Pessoa não mora em lugar algum\n");

                        else if (getDataPessoaTipoMoradia(getdataList(celulaPessoaQuadra)) == 1)
                            fprintf(qry, "Dados de sua moradia:\npessoa mora de aluguel no cep: %s\tface: %c\tnumero: %d\tcomplemento: %s\n", getDataCepLocacao(getDataPessoaMoradia(getdataList(celulaPessoaQuadra))), getDataFaceLocacao(getDataPessoaMoradia(getdataList(celulaPessoaQuadra))), getDataNumeroLocacao(getDataPessoaMoradia(getdataList(celulaPessoaQuadra))), getDataComplexoLocacao(getDataPessoaMoradia(getdataList(celulaPessoaQuadra))));

                        else if (getDataPessoaTipoMoradia(getdataList(celulaPessoaQuadra)) == 2)
                            fprintf(qry, "Dados de sua moradia:\npessoa mora em uma casa própria no cep: %s\tface: %c\tnumero: %d\tcomplemento: %s\n", getDataCepLocacao(getDataPessoaMoradia(getdataList(celulaPessoaQuadra))), getDataFaceLocacao(getDataPessoaMoradia(getdataList(celulaPessoaQuadra))), getDataNumeroLocacao(getDataPessoaMoradia(getdataList(celulaPessoaQuadra))), getDataComplexoLocacao(getDataPessoaMoradia(getdataList(celulaPessoaQuadra))));
                        celulaPessoaQuadra = getnextLista(celulaPessoaQuadra);
                        fprintf(qry, "\n");
                    }
                }

                void *listaLocacoesQuadra = getDataLocacoesLista(getdataList(celulaListaQuadra));
                void *celulaLocacaoQuadra = getheadLista(listaLocacoesQuadra);

                if (!celulaLocacaoQuadra)
                    fprintf(qry, "Quadra não tem locações (sem morador)");
                else {
                    while (celulaLocacaoQuadra) {
                        fprintf(qry, "Dados de uma locação (sem morador):\nid: %s\tcep: %s\tface: %c\tnumero: %d\tcomplemento: %s\tarea: %.2lf\tvalor mensal: %.2lf", getDataIdLocacao(getdataList(celulaLocacaoQuadra)), getDataCepLocacao(getdataList(celulaLocacaoQuadra)), getDataFaceLocacao(getdataList(celulaLocacaoQuadra)), getDataNumeroLocacao(getdataList(celulaLocacaoQuadra)), getDataComplexoLocacao(getdataList(celulaLocacaoQuadra)), getDataAreaLocacao(getdataList(celulaLocacaoQuadra)), getDatavMensaisLocacao(getdataList(celulaLocacaoQuadra)));
                        celulaLocacaoQuadra = getnextLista(celulaLocacaoQuadra);
                    }
                }
                fprintf(qry, " ]\n");

                void *celulaTree = retornaListaAvl(avl, getDataX(getdataList(celulaListaQuadra)));
                void *celulaTreeFree = retornaCelulaAvl(avl, getDataX(getdataList(celulaListaQuadra)));
                while (celulaTreeFree) {
                    if (!celulaTreeFree)
                        break;
                    if (strcmp(getDataCep(getdataList(celulaTreeFree)), getDataCep(getdataList(celulaListaQuadra))))
                        celulaTreeFree = getnextLista(celulaTreeFree);
                    else
                        break;
                }

                void *lista = getRegistro(quadrasHash, getDataCep(getdataList(celulaListaQuadra)));
                RemoveCelulaListaPorData(lista, getDataCep(getdataList(celulaListaQuadra)), getDataCep);

                if (gettamanhoLista(celulaTree) == 1) {
                    verificadorCelulaRemovida = 1;
                    FreeLista(getDataPessoasLista(getdataList(celulaTreeFree)), 0);
                    free(getDataPessoasLista(getdataList(celulaTreeFree)));
                    FreeLista(getDataLocacoesLista(getdataList(celulaTreeFree)), 0);
                    free(getDataLocacoesLista(getdataList(celulaTreeFree)));
                    deleteNode(avl, getdataList(getheadLista(celulaTree)));
                } else {
                    FreeLista(getDataPessoasLista(getdataList(celulaTreeFree)), 0);
                    free(getDataPessoasLista(getdataList(celulaTreeFree)));
                    FreeLista(getDataLocacoesLista(getdataList(celulaTreeFree)), 0);
                    free(getDataLocacoesLista(getdataList(celulaTreeFree)));
                    RemoveCelulaListaPorData(celulaTree, getDataCep(getdataList(celulaListaQuadra)), getDataCep);
                }
            }
        }
        if (verificadorCelulaRemovida == 0)
            celulaListaQuadra = celulaListaQuadraAux;
        else
            break;
    }
}

void dmpt(Tree avl, char *sfx, void *Stvar, char *pathSfx) {
    void *celulaAvl = getHead(avl);
    FILE *qry = fopen(pathSfx, "w");

    fprintf(qry, "digraph G {\n");

    dmptRec(avl, celulaAvl, sfx, Stvar, pathSfx, qry);

    fprintf(qry, "}\n");

    fclose(qry);
}

void dmptRec(Tree avl, Posic celulaAtual, char *sfx, void *Stvar, char *pathSfx, void *qry) {
    if (!celulaAtual) {
        return;
    }

    void *celulaListaQuadra = getheadLista(getData(celulaAtual));

    if (AvlLeft(celulaAtual))
        fprintf(qry, "\t%lf->%lf\n", getDataX(getdataList(getheadLista(getData(celulaAtual)))), getDataX(getdataList(getheadLista(getData(AvlLeft(celulaAtual))))));

    if (AvlRight(celulaAtual))
        fprintf(qry, "\t%lf->%lf\n", getDataX(getdataList(getheadLista(getData(celulaAtual)))), getDataX(getdataList(getheadLista(getData(AvlRight(celulaAtual))))));

    fprintf(qry, "\t%lf[label = \"X ancora = %.2lf\n", getDataX(getdataList(celulaListaQuadra)), getDataX(getdataList(celulaListaQuadra)));
    fprintf(qry, "\tCep = %s\n", getDataCep(getdataList(celulaListaQuadra)));

    int cont = 0;
    while (celulaListaQuadra && cont < 2) {
        if (getnextLista(celulaListaQuadra)) {
            celulaListaQuadra = getnextLista(celulaListaQuadra);

            fprintf(qry, "\tCep = %s\n", getDataCep(getdataList(celulaListaQuadra)));

            cont++;
        } else
            celulaListaQuadra = NULL;
    }

    fprintf(qry, "\tMin = %lf\n", getMin(celulaAtual));
    fprintf(qry, "\tMax = %lf\n", getMax(celulaAtual));
    fprintf(qry, "\tQnt de quadras = %d\n", gettamanhoLista(getdataList(celulaAtual)));
    fprintf(qry, "\tAltura = %d\n", altura(celulaAtual));
    fprintf(qry, "\tFator de balanceamento = %d\"]\n", getBalance(celulaAtual));

    dmptRec(avl, AvlLeft(celulaAtual), sfx, Stvar, pathSfx, qry);
    dmptRec(avl, AvlRight(celulaAtual), sfx, Stvar, pathSfx, qry);
}

void olocInterrogacao(Tree avl, Tabela quadrasHash, double x, double y, double w, double h, void *Stvar, char *path4, void *listaSvg) {
    void *celulaAvl = getHead(avl);
    FILE *qry = fopen(path4, "a");

    char teste[1000];
    sprintf(teste, "\n\t<rect x=\"%.2lf\" y=\"%.2lf\" width=\"%.2lf\" height=\"%.2lf\" stroke=\"%s\" stroke-width=\"3px\" fill=\"none\" opacity=\"1\" stroke-dasharray=\"5\" />", x, y, w, h, "darkred");
    char *teste2 = calloc(strlen(teste) + 2, sizeof(char));
    strcpy(teste2, teste);
    InsereElementoLista(listaSvg, teste2);

    fprintf(qry, "Função oloc? - x %.2lf y %.2lf w %.2lf h %.2lf  {\n", x, y, w, h);

    olocInterrogacaoRec(avl, quadrasHash, celulaAvl, x, y, w, h, Stvar, qry, listaSvg);

    fprintf(qry, "\n}\n\n");
    fclose(qry);
}

void olocInterrogacaoRec(Tree avl, Tabela quadrasHash, Posic celulaAtual, double x, double y, double w, double h, void *Stvar, void *qry, void *listaSvg) {
    if (!celulaAtual) {
        return;
    }

    if (getMin(celulaAtual) <= x + w && getMax(celulaAtual) >= x) {
        olocInterrogacaoRec(avl, quadrasHash, AvlRight(celulaAtual), x, y, w, h, Stvar, qry, listaSvg);
        olocInterrogacaoRec(avl, quadrasHash, AvlLeft(celulaAtual), x, y, w, h, Stvar, qry, listaSvg);
    }

    void *celulaListaQuadra = getheadLista(getData(celulaAtual));
    while (celulaListaQuadra) {
        if (getDataX(getdataList(celulaListaQuadra)) >= x && getDataX(getdataList(celulaListaQuadra)) + getDataW(getdataList(celulaListaQuadra)) <= x + w) {
            if (getDataY(getdataList(celulaListaQuadra)) >= y && getDataY(getdataList(celulaListaQuadra)) + getDataH(getdataList(celulaListaQuadra)) <= y + h) {
                fprintf(qry, "\nQuadra do cep %s [\n", getDataCep(getdataList(celulaListaQuadra)));

                void *listaLocacoesQuadra = getDataLocacoesLista(getdataList(celulaListaQuadra));
                void *celulaLocacaoQuadra = getheadLista(listaLocacoesQuadra);

                if (!celulaLocacaoQuadra)
                    fprintf(qry, "Quadra não tem locações disponíveis");
                else {
                    while (celulaLocacaoQuadra) {
                        char teste[1000];
                        double *endereco = calculaEndereco(avl, quadrasHash, getDataCepLocacao(getdataList(celulaLocacaoQuadra)), getDataFaceLocacao(getdataList(celulaLocacaoQuadra)), getDataNumeroLocacao(getdataList(celulaLocacaoQuadra)));
                        sprintf(teste, "\n\t<text x=\"%lf\" y=\"%lf\" font-size=\"5\">*</text>", endereco[0], endereco[1]);
                        void *teste2 = calloc(strlen(teste) + 2, sizeof(char));
                        strcpy(teste2, teste);
                        InsereElementoLista(listaSvg, teste2);
                        free(endereco);
                        fprintf(qry, "Dados de uma locação disponível:\nid: %s\tcep: %s\tface: %c\tnumero: %d\tcomplemento: %s\tarea: %.2lf\tvalor mensal: %.2lf", getDataIdLocacao(getdataList(celulaLocacaoQuadra)), getDataCepLocacao(getdataList(celulaLocacaoQuadra)), getDataFaceLocacao(getdataList(celulaLocacaoQuadra)), getDataNumeroLocacao(getdataList(celulaLocacaoQuadra)), getDataComplexoLocacao(getdataList(celulaLocacaoQuadra)), getDataAreaLocacao(getdataList(celulaLocacaoQuadra)), getDatavMensaisLocacao(getdataList(celulaLocacaoQuadra)));
                        celulaLocacaoQuadra = getnextLista(celulaLocacaoQuadra);
                    }
                }
                fprintf(qry, " ]\n");
            }
        }
        celulaListaQuadra = getnextLista(celulaListaQuadra);
    }
}

void *PercorreLista(Tabela tabela, char *chave, char *getData(void *auxDados)) {
    void *lista = getRegistro(tabela, chave);
    if (!lista)
        return NULL;
    void *celula = getheadLista(lista);

    int verificador = 0;

    while (celula) {
        if (!strcmp(getData(getdataList(celula)), chave)) {
            verificador = 1;
            break;
        }
        celula = getnextLista(celula);
    }

    if (verificador == 0) {
        celula = NULL;
    }

    return celula;
}

double *calculaEndereco(Tree avl, Tabela quadrasHash, char *cep, char face, int numero) {
    void *celulaQuadra = PercorreLista(quadrasHash, cep, getDataCep);

    double *endereco = calloc(2, sizeof(double));
    endereco[0] = -100;
    endereco[1] = -100;

    if (celulaQuadra == NULL) {
        return endereco;

    } else {
        double x = getDataX(getdataList(celulaQuadra));
        void *celulaTree = retornaListaAvl(avl, x);
        void *celulaTreeFree = retornaCelulaAvl(avl, x);
        while (celulaTreeFree) {
            if (!celulaTreeFree)
                break;
            if (strcmp(getDataCep(getdataList(celulaTreeFree)), cep))
                celulaTreeFree = getnextLista(celulaTreeFree);
            else
                break;
        }

        if (!celulaTreeFree)
            puts("ERRO NA CALCULA ENDERECO");
    }

    if (face == 'S') {
        endereco[0] = getDataX(getdataList(celulaQuadra)) + numero;
        endereco[1] = getDataY(getdataList(celulaQuadra)) + (0.1 * getDataH(getdataList(celulaQuadra)));
    } else if (face == 'N') {
        endereco[0] = getDataX(getdataList(celulaQuadra)) + numero;
        endereco[1] = getDataY(getdataList(celulaQuadra)) + getDataH(getdataList(celulaQuadra)) - (0.1 * getDataH(getdataList(celulaQuadra)));
    } else if (face == 'O') {
        endereco[1] = getDataY(getdataList(celulaQuadra)) + numero;
        endereco[0] = getDataX(getdataList(celulaQuadra)) + getDataW(getdataList(celulaQuadra)) - (0.1 * getDataW(getdataList(celulaQuadra)));
    } else if (face == 'L') {
        endereco[1] = getDataY(getdataList(celulaQuadra)) + numero;
        endereco[0] = getDataX(getdataList(celulaQuadra)) + (0.1 * getDataW(getdataList(celulaQuadra)));
    }

    return endereco;
}
