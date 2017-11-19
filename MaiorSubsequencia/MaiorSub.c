#include "MaiorSub.h"


void setMaiorSub( MaiorSub *maiorSub, int modo_debug ){

    int i = 0;

    maiorSub ->modo_debug = modo_debug;
    maiorSub ->maior[0] = 0;
    maiorSub ->maior[1] = 0;
    maiorSub ->num = (int*) malloc( maiorSub ->tamanho * sizeof(int*) );
    maiorSub ->best = (int*) malloc( maiorSub ->tamanho * sizeof(int*) );
    maiorSub ->next = (int*) malloc( maiorSub ->tamanho * sizeof(int*) );

    for( i = 0; i < maiorSub ->tamanho; i++ ){
        maiorSub ->num[i] = 0;
        maiorSub ->best[i] = 0;
        maiorSub ->next[i] = 0;
    }


}

void initSystem( MaiorSub *maiorSub ){

    int modoDebug = 0;
    int opcao = 0;


    printf("Entre com o modo do sistema:\n");
    printf("0 - Modo Debug\nQualquer outro valor - Modo normal\n");
    printf("Opcao: ");
    scanf("%d", &modoDebug);

    printf("Voce deseja criar um arquivo com numeros aleatorios ou entrar com um arquivo de sua escolha?\n");
    printf("0 - CRIAR\n1 - ENTRAR\n");
    scanf("%d", &opcao);

    if( opcao < 0 || opcao > 1){
        opcao = 1;
    }

    if(modoDebug != 0 ){
        modoDebug = 1;
    }

    if( opcao == 0){
        criaArquivo(maiorSub, modoDebug);
        leArquivo2(maiorSub, modoDebug);

    }
    else{
        leArquivo( maiorSub, modoDebug );
    }


}

void calcSubSequencia( MaiorSub *maiorSub ){

    int i = 0;
    int j = 0;
    int size = maiorSub ->tamanho;
    clock_t tempoInicial;
    clock_t tempoFinal;
    double tempoGasto = 0;

    tempoInicial = clock();

    maiorSub ->best[size - 1] = 1;
    maiorSub ->next[size - 1] = -1;
    maiorSub ->maior[0] = maiorSub ->best[size - 1];

    for( i = size - 2; i > -1; i-- ){
        maiorSub ->best[i] = 1;
        maiorSub ->next[i] = -1;
        for( j = i + 1; j < size; j++){
            if( maiorSub ->num[j] > maiorSub ->num[i] && ( maiorSub ->best[j] + 1 > maiorSub ->best[i]) ){
                maiorSub ->best[i] = 1 + maiorSub ->best[j];
                if( maiorSub->maior[0] < 1 + maiorSub ->best[j] ){
                    maiorSub ->maior[0] = 1 + maiorSub ->best[j];
                    maiorSub ->maior[1] = i ;
                }
                maiorSub ->next[i] = j;
            }

        }
    }

    tempoFinal = clock();
    tempoGasto = (double)((tempoFinal - tempoInicial)/ CLOCKS_PER_SEC);

    system("clear");
    printf("O maior numero de elementos na subsequencia e: %d\n", maiorSub ->maior[0]);
    printf("A subsquencia e: ");

    i = maiorSub ->maior[1];

    do{
        printf("%d ", maiorSub ->num[i]);
        i = maiorSub ->next[i];
    }while( i != -1 );

    if( maiorSub ->modo_debug == 0){
        printf("\n");
        printf("O tempo total de execucao e: %.3f\n", tempoGasto);
    }


}

void leArquivo( MaiorSub *maiorSub, int modoDebug ){

    char nomeArq[20];
    int i = 0;

    system("clear");
    fflush(stdin);
    printf("Entre com o nome do arquivo: ");
    gets(nomeArq);

    FILE *arq;

    arq = fopen(nomeArq, "r");

    if( arq == NULL ){
        printf("Arquivo nao encontrado ! \n");
        return(0);
    }

    system("clear");
    system("pause");

    fscanf(arq, "%d", &(maiorSub ->tamanho));

    setMaiorSub(maiorSub, modoDebug);

    while( fscanf(arq, "%d", &(maiorSub ->num[i])) != EOF ){
        i++;
    }
    fclose(arq);
}


void criaArquivo( MaiorSub *maiorSub, int modoDebug){

    system("clear");

    FILE *arq;
    char nomeArq[20] = "arqEntrada.txt";
    int tamanho = 0;
    int i = 0;

    arq = fopen(nomeArq, "wt");

    if(arq == NULL){
        printf("Problema ao criar arquivo ! \n");
        return(0);
    }
    printf("Arquivo %s criado com sucesso\n", nomeArq);
    printf("Entre com o tamanho do vetor: ");
    scanf("%d", &tamanho);
    fprintf(arq, "%d\n", tamanho);

    srand(time(NULL));

    for( i = 0; i < tamanho; i++){
        fprintf(arq, "%d ", rand() % tamanho);
    }

    fclose(arq);
}

void leArquivo2( MaiorSub *maiorSub, int modoDebug ){

    char nomeArq[20] = "arqEntrada.txt";
    int i = 0;

    system("clear");

    FILE *arq;

    arq = fopen(nomeArq, "r");

    if( arq == NULL ){
        printf("Arquivo nao encontrado ! \n");
        return(0);
    }

    system("clear");
    system("pause");

    fscanf(arq, "%d", &(maiorSub ->tamanho));

    setMaiorSub(maiorSub, modoDebug);

    while( fscanf(arq, "%d", &(maiorSub ->num[i])) != EOF ){
        i++;
    }

    fclose(arq);
}
