/*  Max Henrique Barbosa - 16/0047013
    Érico Maximiano Bandeira - 16/0070287 */

#ifndef ARVORE_H
#define ARVORE_H

typedef struct no
{
  int num;
  struct no *esquerda;
  struct no *direita;
} No;

int getHeight(No *raiz);

void showTree(No *raiz);
void isFull(No *raiz);
void searchValue(No *raiz, int );
void printInOrder(No *raiz);
void printPreOrder(No *raiz);
void printPostOrder(No *raiz);

No *balanceTree(No *raiz);
No *removeValue(No *raiz, int );
No *loadTreeFromFile(char arquivo[]);

#endif
