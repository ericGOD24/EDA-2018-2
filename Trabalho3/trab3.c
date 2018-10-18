#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct contato {
  char name[101];
  char cel[11];
  char adress[101];
  int cep;
  char date[11];

  struct contato *prox;
  struct contato *ante;
} Contato;



//---------------------------------------------------------------------
int main() {
  FILE *fp;
  Contato *list;
  int sel;
  char c;

  if(list = (Contato*)malloc(sizeof(Contato)), list == NULL){
    printf("Erro ao alocar!\n");
  }

  list = readFile();
  system("clear");



  return 0;
}
//-----------------------------------------------------------------------