/*  Max Henrique Barbosa - 16/0047013
    Érico Maximiano - 16/0070287 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>



// DECLARACAO DE FUNCOES

void alocaMatriz(int **);
int gerarNumeroAleatorio ();
void selecionarGrama (int *, char *);
void ilbp(int **,int ,int ,double **, int);
void ilbpQuadrante(int **,int ,int ,double **,int);


// MAIN
int main(int argc, char const *argv[]) {

  FILE *fp;
  int **vetorImagens;
  int linha, coluna, i, j, cont, pixel;
  int taxaAcerto = 0, taxaFalsaRejeicao = 0, taxaFalsaAceitacao = 0;
  double *mediaGrama, *mediaAsfalto;
  double **aspectos;
  char nomeArquivo[20] = "", aux;
  static int asfalto[50], grama[50];

    if(mediaGrama = (double*)calloc(536,sizeof(double)),mediaGrama == NULL){
      printf("alocação falhou!\n");
      exit(1);
    }

    if(mediaAsfalto = (double*)calloc(536,sizeof(double)),mediaAsfalto == NULL){
      printf("alocação falhou!\n");
      exit(1);
    }

    if(
      aspectos = (double**)calloc(50,sizeof(double*)),aspectos == NULL){
      printf("alocação falhou!\n");
      exit(1);
    }
    for(i = 0; i < 50; i++){
      if(*(aspectos+i) = (double*)calloc(TAMVET,sizeof(double)),*(aspectos+i) == NULL){
        printf("alocação falhou!\n");
        exit(1);
      }
    }

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
void ilbp(int **vetorImagens,int linha,int colunas,double **aspectos,int cont){
  int i,j;
  for(i = 1; i < linha-1; i++) {
    for (j = 1; j < colunas-1; j++) {
      fazIlbpQuadrante(vetorImagens,i,j,aspectos,cont);
    }
  }
}
//-----------------------------------------------------------------------------
int AchaMenorValor(int *vetor,int menor,int cont){
  int n;
  if (cont == 9) {
    return menor;
  } else {
    n = fazBinParaDecimal(vetor);
    if (n < menor) {
      menor = n;
    }
    rotacionaVetor(vetor);
    return AchaMenorValor(vetor,menor,cont+1);
  }
}
//-------------------------------------------------------------------------
void ilbpQuadrante(int **vetorImagens,int linha,int coluna,double **aspectos,int aux){
  double total=0.0;
  int cont=0,menorValor;
  int vetor[9];
  for (int i = linha-1; i <= linha+1; i++) {
    for (int j = coluna-1; j <= coluna+1; j++) {
      total += *(*(matriz+i)+j);
      vetor[cont] = matriz[i][j];
      cont++;
    }
  }
  for (int i = 0; i < 9; i++) {
    if (total/9 >= vetor[i]) {
      vetor[i] = 1;
    } else {
      vetor[i] = 0;
    }
  }
  menorValor = AchaMenorValor(vetor,TAMCOD,0);
  if (aux%2) {
    caracteristicas[(aux-1)/2][menorValor]+=1;
  } else {
    caracteristicas[IMAGENS/2+aux/2][menorValor]+=1;
  }
}
//-------------------------------------------------------------------------
