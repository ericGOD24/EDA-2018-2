/*
  Érico Bandeira - 16/0070287
  Max Henrique Barbosa - 16/0047013
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX 10

//=========================================================
//DECLARACAO DE FUNCOES

void fneuronio(double *, double *, double, int *);

//=========================================================

int main(int argc, char const *argv[]) {
  double X[MAX], W[MAX];
  double T;
  int i, result;

  printf("Escreva o valor do limiar T\n");
  scanf("%lf", &T);

  printf("Escreva dez valores para o vetor de entrada.\n\n");
  for( i = 0 ; i < MAX ; i++){
    scanf("%lf", &X[i]);
  }

  printf("Escreva dez valores para o vetor de pesos.\n\n");
  for( i = 0 ; i < MAX ; i++){
    scanf("%lf", &W[i]);
  }

  fneuronio(X, W, T, &result);

  if(!(result)){
    printf("\n Neuronio inibido!\n\n");
  }
  else{
    printf("\n Neuronio ativado!\n");
    printf("\n\n");
  }

  return 0;
}

void fneuronio(double *X, double *W, double T, int *result) {
  int k;
  double SOMAP = 0;

    for(k = 0; k < MAX; k++){
      SOMAP += (X[k] * W[k]);
    }

    if (SOMAP <= T){
      *result = 0;
    }
    else{
      *result = 1;
    }
}
