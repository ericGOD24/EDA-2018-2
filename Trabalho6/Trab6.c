/*  Max Henrique Barbosa - 16/0047013
    Érico Maximiano - 16/0070287 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define ENTRADA 536

//------------------------------------------------------------------------------
typedef struct neuronio{
  double *peso;
  double somatorio;
  double escalar;
  double saida;
} Neuronio;

//------------------------------------------------------------------------------

Neuronio *novoNeuronio();

double calculoNucleo(Neuronio *n, double *);
double ativacaoLogistica(double *);
double entradasXpesos(double *, double *, double);

void pesoAleatorio(Neuronio *n);
void escalarAleatorio(Neuronio *n);

//------------------------------------------------------------------------------
int main(int argc, char const *argv[]){

  srand(time(NULL));
  int numCamadaOculta = atoi(argv[1]);
  double **vetorDeEntrada = (double **)calloc(100, sizeof(double *));

  printf("\n--------------------------------------------------------\n");
  printf("\tNumero de neuronios na camada oculta = %d\n", numCamadaOculta);
  printf("--------------------------------------------------------\n");

  for (int i = 0; i < 100; i++)
  {
    vetorDeEntrada[i] = (double *)calloc(ENTRADA + 1, sizeof(double));
  }

  FILE *arquivo = NULL;
  if (arquivo = fopen("vetoresNormalizados.txt", "r"), arquivo == NULL)
  {
    printf("Erro ao abrir o arquivo!\n");
    exit(1);
  }

  for (int i = 0; i < 100; i++)
  {
    if ((i < 25) || ((i > 49) && (i < 75)))
    {
      vetorDeEntrada[i][0] = 1;
    }

    for (int j = 1; j < ENTRADA + 1; j++)
    {
      fscanf(arquivo, "%lf", &vetorDeEntrada[i][j]);
    }
  }

  Neuronio **camadaEntrada = (Neuronio **)calloc(ENTRADA, sizeof(Neuronio *));
  Neuronio **camadaOculta = (Neuronio **)calloc(numCamadaOculta, sizeof(Neuronio *));
  Neuronio *camadaSaida = novoNeuronio();

  for (int i = 0; i < ENTRADA; i++)
  {
    camadaEntrada[i] = novoNeuronio();
    pesoAleatorio(camadaEntrada[i]);
    escalarAleatorio(camadaEntrada[i]);
  }

  for (int i = 0; i < numCamadaOculta; i++)
  {
    camadaOculta[i] = novoNeuronio();
    pesoAleatorio(camadaOculta[i]);
    escalarAleatorio(camadaOculta[i]);
  }

  double treinoGrama[25][ENTRADA + 1];
  double treinoAsfalto[25][ENTRADA + 1];

  for (int i = 0; i < 25; i++)
  {
    int indice = rand() % (50);

    for (int j = 0; j < ENTRADA + 1; j++)
    {
      if (indice < 25)
      {
        treinoGrama[i][j] = vetorDeEntrada[indice][j];
        treinoAsfalto[i][j] = vetorDeEntrada[indice + 25][j];
      }

      else
      {
        treinoGrama[i][j] = vetorDeEntrada[indice + 25][j];
        treinoAsfalto[i][j] = vetorDeEntrada[indice + 50][j];
      }
    }
  }

  double *erros = (double *)calloc(50, sizeof(double)); //vetor de erros com 50 posicoes
  double erro_geral = 1;                                //erro geral = sum(erros[i]^2)/50
  double limiar_do_erro_geral = 0.2;                    //erro_geral deve ser = ou menor que isso
  int numero_de_epocas = 0;                             //vai de 0 a 1000, ou de 0 a x se erro_geral<=limiar_do_erro_geral
  double taxa_de_aprendizagem = 0.45;                   //taxa de aprendizagem para a rede neural
  //treinar a rede neural
  //do{

  //  numero_de_epocas+=1;
  //}while(numero_de_epocas<=1000 || erro_geral>limiar_do_erro_geral);
  //-----------------------------------------------------//

  for (int i = 0; i < 100; i++){
    free(vetorDeEntrada[i]);
  }

  for (int i = 0; i < ENTRADA; i++){
    free(camadaEntrada[i]);
  }

  for (int i = 0; i < numCamadaOculta; i++){
    free(camadaOculta[i]);
  }

  free(camadaSaida);
  free(erros);
  
  return 0;
}
//------------------------------------------------------------------------------
Neuronio *novoNeuronio(){
  Neuronio *novo = NULL;

  if (novo = (Neuronio *)calloc(1, sizeof(Neuronio)), novo == NULL){
    printf("Erro ao criar novo neurônio\n\n");
    return NULL;
  }
  return novo;
}
//------------------------------------------------------------------------------
double calculoNucleo(Neuronio *n, double *p){

  n->somatorio = entradasXpesos(p, n->peso, n->escalar);
  n->saida = ativacaoLogistica(&n->somatorio);
  
  return n->saida;
}
//------------------------------------------------------------------------------
double ativacaoLogistica(double *somatorio){
  double f;

  f = 1.0/(1.0 + exp(-(*somatorio))); 

  return f;
}
//------------------------------------------------------------------------------
double entradasXpesos (double *p, double *peso, double escalar){
  double somatorio;
  
  for (int i = 0; i < ENTRADA; i++){ 
    somatorio += (p[i] * peso[i]);
  }
  
  return somatorio + escalar;
}
//------------------------------------------------------------------------------
void pesoAleatorio(Neuronio *n){

    n->peso = (double *)calloc(ENTRADA, sizeof(double)); 

    for (int i = 0; i < ENTRADA; i++){
      int aleatorio = (rand() % 32767) - 16384;
      n->peso[i] = aleatorio;
    }
  }

void escalarAleatorio(Neuronio *n){
  n->escalar = (rand() % 32767) - 16384;
}
