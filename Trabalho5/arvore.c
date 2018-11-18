/*  Max Henrique Barbosa - 16/0047013
    Érico Maximiano Bandeira - 16/0070287 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

No *loadTreeFromFile(char arquivo[]){
  FILE *arq;
  int num;
  No *aux;
  No *raiz = NULL;
  
  if (arq = fopen(arquivo, "a+"), arq == NULL){
    printf("Erro, nao foi possivel abrir o arquivo!\n");
    exit(1);
  }
  
  if (!feof(arq)){
    fscanf(arq, " %d ", &num);
    if (raiz = (No *)malloc(sizeof(No)), raiz == NULL){
      printf("Falha na alocacao!\n");
    }
    raiz->num = num;
    raiz->esquerda = NULL;
    raiz->direita = NULL;
  }
  
  while (!feof(arq)){
    fscanf(arq, " %d ", &num);
    if (aux = (No *)malloc(sizeof(No)), aux == NULL){
      printf("Falha na alocacao!\n");
    }
    aux->num = num;
    aux->direita = NULL;
    aux->esquerda = NULL;
    insereNo(raiz, aux);
  }
  fclose(arq);
  return raiz;
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void insereNo(No *raiz, No *aux)
{
  if (raiz->num < aux->num)
  {
    if (raiz->dir == NULL)
    {
      raiz->dir = aux;
    }
    else
    {
      insereNo(raiz->dir, aux);
    }
  }
  else
  {
    if (raiz->esquerda == NULL)
    {
      raiz->esquerda = aux;
    }
    else
    {
      insereNo(raiz->esquerda, aux);
    }
  }
}
//------------------------------------------------------------------------------
void isFull(No *raiz)
{
  int altura = getHeight(raiz);
  int elementosMax = (pow(2, altura)) - 1;
  int elementos = 0;
  contaElementos(raiz, &elementos);
  if (elementos == elementosMax)
    printf("A arvore e cheia\n");
  else
    printf("A arvore nao e cheia\n");
}
//------------------------------------------------------------------------------
void contaElementos(No *raiz, int *elementos)
{
  if (raiz == NULL);
  else
  {
    *elementos = *elementos + 1;
    contaElementos(raiz->esq, elementos);
    contaElementos(raiz->dir, elementos);
  }
}
//------------------------------------------------------------------------------
No *balanceTree(No *raiz){
  if (raiz == NULL){
    printf("arvore esta vazia\n");
    return raiz;
  }

  if (!verificaBalanceamento(raiz)){
    
    do{
      raiz = rotaciona(raiz, NULL, raiz);
    } while (!verificaBalanceamento(raiz));
  }
  
  else{
    printf("arvore esta balanceada\n");
  }
  return raiz;
}
//------------------------------------------------------------------------------
No *rodaDir(No *raiz, No *pai, No *raizReal)
{
  No *aux = raiz->dir;
  if (pai != NULL)
  {
    if (pai->esquerda == raiz)
    {
      pai->esquerda = aux;
    }
    else
    {
      pai->dir = aux;
    }
    raiz->dir = aux->esquerda;
    aux->esquerda = raiz;
  }
  else
  {
    raiz->dir = aux->esquerda;
    aux->esquerda = raiz;
    raizReal = aux;
  }

  return raizReal;
}
//------------------------------------------------------------------------------
No *rodaEsq(No *raiz, No *pai, No *raizReal)
{
  No *aux = raiz->esquerda;
  if (pai != NULL)
  {
    if (pai->esquerda == raiz)
    {
      pai->esquerda = aux;
    }
    else
    {
      pai->dir = aux;
    }
    raiz->esquerda = aux->dir;
    aux->dir = raiz;
  }
  else
  {
    raiz->esquerda = aux->dir;
    aux->dir = raiz;
    raizReal = aux;
  }
  return raizReal;
}
//------------------------------------------------------------------------------
No *rotaciona(No *raiz, No *pai, No *raizReal)
{
  if (raiz != NULL)
  {
    if (!verificaBalanceamento(raiz))
    {
      raizReal = rotaciona(raiz->esquerda, raiz, raizReal);
      if (verificaBalanceamento(raiz))
      {
        return raizReal;
      }
      raizReal = rotaciona(raiz->dir, raiz, raizReal);
      if (verificaBalanceamento(raiz))
      {
        return raizReal;
      }
      if (getHeight(raiz->esquerda) > getHeight(raiz->dir))
      {
        raizReal = rodaEsq(raiz, pai, raizReal);
      }
      else
      {
        raizReal = rodaDir(raiz, pai, raizReal);
      }
    }
  }
  return raizReal;
}
//------------------------------------------------------------------------------
int verificaBalanceamento(No *raiz){
  int dif;
  if (raiz != NULL){
    dif = getHeight(raiz->esquerda) - getHeight(raiz->dir);
    if (dif < -1 || dif > 1)
    {
      return 0;
    }
    else
    {
      return verificaBalanceamento(raiz->esquerda) * verificaBalanceamento(raiz->dir);
    }
  }
  return 1;
}
//------------------------------------------------------------------------------
No *removeValue(No *raiz, int num)
{
  No *pai = NULL, *aux = raiz;
  while (aux != NULL)
  {
    if (aux->num == num)
    {
      break;
    }
    pai = aux;
    if (aux->num < num)
    {
      aux = pai->dir;
    }
    else
    {
      aux = pai->esquerda;
    }
  }
  if (aux == NULL)
  {
    printf("Valor não encontrado\n");
  }
  else
  {
    if (pai == NULL)
    {
      raiz = removeRaiz(raiz);
    }
    else
    {
      aux = verificaValor(aux, pai);
      free(aux);
    }
    printf("\nValor removido\n\n");
    showTree(raiz);
  }
  return raiz;
}

//------------------------------------------------------------------------------
No *removeRaiz(No *raiz){
  No *aux;
  if (raiz->dir != NULL || raiz->esquerda != NULL){
    if (raiz->dir != NULL && raiz->esquerda != NULL){
      aux = procuraSucessor(raiz);
      free(aux);
      return raiz;
    }
    
    else{
      if (raiz->dir != NULL){
        aux = raiz->dir;
        free(raiz);
        return aux;
      }
      
      else{
        aux = raiz->esquerda;
        free(raiz);
        return aux;
      }
    }
  }
  
  else{
    free(raiz);
    return NULL;
  }
}
//------------------------------------------------------------------------------
No *verificaValor(No *raiz, No *pai){
  if (raiz->dir != NULL || raiz->esquerda != NULL){
    if (raiz->dir != NULL && raiz->esquerda != NULL){
      return procuraSucessor(raiz);
    }
    
    else{
      if (raiz->dir != NULL){
        if (pai->dir == raiz){
          pai->dir = raiz->dir;
          return raiz;
        }
        
        else{
          pai->esquerda = raiz->dir;
          return raiz;
        }
      }
      
      else{
        if (pai->dir == raiz){
          pai->dir = raiz->esquerda;
          return raiz;
        }
        
        else{
          pai->esquerda = raiz->esquerda;
          return raiz;
        }
      }
    }
  }
  
  else{
    if (pai->num < raiz->num){
      pai->dir = NULL;
    }
    else{
      pai->esquerda = NULL;
    }
    return raiz;
  }
}
//------------------------------------------------------------------------------
No *procuraSucessor(No *raiz)
{
  No *sucessor, *pai, *aux;
  int num;
  
  sucessor = raiz->dir;
  pai = raiz;
  
  while (sucessor->esquerda != NULL){
    pai = sucessor;
    sucessor = pai->esquerda;
  }
  num = sucessor->num;
  aux = verificaValor(sucessor, pai);
  raiz->num = num;
  return aux;
}
//------------------------------------------------------------------------------
int getHeight(No *raiz){
  int alturaEsquerda, alturaDireita;

  if (raiz == NULL)
    return 0;

  alturaEsquerda = getHeight(raiz->esq);
  alturaDireita = getHeight(raiz->dir);

  if (alturaEsquerda > alturaDireita)
    return (alturaEsquerda + 1);
  else
    return (alturaDireita + 1);
}
//------------------------------------------------------------------------------
void printPostOrder(No *raiz)
{
  if (raiz != NULL)
  {
    printPostOrder(raiz->esquerda);
    printPostOrder(raiz->dir);
    printf("%d ", raiz->num);
  }
}
//------------------------------------------------------------------------------
void printPreOrder(No *raiz)
{
  if (raiz != NULL)
  {
    printf("%d ", raiz->num);
    printPreOrder(raiz->esquerda);
    printPreOrder(raiz->dir);
  }
}
//------------------------------------------------------------------------------
void printInOrder(No *raiz)
{
  if (raiz != NULL)
  {
    printInOrder(raiz->esquerda);
    printf("%d ", raiz->num);
    printInOrder(raiz->dir);
  }
}
//------------------------------------------------------------------------------
void searchValue(No *raiz, int num){
  int nivel = 1;
  
  No *pai = NULL, *irmao = NULL;
  
  while (raiz != NULL){
    if (raiz->num == num){
      break;
    }
    
    nivel++;
    pai = raiz;
    
    if (raiz->num > num){
      irmao = raiz->direita;
      raiz = pai->esquerda;
    }
   
    else{
      irmao = raiz->esquerda;
      raiz = pai->direita;
    }
  }
  
  if (raiz == NULL){
    printf("Valor não encontrado\n");
  }
  
  else{
    printf("Nivel : %d\n", nivel);
    if (pai != NULL){
      printf("Pai : %d\n", pai->num);
    }
    
    if (irmao != NULL){
      printf("Irmão : %d\n", irmao->num);
    }
  }
}
//------------------------------------------------------------------------------
void showTree(No *raiz)
{
  if (raiz == NULL)
  {
    return;
  }
  int height = getHeight(raiz);
  int *retira;
  retira = (int *)calloc((int)pow(2, height) - 1, sizeof(int));
  if (retira == NULL)
  {
    puts("Alocação Falhou!");
    exit(1);
  }
  int **matrixTree = (int **)calloc(height, sizeof(int *));
  if (matrixTree == NULL)
  {
    puts("Alocação Falhou!");
    exit(1);
  }
  for (int i = 0; i < (height); i++)
  {
    *(matrixTree + i) = (int *)calloc(pow(2, height) - 1, sizeof(int));
    if (*(matrixTree + i) == NULL)
    {
      puts("Alocação Falhou!");
      exit(1);
    }
  }

  char **matrixTreeChar = (char **)calloc(height - 1, sizeof(char *));
  if (matrixTreeChar == NULL)
  {
    puts("Alocação Falhou!");
    exit(1);
  }
  for (int i = 0; i < (height - 1); i++)
  {
    *(matrixTreeChar + i) = (char *)calloc(pow(2, height) - 1, sizeof(char));
    if (*(matrixTreeChar + i) == NULL)
    {
      puts("Alocação Falhou!");
      exit(1);
    }
  }

  for (int i = 0; i < height - 1; i++)
  {
    for (int j = 0; j < pow(2, height) - 1; j++)
    {
      matrixTreeChar[i][j] = ' ';
    }
  }

  encheMatriz(matrixTree, matrixTreeChar, raiz, height, 0, (pow(2, height) - 1) / 2);

  retiraEspacos(matrixTreeChar, height, retira);

  mostraMatriz(matrixTree, matrixTreeChar, height, retira);

  for (int i = 0; i < height; i++)
    free(*(matrixTree + i));

  free(matrixTree);

  for (int i = 0; i < height - 1; i++)
    free(*(matrixTreeChar + i));

  free(matrixTreeChar);
}
//------------------------------------------------------------------------------
void retiraEspacos(char **matrixTreeChar, int height, int *retira)
{
  for (int j = 0; j < pow(2, height) - 1; j++)
  {
    for (int i = 0; i < height - 1; i++)
    {
      if (matrixTreeChar[i][j] == '/' || matrixTreeChar[i][j] == '\\')
      {
        retira[j] = 1;
      }
    }
  }
  int aux = (pow(2, height) - 1) / 2;
  retira[aux] = 1;
}
//------------------------------------------------------------------------------
void encheMatriz(int **matrixTree, char **matrixTreeChar, No *raiz, int altura, int linha, int coluna)
{
  int aux = pow(2, altura - 2 - linha);
  *(*(matrixTree + linha) + coluna) = raiz->num;
  if (raiz->esquerda != NULL)
  {
    *(*(matrixTreeChar + linha) + coluna - aux) = '/';
    encheMatriz(matrixTree, matrixTreeChar, raiz->esquerda, altura, linha + 1, coluna - aux);
  }
  if (raiz->dir != NULL)
  {
    *(*(matrixTreeChar + linha) + coluna + aux) = '\\';
    encheMatriz(matrixTree, matrixTreeChar, raiz->dir, altura, linha + 1, coluna + aux);
  }
}
//------------------------------------------------------------------------------
void mostraMatriz(int **matrixTree, char **matrixTreeChar, int height, int *retira)
{
  printf("  ");
  for (int j = 0; j < pow(2, height) - 1; j++)
  {
    if (retira[j])
    {
      if (j != (int)(pow(2, height) - 1) / 2)
      {
        printf(" ");
      }
      else
      {
        printf("%d", matrixTree[0][j]);
      }
    }
  }
  printf("  \n");
  for (int i = 0; i < height - 1; i++)
  {
    printf("  ");
    for (int j = 0; (j < pow(2, height) - 1); j++)
    {
      if (retira[j])
      {
        if (matrixTreeChar[i][j] == '/' || matrixTreeChar[i][j] == '\\')
        {
          for (int aux = matrixTree[i + 1][j] / 10; aux != 0; aux = aux / 10)
          {
            printf(" ");
          }
          printf("%c", matrixTreeChar[i][j]);
        }
        else
        {
          printf(" ");
        }
      }
    }
    printf("  \n");
    printf("  ");
    for (int j = 0; j < pow(2, height) - 1; j++)
    {
      if (retira[j])
      {
        if (matrixTreeChar[i][j] == '/' || matrixTreeChar[i][j] == '\\')
        {
          printf("%d", matrixTree[i + 1][j]);
        }
        else
        {
          printf("%c", matrixTreeChar[i][j]);
        }
      }
    }
    printf("  \n");
  }
}
//------------------------------------------------------------------------------
