/*  Max Henrique Barbosa - 16/0047013
    Érico Maximiano - 16/0070287 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>



//-------------------- DECLARACAO DE FUNCOES ---------------------

int gerarNumeroAleatorio ();
int menorValor(int *,int ,int);
int transformaBinDecimal(int *);

double energia(int **);
double contraste(int **);
double homogeneidade(int **);

void selecionarGrama (int *, char *);
void ilbp(int **,int ,int ,double **, int);
void ilbpQuadrante(int **,int ,int ,double **,int);
void alocaMatriz(int **);
void rotacionaVetor(int *);
void normalizaVetor(double *,int);
void mediaPontos(double **,double *,double *);
void glcm(int **, int, int , double **, int);
void euclidiana(double **, double *, double *, int *, int *, int *);
void imagensParaTreino(int *,int *,char *, FILE *, int **, int *, int *, int);

//------------------------------ MAIN -----------------------------
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
int menorValor(int *vetor,int menor,int cont){
  int n;
  if (cont == 9) {
    return menor;
  } else {
    n = transformaBinDecimal(vetor);
    if (n < menor) {
      menor = n;
    }
    rotacionaVetor(vetor);
    return menorValor(vetor,menor,cont+1);
  }
}
//-------------------------------------------------------------------------
void ilbpQuadrante(int **vetorImagens,int linha,int coluna,double **aspectos,int aux){
  double total=0.0;
  int cont=0,minValue;
  int vetor[9];
  for (int i = linha-1; i <= linha+1; i++) {
    for (int j = coluna-1; j <= coluna+1; j++) {
      total += *(*(vetorImagens+i)+j);
      vetor[cont] = vetorImagens[i][j];
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
  minValue = menorValor(vetor,256,0);
  if (aux%2) {
    aspectos[(aux-1)/2][minValue]+=1;
  } else {
    aspectos[50/2+aux/2][minValue]+=1;
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
double contraste(int **vetorImagens){
  int i,j;
  double total=0.0;
  for (i = 0; i < 256; i++) {
    for (j = 0; j < 256; j++) {
      total += vetorImagens[i][j]*pow(i-j,2);
    }
  }
  return total;
}
//-------------------------------------------------------------------------
double homogeneidade(int **vetorImagens){
  int i,j;
  double total=0.0;
  for (i = 0; i < 256; i++) {
    for (j = 0; j < 256; j++) {
      total += vetorImagens[i][j]/(1+abs(i-j));
    }
  }
  return total;
}
//-------------------------------------------------------------------------
double energia(int **vetorImagens){
  int i,j;
  double total=0.0;
  for (i = 0; i < 256; i++) {
    for (j = 0; j < 256; j++) {
      total += pow(vetorImagens[i][j],2);
    }
  }
  return total;
}
//-------------------------------------------------------------------------
void glcm(int **vetorImagens,int linha,int coluna,double **aspectos,int cont){
  int ***matrizesGlcm;
  int i,j,t;

  if(matrizesGlcm = (int***)calloc(8,sizeof(int**)),matrizesGlcm == NULL){
    printf("alocação falhou!\n");
  }
	for (i = 0; i < 8; i++) {
    if(matrizesGlcm[i] = (int**)calloc(256,sizeof(int*)),matrizesGlcm[i] == NULL){
      printf("alocação falhou!\n");
    }
		for (j = 0; j < 256; j++) {
      if(matrizesGlcm[i][j] = (int*)calloc(256,sizeof(int)),matrizesGlcm[i][j] == NULL){
        printf("alocação falhou!\n");
      }
		}
	}

  for (t = 0; t < 8; t++) {
    for (i = 1; i < linha-1; i++) {
      for (j = 1; j < coluna-1; j++) {
        switch (t) {
          case 0:
            matrizesGlcm[t][vetorImagens[i][j]][vetorImagens[i-1][j-1]]++;
            break;
          case 1:
            matrizesGlcm[t][vetorImagens[i][j]][vetorImagens[i-1][j]]++;
            break;
          case 2:
            matrizesGlcm[t][vetorImagens[i][j]][vetorImagens[i-1][j+1]]++;
            break;
          case 3:
            matrizesGlcm[t][vetorImagens[i][j]][vetorImagens[i][j-1]]++;
            break;
          case 4:
            matrizesGlcm[t][vetorImagens[i][j]][vetorImagens[i][j+1]]++;
            break;
          case 5:
            matrizesGlcm[t][vetorImagens[i][j]][vetorImagens[i+1][j-1]]++;
            break;
          case 6:
            matrizesGlcm[t][vetorImagens[i][j]][vetorImagens[i+1][j]]++;
            break;
          case 7:
            matrizesGlcm[t][vetorImagens[i][j]][vetorImagens[i+1][j+1]]++;
        }
      }
    }
    if (cont%2) {
      aspectos[(cont-1)/2][512+3*t] = energia(matrizesGlcm[t]);
      aspectos[(cont-1)/2][512+3*t+1] = homogeneidade(matrizesGlcm[t]);
      aspectos[(cont-1)/2][512+3*t+2] = contraste(matrizesGlcm[t]);
    } else {
      aspectos[50/2+cont/2][512+3*t] = energia(matrizesGlcm[t]);
      aspectos[50/2+cont/2][512+3*t+1] = homogeneidade(matrizesGlcm[t]);
      aspectos[50/2+cont/2][512+3*t+2] = contraste(matrizesGlcm[t]);
    }
  }

  for (i = 0; i < 8; i++) {
    for (j = 0; j < 256; j++) {
      free(matrizesGlcm[i][j]);
    }
    free(matrizesGlcm[i]);
  }
  free(matrizesGlcm);
}
//-------------------------------------------------------------------------
void imagensParaTreino(int *asfalto,int *grama,char *nomeArquivo,FILE *arq,int **vetorImagens,int *linha,int *coluna,int seletor){
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
      *coluna += 1;
    }
    else if(aux == '\n'){
      *linha += 1;
    }
  }
  *linha -= 1;
  *coluna = *coluna/(*linha)+1;
  fclose(arq);
}
//-------------------------------------------------------------------------
