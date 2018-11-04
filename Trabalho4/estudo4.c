#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#define UnTempo 5   


typedef struct info {
	int id;
	char tipo;
	int combustivel;
} Info;

typedef struct lista {
	Info info;
	struct lista* ant;
	struct lista* prox;
} Lista;

typedef struct fila {
	Lista* ini;
	Lista* fim;
} Fila;

int main (){

}