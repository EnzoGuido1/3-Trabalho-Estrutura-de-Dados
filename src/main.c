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

int main(int argc, char **argv) {
    void *Stvar = createVar();
    void *listaSvg = CriaLista();
    void *avl = CriaArvore(compareDouble, free);

    leituraParametros(argc, argv, Stvar);
    void *quadrasHash = leituraGeo(avl, Stvar);

    void *pessoas = criaTabela(getVarNx(Stvar));
    void *locacoes = criaTabela(getVarNx(Stvar));

    leituraPm(avl, pessoas, locacoes, quadrasHash, Stvar);

    char *saidaGeo = leituraQry(avl, pessoas, locacoes, quadrasHash, listaSvg, Stvar);  //caso !strcmp(saidaGeo, "NULL") NÃO FAÇA NADA

    if (getVarQryVerifica(Stvar) != 0) {
        FILE *inicializaSvgSaida = fopen(saidaGeo, "w");

        fprintf(inicializaSvgSaida, "<svg xmlns=\"http://www.w3.org/2000/svg\">  <!--ENZO GUIDO-->");

        imprimeSvgAvl(avl, inicializaSvgSaida, getHead(avl));

        void *cabeca = getheadLista(listaSvg);
        for (int i = 0; i < gettamanhoLista(listaSvg); i++) {
            fprintf(inicializaSvgSaida, "%s", ((char *)getdataList(cabeca)));
            cabeca = getnextLista(cabeca);
        }

        fprintf(inicializaSvgSaida, "\n</svg>");

        fclose(inicializaSvgSaida);
    }

    // puts("\n\nPESSOAS HASHTABLE:");
    // for (int i = 0; i < getVarNx(Stvar); i++) {
    //     printList(retornaRegistroLista(pessoas, i), getDataPessoaCpf);
    // }

    // printf("\n\n//==//==//==//==//==//==//==//==//==//==//==//==//==//==//\n\n");

    // puts("LOCACOES HASHTABLE:");
    // for (int i = 0; i < getVarNx(Stvar); i++) {
    //     printList(retornaRegistroLista(locacoes, i), getDataIdLocacao);
    // }

    // printf("\n\n//==//==//==//==//==//==//==//==//==//==//==//==//==//==//\n\n");

    // puts("QUADRAS AVL:");
    // printRecursivoRec(avl);

    //bloco de free
    if (saidaGeo)
        free(saidaGeo);

    freeRegistro(pessoas, 1);  //esse numero 1 corresponde ao free locações que esta nos dados de uma pessoa, da free na sua moradia
    free(pessoas);

    freeRegistro(locacoes, 0);
    free(locacoes);

    freeRegistro(quadrasHash, 0);
    free(quadrasHash);

    freeAvl(avl);
    free(avl);

    freeParametros(Stvar);

    FreeLista(listaSvg, 0);
    free(listaSvg);

    return 0;
}
