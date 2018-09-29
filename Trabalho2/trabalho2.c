/*  Max Henrique Barbosa - 16/0047013
    Érico Maximiano - 16/0070287 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>



// DECLARACAO DE FUNCOES

int gerarNumeroAleatorio ();
int AchaMenorValor(int *,int ,int);
int transformaBinDecimal(int *);
void selecionarGrama (int *, char *);
void ilbp(int **,int ,int ,double **, int);
void ilbpQuadrante(int **,int ,int ,double **,int);
void alocaMatriz(int **);
void rotacionaVetor(int *);
void normalizaVetor(double *,int);
void mediaPontos(double **,double *,double *);
void euclidiana(double **, double *, double *, int *, int *, int *);




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
      if(*(aspectos+i) = (double*)calloc(536,sizeof(double)),*(aspectos+i) == NULL){
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
      ilbpQuadrante(vetorImagens,i,j,aspectos,cont);
    }
  }
}
//-----------------------------------------------------------------------------
int transformaBinDecimal(int *bin){
  int decimal=0;
  for (int i = 0; i < 9; i++) {
    decimal += pow(2,(8-i))*bin[i];
  }
  return decimal;
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
  menorValor = AchaMenorValor(vetor,256,0);
  if (aux%2) {
    aspectos[(aux-1)/2][menorValor]+=1;
  } else {
    aspectos[50/2+aux/2][menorValor]+=1;
  }
}
//-------------------------------------------------------------------------
void rotacionaVetor(int *vetor){
  int aux = vetor[0];
  int aux1;
  vetor[0] = vetor[8];
  for (int i = 1; i < 9; i++) {
    aux1 = vetor[i];
    vetor[i] = aux;
    aux = aux1;
  }
}
//-------------------------------------------------------------------------
void normalizaVetor(double *vetor,int 536or){

  int maior=0,menor=10000,i;
  for (i = 0; i < tamVetor; i++) {
    if (vetor[i] < menor) {
      menor = vetor[i];
    }else if(vetor[i] > maior){
      maior = vetor[i];
    }
  }
  if (maior == menor) {
    return;
  }
  for (i = 0; i < tamVetor; i++) {
    vetor[i] = (vetor[i] - menor)/(maior - menor);
  }
}
//-------------------------------------------------------------------------
void mediaPontos(double **aspectos,double *mediaGrama,double *mediaAsfalto){

  int i,j;
  double total=0.0;

  for (j = 0; j < 536; j++) {
    for (i = 0; i < 50/2; i++) {
      total+= aspectos[i][j];
    }
    mediaGrama[j] = total/(50/2);
    total = 0.0;
    for (i = 50/2; i < 50; i++) {
      total+= aspectos[i][j];
    }
    mediaAsfalto[j] = total/(50/2);
    total = 0.0;
  }
}
//-------------------------------------------------------------------------
void euclidiana(double **aspectos, double *mediaAsfalto,double *mediaGrama,int *taxaAcerto,int *taxaFalsaAceitacao,int *taxaFalsaRejeicao){

  double total = 0.0,distEuclidGrama,distEuclidAsfalto;
  int i,j;
  for (i = 0; i < 50; i++) {
    for (j = 0; j < 536; j++) {
      total+= pow(aspectos[i][j] - mediaGrama[j],2);
    }
    distEuclidGrama = sqrt(total);
    total = 0.0;
    for (j = 0; j < 536; j++) {
      total+= pow(aspectos[i][j] - mediaAsfalto[j],2);
    }
    distEuclidAsfalto = sqrt(total);
    total = 0.0;
    if (i < 50/2) {
      if (distEuclidGrama < distEuclidAsfalto) {
        *taxaAcerto += 1;
      } else {
        *taxaFalsaRejeicao += 1;
      }
    } else{
      if (distEuclidGrama > distEuclidAsfalto) {
        *taxaAcerto += 1;
      } else {
        *taxaFalsaAceitacao += 1;
      }
    }
  }
}
//EU PAREI AS ALTERAÇÕES AQUI
//-------------------------------------------------------------------------
double contraste(int **matriz){
  int i,j;
  double total=0.0;
  for (i = 0; i < TAMCOD; i++) {
    for (j = 0; j < TAMCOD; j++) {
      total += matriz[i][j]*pow(i-j,2);
    }
  }
  return total;
}
//-------------------------------------------------------------------------
double homogeneidade(int **matriz){
  int i,j;
  double total=0.0;
  for (i = 0; i < TAMCOD; i++) {
    for (j = 0; j < TAMCOD; j++) {
      total += matriz[i][j]/(1+abs(i-j));
    }
  }
  return total;
}
//-------------------------------------------------------------------------
double energia(int **matriz){
  int i,j;
  double total=0.0;
  for (i = 0; i < TAMCOD; i++) {
    for (j = 0; j < TAMCOD; j++) {
      total += pow(matriz[i][j],2);
    }
  }
  return total;
}
//-------------------------------------------------------------------------
void glcm(int **matriz,int linha,int coluna,double **caracteristicas,int cont){
  int ***matrizesGlcm;
  int i,j,t;

  if(matrizesGlcm = (int***)calloc(8,sizeof(int**)),matrizesGlcm == NULL){
    printf("alocação falhou!\n");
  }
	for (i = 0; i < 8; i++) {
    if(matrizesGlcm[i] = (int**)calloc(TAMCOD,sizeof(int*)),matrizesGlcm[i] == NULL){
      printf("alocação falhou!\n");
    }
		for (j = 0; j < TAMCOD; j++) {
      if(matrizesGlcm[i][j] = (int*)calloc(TAMCOD,sizeof(int)),matrizesGlcm[i][j] == NULL){
        printf("alocação falhou!\n");
      }
		}
	}

  for (t = 0; t < 8; t++) {
    for (i = 1; i < linha-1; i++) {
      for (j = 1; j < coluna-1; j++) {
        switch (t) {
          case 0:
            matrizesGlcm[t][matriz[i][j]][matriz[i-1][j-1]]++;
            break;
          case 1:
            matrizesGlcm[t][matriz[i][j]][matriz[i-1][j]]++;
            break;
          case 2:
            matrizesGlcm[t][matriz[i][j]][matriz[i-1][j+1]]++;
            break;
          case 3:
            matrizesGlcm[t][matriz[i][j]][matriz[i][j-1]]++;
            break;
          case 4:
            matrizesGlcm[t][matriz[i][j]][matriz[i][j+1]]++;
            break;
          case 5:
            matrizesGlcm[t][matriz[i][j]][matriz[i+1][j-1]]++;
            break;
          case 6:
            matrizesGlcm[t][matriz[i][j]][matriz[i+1][j]]++;
            break;
          case 7:
            matrizesGlcm[t][matriz[i][j]][matriz[i+1][j+1]]++;
        }
      }
    }
    if (cont%2) {
      caracteristicas[(cont-1)/2][512+3*t] = calculaEnergia(matrizesGlcm[t]);
      caracteristicas[(cont-1)/2][512+3*t+1] = calculaHomogeneidade(matrizesGlcm[t]);
      caracteristicas[(cont-1)/2][512+3*t+2] = calculaContraste(matrizesGlcm[t]);
    } else {
      caracteristicas[IMAGENS/2+cont/2][512+3*t] = calculaEnergia(matrizesGlcm[t]);
      caracteristicas[IMAGENS/2+cont/2][512+3*t+1] = calculaHomogeneidade(matrizesGlcm[t]);
      caracteristicas[IMAGENS/2+cont/2][512+3*t+2] = calculaContraste(matrizesGlcm[t]);
    }
  }

  for (i = 0; i < 8; i++) {
    for (j = 0; j < TAMCOD; j++) {
      free(matrizesGlcm[i][j]);
    }
    free(matrizesGlcm[i]);
  }
  free(matrizesGlcm);
}
//-------------------------------------------------------------------------
void selecionaImagensTreino(int *asfalto,int *grama,char *nomeArquivo,FILE *arq,int **matriz,int *contLine,int *contCol,int seletor){
  int cont=0,numeroAleatorio;
  char stringNumeroAleatorio[4];
  int pixel;
  char aux;
  if (seletor) {
    strcat(nomeArquivo,"grass/grass_");
    while(grama[cont]) {
      cont++;
    }
    numeroAleatorio = cont+1;
    grama[cont] = 1;
  } else {
    strcat(nomeArquivo,"asphalt/asphalt_");
    while(asfalto[cont]) {
      cont++;
    }
    numeroAleatorio = cont+1;
    asfalto[cont] = 1;
  }
  sprintf(stringNumeroAleatorio,"%02d",numeroAleatorio);
  strcat(nomeArquivo,stringNumeroAleatorio);
  strcat(nomeArquivo,".txt");
  if(arq = fopen(nomeArquivo,"r"),arq == NULL){
    printf("erro ao abrir o arquivo!\n");
    exit(1);
  }
  while(!feof(arq)){
    fscanf(arq, "%d%c",&pixel,&aux);
    if(aux == ';'){
      *contCol += 1;
    }
    else if(aux == '\n'){
      *contLine += 1;
    }
  }
  *contLine -= 1;
  *contCol = *contCol/(*contLine)+1;
  fclose(arq);
}
//-------------------------------------------------------------------------
