/*  Max Henrique Barbosa - 16/0047013
    Érico Maximiano - 16/0070287 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define ENTRADA 536
#define LEARNRATE 1
//------------------------------------------------------------------------------
typedef struct neuronio{
  double *peso;
  double somatorio;
  double b;
  double saida;
  double gradiente;
} Neuronio;

//------------------------------------------------------------------------------

Neuronio *novoNeuronio();

double calculoNucleo(Neuronio *n, double *);
double ativacaoLogistica(double *);
double entradasXpesos(double *, double *, double);
double erroQuadratico (double *, Neuronio *n);

void backPropagation (double *, int, double **, double **, Neuronio * n, Neuronio **k, Neuronio ** l);
void ajustePeso(Neuronio *n, Neuronio **k, Neuronio **l, double **, double **, int);
void ajusteB(Neuronio *n, Neuronio **k, Neuronio **l, double **, double **, int);
void pesoAleatorio(Neuronio *n);
void bAleatorio(Neuronio *n);

//------------------------------------------------------------------------------
int main(int argc, char const *argv[]){

  srand(time(NULL));
  int numCamadaOculta = atoi(argv[1]);

  printf("\n========================================================\n");
  printf("||\tNumero de neuronios na camada oculta = %d      ||\n", numCamadaOculta);
  printf("========================================================\n");

  double **matrizDeEntradas = (double **)calloc(100, sizeof(double *));

  for (int i = 0; i < 100; i++){
    matrizDeEntradas[i] = (double *)calloc(ENTRADA + 1, sizeof(double));
  }

  FILE *arquivo = NULL;
  if (arquivo = fopen("vetoresNormalizados.txt", "r"), arquivo == NULL){
    printf("Erro ao abrir o arquivo!\n");
    exit(1);
  }

  for (int i = 0; i < 100; i++){
    if ((i < 25) || ((i > 49) && (i < 75))){
      matrizDeEntradas[i][0] = 1;
    }

    for (int j = 1; j < ENTRADA + 1; j++){
      fscanf(arquivo, " %lf", &matrizDeEntradas[i][j]);
    }
  }

  Neuronio **camadaEntrada = (Neuronio **)calloc(ENTRADA, sizeof(Neuronio*));
  Neuronio **camadaOculta = (Neuronio **)calloc(numCamadaOculta, sizeof(Neuronio*));
  Neuronio *camadaSaida = novoNeuronio();

  pesoAleatorio(camadaSaida);
  bAleatorio(camadaSaida);

  for (int i = 0; i < ENTRADA; i++){
    camadaEntrada[i] = novoNeuronio();
    pesoAleatorio(camadaEntrada[i]);
    bAleatorio(camadaEntrada[i]);
  }

  for (int i = 0; i < numCamadaOculta; i++){
    camadaOculta[i] = novoNeuronio();
    pesoAleatorio(camadaOculta[i]);
    bAleatorio(camadaOculta[i]);
  }

  double treinoGrama[25][ENTRADA + 1];
  double treinoAsfalto[25][ENTRADA + 1];
  static int visitados[50];
  int indice;

  for (int i = 0; i < 25; i++){
    do{
        indice = rand() % (50);
      }while(visitados[indice] == 1);
    visitados[indice] = 1;

    for (int j = 0; j < ENTRADA + 1; j++){
      if (indice < 25){
        treinoGrama[i][j] = matrizDeEntradas[indice][j];
        treinoAsfalto[i][j] = matrizDeEntradas[indice + 25][j];
      }

      else{
        treinoGrama[i][j] = matrizDeEntradas[indice + 25][j];
        treinoAsfalto[i][j] = matrizDeEntradas[indice + 50][j];
      }
    }
  }

  double resultadoEntrada[50][ENTRADA];
  // double **resultadoEntrada = (double **)calloc(50, sizeof(double *));
  // for (int i = 0; i < 50; i++){
  //   resultadoEntrada[i] = (double *)calloc(ENTRADA, sizeof(double));
  // }

   for(int i = 0; i < 50; i++){
       for(int j = 0; j < ENTRADA; j++){ 
         if(i < 25){
           resultadoEntrada[i][j] = calculoNucleo(camadaEntrada[j], treinoGrama[i]);
         }
         else{
           resultadoEntrada[i][j] = calculoNucleo(camadaEntrada[j], treinoAsfalto[i]);
         }
       }
   }

   double resultadoOculta[50][numCamadaOculta];
  //  double **resultadoOculta = (double **)calloc(50, sizeof(double *));
  //  for (int i = 0; i < 50; i++){
  //    resultadoOculta[i] = (double *)calloc(numCamadaOculta, sizeof(double));
  //  }

   for (int i = 0; i < 50; i++){
     for (int j = 0; j < numCamadaOculta; j++){
       resultadoOculta[i][j] = calculoNucleo(camadaOculta[j], resultadoEntrada[i]);
     }
  }

  double resultadoSaida [50];
  // double *resultadoSaida = (double *)calloc(50, sizeof(double));

  for (int i = 0; i < 50; i++){
    resultadoSaida[i] = calculoNucleo(camadaSaida, resultadoOculta[i]);
  }
  
  
  for (int i = 0; i < 50; i++){
    if (i<25) {
      printf("resultado grama: %lf\n", resultadoSaida[i]);
    }
    else{
      printf("resultado asfalto: %lf\n", resultadoSaida[i]);
    }
  }

  // backPropagation (resultadoSaida, numCamadaOculta, resultadoOculta, resultadoEntrada, camadaSaida, camadaOculta, camadaEntrada);

  // free(resultadoSaida);

  // for (int i = 0; i < 50; i++){
  //   free(resultadoOculta[i]);
  // }
  // free(resultadoOculta);

  // for (int i = 0; i < 50; i++){
  //   free(resultadoEntrada[i]);
  // }
  // free(resultadoEntrada);

  for (int i = 0; i < 100; i++){
    free(matrizDeEntradas[i]);
  }
  free(matrizDeEntradas);

  for (int i = 0; i < ENTRADA; i++){
    free(camadaEntrada[i]);
  }
  free(camadaEntrada);

  for (int i = 0; i < numCamadaOculta; i++){
    free(camadaOculta[i]);
  }
  free(camadaOculta);

  free(camadaSaida);
  fclose(arquivo);

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

  n->somatorio = entradasXpesos(p, n->peso, n->b);
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
double entradasXpesos (double *p, double *peso, double b){
  double somatorio;
  
  for (int i = 0; i < ENTRADA; i++){ 
    somatorio += (p[i] * peso[i]);
  }
  
  return somatorio + b;
}
//------------------------------------------------------------------------------
void pesoAleatorio(Neuronio *n){
    n->peso = (double *)calloc(ENTRADA, sizeof(double)); 
  
    for (int i = 0; i < ENTRADA; i++){
      int aleatorio = (rand() % 32767) - 16384;
      n->peso[i] = aleatorio;
    }
  }
//------------------------------------------------------------------------------
void bAleatorio(Neuronio *n){
  n->b = (rand() % 32767) - 16384;
}
//------------------------------------------------------------------------------
double erroQuadratico (double *resultadoSaida, Neuronio * n){
  double erroCiclo[50];
  double gradiente;
  double totalErro = 0;

  for (int i = 0; i < 50; i++){
    erroCiclo[i] = pow(0.2 - resultadoSaida[i], 2);
    totalErro += erroCiclo[i];
  }

  return ((1 / n->somatorio) * totalErro);
}
//------------------------------------------------------------------------------
void backPropagation (double *resultadoSaida, int numCamadaOculta, double **resultadoOculta, double **resultadoEntrada, Neuronio * n, Neuronio **k, Neuronio ** l){
  double erro = erroQuadratico(resultadoSaida, n);
  double totalDerivadaAtivacao = 0;
  double totalGradienteOculta = 0;
  double somaGradienteXpeso = 0;

  // n = nó de saida, k = nó da camada oculta, l = nó camada entrada

  //gradiente camada saida
  for (int i = 0; i < 50; i++){
    totalDerivadaAtivacao += (exp(resultadoSaida[i])) / pow(exp(resultadoSaida[i]) - 1, 2);
  }

  n->gradiente = totalDerivadaAtivacao * erro;

  //gradiente camada oculta

  for (int i = 0; i < numCamadaOculta; i++){
    somaGradienteXpeso += (n->gradiente * n->peso[i]);
  }
  
  for(int i = 0; i < 50; i++){
    totalDerivadaAtivacao = 0;
     for (int j = 0; j < numCamadaOculta; j++){
     totalDerivadaAtivacao += (exp(resultadoOculta[i][j])) / pow(exp(resultadoOculta[i][j]) - 1, 2);
    }
    k[i]->gradiente = totalDerivadaAtivacao * somaGradienteXpeso;
  }
    
  //gradiente camada entrada

  somaGradienteXpeso = 0;

  for (int i = 0; i < 50; i++){
    for (int j = 0; j < ENTRADA; j++){
      somaGradienteXpeso += (k[i]->gradiente * k[i]->peso[j]);
    }
  }
  
  for(int i = 0; i < 50; i++){
    totalDerivadaAtivacao = 0;
     for (int j = 0; j < ENTRADA; j++){
     totalDerivadaAtivacao += (exp(resultadoEntrada[i][j])) / pow(exp(resultadoEntrada[i][j]) - 1, 2);
    }
    l[i]->gradiente = totalDerivadaAtivacao * somaGradienteXpeso;
  }
}
//------------------------------------------------------------------------------
void ajustePeso(Neuronio *n, Neuronio **k, Neuronio **l, double **resultadoEntrada, double **resultadoOculta, int numCamadaOculta){
  //Peso [i](atual) = Peso [i](atual) + LEARNRATE * resultado da camada anterior * gradiente (atual)
  
  //Entrada
  
  for (int i = 0; i < 50; i++){
     for (int j = 0; j < ENTRADA; j++){
      l[i]->peso[j] = l[i]->peso[j] + (LEARNRATE * l[i]->gradiente);
    }
  }
  
  //Oculta
  
  for (int i = 0; i < 50; i++){
    for (int j = 0; j < ENTRADA; j++){
      k[i]->peso[j] = k[i]->peso[j] + (LEARNRATE * k[i]->gradiente * resultadoEntrada[i][j]);
    }
  }

  //Saida
  for (int i = 0; i < numCamadaOculta; i++){
    n->peso[i] = n->peso[i] + (LEARNRATE * n->gradiente * resultadoOculta[0][i]);
  }
}
//------------------------------------------------------------------------------
void ajusteB(Neuronio *n, Neuronio **k, Neuronio **l, double **resultadoEntrada, double **resultadoOculta, int numCamadaOculta){
  //b [i](atual) = Peso [i](atual) + LEARNRATE * gradiente (atual)

  //Entrada
  
  for (int i = 0; i < 50; i++){
    for (int j = 0; j < ENTRADA; j++){
      l[i]->peso[j] = l[i]->peso[j] + (LEARNRATE * l[i]->gradiente);
    }
  }
  
  //Oculta
  
  for (int i = 0; i < 50; i++){
    for (int j = 0; j < ENTRADA; j++){
      k[i]->peso[j] = k[i]->peso[j] + (LEARNRATE * k[i]->gradiente * resultadoEntrada[i][j]);
    }
  }

  //Saida
  for (int i = 0; i < numCamadaOculta; i++){
    n->peso[i] = n->peso[i] + (LEARNRATE * n->gradiente * resultadoOculta[0][i]);
  }
}
//------------------------------------------------------------------------------
