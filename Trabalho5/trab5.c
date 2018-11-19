/*  Max Henrique Barbosa - 16/0047013
    Érico Maximiano Bandeira - 16/0070287 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arvore.c"

void liberaArvore(No *raiz);
No *selecionaArquivo();
void limpaBuff();
void continuar();

int main(){
  char select;
  No *raiz;
  int valor;
  raiz = selecionaArquivo();
  do
  {
    do{
      system("clear");
      printf("\t||=======================================================||\n");
      printf("\t|| 1 - Mostrar arvore                                    ||\n");
      printf("\t|| 2 - Verificar se a arvore é cheia                     ||\n");
      printf("\t|| 3 - Procurar valor na arvore                          ||\n");
      printf("\t|| 4 - Verificar altura da arvore                        ||\n");
      printf("\t|| 5 - Remover valor da arvore                           ||\n");
      printf("\t|| 6 - Mostrar valores da arvore usando algoritmos       ||\n");
      printf("\t|| 7 - Balancear arvore                                  ||\n");
      printf("\t|| 0 - Sair                                              ||\n");
      printf("\t||=======================================================||\n");
      scanf("%c", &select);
      limpaBuff();
    } while (select < '0' || select > '7');
    
    system("clear");
    
    switch (select){
    case '1':
      showTree(raiz);
      break;
    case '2':
      isFull(raiz);
      break;
    case '3':
      printf("Digite o valor que deseja procurar na arvore: \n");
      showTree(raiz);
      scanf("%d", &valor);
      getchar();
      searchValue(raiz, valor);
      break;
    case '4':
      printf("altura da arvore: %d\n", getHeight(raiz));
      break;
    case '5':
      printf("Digite o valor que deseja remover da arvore: \n");
      showTree(raiz);
      scanf("%d", &valor);
      getchar();
      raiz = removeValue(raiz, valor);
      break;
    case '6':
      do {
        printf("\t||================||\n");
        printf("\t|| 1 - InOrder:   ||\n");
        printf("\t|| 2 - PreOrder:  ||\n");
        printf("\t|| 3 - PostOrder: ||\n");
        printf("\t||================||\n");
        scanf("%c", &select);
        limpaBuff();
      } while (select < '1' || select > '3');

      system("clear");     

      switch (select){
      case '1':
        printInOrder(raiz);
        break;
      case '2':
        printPreOrder(raiz);
        break;
      case '3':
        printPostOrder(raiz);
        break;
      }
      break;
    case '7':
      raiz = balanceTree(raiz);
      showTree(raiz);
      break;
    case '0':
      liberaArvore(raiz);
    }
    if (select != '0')
    {
      continuar();
    }
  } while (select != '0');
  return 0;
}
////////////////////////////////////////////////////////////////////////////////
No *selecionaArquivo()
{
  char arquivo;
  static char nomeArquivo[30];
  No *raiz;
  do
  {
    system("clear");
    printf("\t||=================================||\n");
    printf("\t||Selecione um dos arquivos abaixo.||\n");
    printf("\t|| 1 - bst1.txt                    ||\n");
    printf("\t|| 2 - bst2.txt                    ||\n");
    printf("\t|| 3 - bst3.txt                    ||\n");
    printf("\t|| 4 - bst4.txt                    ||\n");
    printf("\t|| 5 - bst5.txt                    ||\n");
    printf("\t|| 6 - bst6.txt                    ||\n");
    printf("\t||=================================||\n");
    scanf("%c", &arquivo);
    limpaBuff();
  } while (arquivo < '1' || arquivo > '6');

  strcat(nomeArquivo, "BSTs/bst");
  nomeArquivo[strlen(nomeArquivo)] = arquivo;
  strcat(nomeArquivo, ".txt");
  // printf("%s", nomeArquivo);
  raiz = loadTreeFromFile(nomeArquivo);

  return raiz;
}
////////////////////////////////////////////////////////////////////////////////
void liberaArvore(No *raiz){
  if (raiz != NULL){
    liberaArvore(raiz->esquerda);
    liberaArvore(raiz->direita);
    free(raiz);
  }
}
////////////////////////////////////////////////////////////////////////////////
void limpaBuff()
{
  char c;
  do
  {
    c = getchar();
  } while (c != '\n');
}
////////////////////////////////////////////////////////////////////////////////
void continuar()
{
  char c;
  printf("\nAperte enter para voltar ao menu\n");
  do
  {
    c = getchar();
  } while (c != '\n');
}
