#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TRUE 0
#define FALSE 1

#define MODO_DEBUG 0


typedef struct MaiorSub{

    int *num;
    int *best;
    int *next;
    int tamanho;
    int maior[2];
    int modo_debug;

}MaiorSub;

void setMaiorSub( MaiorSub *maiorSub, int modo_debug);
void initSystem( MaiorSub *maiorSub );
void calcSubSequencia( MaiorSub *maiorSub);
void leArquivo( MaiorSub *maiorSub, int modoDebug);
void leArquivo2( MaiorSub *maiorSub, int modoDebug);
void criaArquivo( MaiorSub *maiorSub, int modoDebug);
