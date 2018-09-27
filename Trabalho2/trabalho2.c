/*  Max Henrique Barbosa - 16/0047013
    Érico Maximiano - 16/0070287 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>



// DECLARACAO DE FUNCOES

void alocaMatriz(int **vetorImagens);
int gerarNumeroAleatorio ();
void selecionarGrama (int *grama, char *nomeArquivo);

// MAIN
int main(int argc, char const *argv[]) {

  FILE *fp;
  int **vetorImagens;
  int linhas, colunas, i, j, cont, contCol, contLine, pixel;
  int taxaAcerto = 0, taxaFalsaRejeicao = 0, taxaFalsaAceitacao = 0;
  double *mediaGrama, *mediaAsfalto;
  double **aspectos;
  char nomeArquivo[20] = "", aux;
  static int asfalto[50], grama[50];

    if(
      mediaGrama = (double*)calloc(536,sizeof(double)),mediaGrama == NULL){
      printf("alocação falhou!\n");
      exit(1);
    }

    if(
      mediaAsfalto = (double*)calloc(536,sizeof(double)),mediaAsfalto == NULL){
      printf("alocação falhou!\n");
      exit(1);
    }

    // if(
    //   aspectos = (double**)calloc(50,sizeof(double*)),aspectos == NULL){
    //   printf("alocação falhou!\n");
    //   exit(1);
    // }
    // for(i = 0; i < 50; i++){
    //   if(*(aspectos+i) = (double*)calloc(TAMVET,sizeof(double)),*(aspectos+i) == NULL){
    //     printf("alocação falhou!\n");
    //     exit(1);
    //   }
    // }

  free(fp);
  return 0;
}
//-------------------------------------------------------------------------
int gerarNumeroAleatorio (){ //Gerar numeros aleatórios para selicionar arquivos
  srand(time(NULL));
  return (rand() % 50) + 1;
}
//-------------------------------------------------------------------------
void selecionarGrama (int *grama, char *nomeArquivo){
  int nAleatorio;

  nAleatorio = gerarNumeroAleatorio ();
  sprintf(nomeArquivo, "./DataSet/grass/grass_%02d.txt", nAleatorio);
  grama[nAleatorio-1] = 1;
}
//-------------------------------------------------------------------------
void selecionarAsfalto (int *asfalto, char *nomeArquivo){
  int nAleatorio;

  nAleatorio = gerarNumeroAleatorio ();
  sprintf(nomeArquivo, "./DataSet/asphalt/asphalt_%02d.txt", nAleatorio);
  grama[nAleatorio-1] = 1;
}
//-------------------------------------------------------------------------
void treinoDeMetricas (){

}
//-------------------------------------------------------------------------
