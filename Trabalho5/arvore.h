/*  Max Henrique Barbosa - 16/0047013
    Érico Maximiano Bandeira - 16/0070287 */

#ifndef TREE_H
#define TREE_H

typedef struct no
{
  int num;
  struct no *esquerda;
  struct no *direirta;
} No;

No *loadTreeFromFile(char arquivo[]);
void showTree(No *raiz);
void isFull(No *raiz);
void searchValue(No *raiz, int value);
int getHeight(No *raiz);
No *removeValue(No *raiz, int value);
void printInOrder(No *raiz);
void printPreOrder(No *raiz);
void printPostOrder(No *raiz);
No *balanceTree(No *raiz);

#endif
