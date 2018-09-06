#include <stdio.h>
#include <stdlib.h>
#define MAX 10

//Funções
void recebe_notas (double *, int, int *);
void conta_notas (int *, int, int *, int *);
int percent_aprov (int *, int *, double *, double *);

//Main
int main() {

  double NOTAS[MAX];
  int i, j, APR[MAX];
  int aprovados, reprovados;
  double percentAprovados, percentReprovados;

  printf("Digite a nota de %d alunos: \n", MAX);
  for(i = 0; i < MAX; i++){
    scanf("%lf", &NOTAS[i]);
    if(NOTAS[i] < 0 || NOTAS[i] > 10){
      while(NOTAS[i] < 0 || NOTAS[i] > 10){
        printf("Valor invalido. Insira novamente: \n");
        scanf("%lf", &NOTAS[i]);
      }
    }
  }


  recebe_notas(NOTAS, MAX, APR);
  conta_notas(APR, MAX, &aprovados, &reprovados);
  percent_aprov(&aprovados, &reprovados, &percentAprovados, &percentReprovados);

  printf("\nAprovados: %d\n", aprovados);
  printf("Reprovados: %d\n", reprovados);
  printf("Porcentagem de Aprovados: %.1lf\% \n", percentAprovados);
  printf("Porcentagem Reprovados: %.1lf\% \n", percentReprovados);

  if(percent_aprov(&aprovados, &reprovados, &percentAprovados, &percentReprovados))
    printf("Mais da metade da turma foi aprovada! \n\n");

  return 0;
}

//Funções again
void recebe_notas (double *NOTAS, int Num, int *APR){
  int k;

  for(k = 0 ; k < Num ; k++){
    if(NOTAS[k] >= 6){
      APR[k] = 1;
    }
    else{
      APR[k] = 0;
    }
  }
}

void conta_notas (int *APR, int Num, int *aprovados, int *reprovados){
  int j = 0, contAprovados = 0, contReprovados = 0;

  for(j = 0; j < Num; ++j){
    if (!(APR[j])){
      contReprovados ++;
    }
    else{
      contAprovados ++;
    }
  }

  *aprovados = contAprovados;
  *reprovados = contReprovados;
}


int percent_aprov (int *aprovados, int *reprovados, double *percentAprovados, double *percentReprovados){
  int aprov, reprov;
  aprov = *aprovados;
  reprov = *reprovados;

  *percentAprovados = ((aprov*100)/MAX);
  *percentReprovados = ((reprov*100)/MAX);

  if(*percentAprovados > 50)
    return 1;
  else
   return 0;
}
