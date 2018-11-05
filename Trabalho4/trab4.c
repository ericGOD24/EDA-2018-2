/*  Max Henrique Barbosa - 16/0047013
    Érico Maximiano Bandeira - 16/0070287 */
    
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

#define UnidadeTempo 5 


//------------------------------------------------------------------------------
typedef struct info {
	int codigo;
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
//------------------------------------------------------------------------------

int aproxDecolagem();
int numeroCombustivel();
char tipoVoo(int *, int *, int, int);
void insereInicioFila(Fila *f, int );
void insereFimFila(Fila *f, int, int *, int *, int, int);
void imprimeVoo(Fila *f);
void eventos(Fila *f, int, int *, char cod[64][6]);
int relogio(int, int);
void confereTempo(Fila *f, int);
void reduzCombustivel(Fila *f, int);
int procura(Fila *f);
void insereFilaEmergencia(Fila *f, int, char, int);


Info filaRetiraInicio(Fila *f);
Info filaRetiraFim(Fila *f);
Fila *criaFila(void);
Fila *retiraElemento(Fila *f);
Lista *insereInicio(Lista *ini, Info *i);
Lista *insereFim(Lista *fim, Info *i);
Lista *retiraInicio(Lista *ini);
Lista *retiraFim(Lista *fim);
Lista *busca(Fila *f);


//------------------------------------------------------------------------------

int main(int argc, char const *argv[]){
  int nVoos,nAproximacoes,nDecolagens,aux,tempo = 1000;
	int auxAproximacao=0, auxDecolagem=0;
  char codVoos[64][6] = {"VG3001", "JJ4404", "LN7001", "TG1501", "GL7602", "TT1010", "AZ1009",
                         "AZ1008", "AZ1010", "TG1506", "VG3002", "JJ4402", "GL7603", "RL7880",
                         "AL0012", "TT4544", "TG1505", "VG3003", "JJ4403", "JJ4401", "LN7002",
                         "AZ1002", "AZ1007", "GL7604", "AZ1006", "TG1503", "AZ1003", "JJ4403",
                         "AZ1001", "LN7003", "AZ1004", "TG1504", "AZ1005", "TG1502", "GL7601",
                         "TT4500", "RL7801", "JJ4410", "GL7607", "AL0029", "VV3390", "VV3392",
                         "GF4681", "GF4690", "AZ1020", "JJ4435", "VG3010", "LF0920", "AZ1065",
                         "LF0978", "RL7867", "TT4502", "GL7645", "LF0932", "JJ4434", "TG1510",
                         "TT1020", "AZ1098", "BA2312", "VG3030", "BA2304", "KL5609", "KL5610",
                         "KL5611"};

  
	Lista *l;
	Fila *f,*auxiliar;
	srand(time(NULL));
	f = criaFila();
	nAproximacoes=aproxDecolagem();
	nDecolagens=aproxDecolagem();
	nVoos = nAproximacoes + nDecolagens;
	for(aux = 0; aux < nVoos; aux++){
		insereFimFila(f,aux+1,&auxDecolagem,&auxAproximacao,nAproximacoes,nDecolagens);
	}
	printf("||===================================================||\n");
	printf("||Aeroporto Internacional de Brasília                ||\n");
	printf("||Hora Inicial: 10:00                                ||\n");
	printf("||Fila de Pedidos:[código do voo – P/D – prioridade] ||\n");
	printf("||Número de Voos: %d                                 ||\n",nVoos);
	printf("||Número de Aproximacoes: %d                         ||\n",nAproximacoes);
	printf("||Número de Decolagens: %d                           ||\n",nDecolagens);
	printf("||===================================================||\n");
	eventos(f,nVoos,&tempo,codVoos);
	free(f);
	//printf("%d %d\n",auxDecolagem,auxAproximacao);
  return 0;
}
//------------------------------------------------------------------------------
int aproxDecolagem(){
  return 10 + (rand() % (22)) + 1;
}
//------------------------------------------------------------------------------
int numeroCombustivel(){
  return (rand() % (13));
}
//------------------------------------------------------------------------------
char tipoVoo(int *auxDecolagem,int *auxAproximacao,int nAproximacoes,int nDecolagens){
	int n;
  n = rand() % (2);
	if (*auxAproximacao == nAproximacoes) {
		*auxDecolagem += 1;
		return 'D';
	}
	if (*auxDecolagem == nDecolagens) {
		*auxAproximacao += 1;
		return 'A';
	}
	if(n == 0){
		*auxAproximacao += 1;
		return 'A';
	}
	if(n == 1){
		*auxDecolagem += 1;
		return 'D';
	}
}
//------------------------------------------------------------------------------
Lista *insereInicio(Lista *ini, Info *i){
  Lista *novo = (Lista *)malloc(sizeof(Lista));
  novo->info = *i;
  novo->prox = ini;
  novo->ant = NULL;
  if (ini != NULL) 
    ini->ant = novo;
  return novo;
}
//------------------------------------------------------------------------------
Lista *insereFim(Lista *fim, Info *i){
  Lista *novo = (Lista *)malloc(sizeof(Lista));
  novo->info = *i;
  novo->prox = NULL;
  novo->ant = fim;
  if (fim != NULL) 
    fim->prox = novo;
  return novo;
}
//------------------------------------------------------------------------------
Lista *retiraInicio(Lista *ini){
  Lista *p = ini->prox;
  if (p != NULL) 
    p->ant = NULL;
  free(ini);
  return p;
}
//------------------------------------------------------------------------------
Lista *retiraFim(Lista *fim){
  Lista *p = fim->ant;
  if (p != NULL) 
    p->prox = NULL;
  free(fim);
  return p;
}
//------------------------------------------------------------------------------
Fila *criaFila(void){
  Fila *f = (Fila *)malloc(sizeof(Fila));
  f->ini = f->fim = NULL;
  return f;
}
//------------------------------------------------------------------------------
void insereInicioFila(Fila *f, int n){
  Info *i = (Info *)calloc(1, sizeof(Info));
  f->ini = insereInicio(f->ini, i);
  if (f->fim == NULL) 
    f->fim = f->ini;
}
//------------------------------------------------------------------------------
void insereFimFila(Fila *f, int n, int *auxDecolagem, int *auxAproximacao, int nAproximacoes, int nDecolagens){
  Info *i = (Info *)calloc(1, sizeof(Info));
  i->codigo = n;
  i->tipo = tipoVoo(auxDecolagem, auxAproximacao, nAproximacoes, nDecolagens);
  if (i->tipo == 'A')
  {
    i->combustivel = numeroCombustivel();
  }
  f->fim = insereFim(f->fim, i);
  if (f->ini == NULL)
    f->ini = f->fim;
}
//------------------------------------------------------------------------------
Info filaRetiraInicio(Fila *f){
  Info v;
  if (f->ini == NULL){
    printf("Fila vazia.\n");
    exit(1);
  }
  v = f->ini->info;
  f->ini = retiraInicio(f->ini);
  if (f->ini == NULL)
    f->fim = NULL;
  return v;
}
//------------------------------------------------------------------------------
void imprimeVoo(Fila *f){
  Lista *q;
  for (q = f->ini; q != NULL; q = q->prox)
    printf("[%d %c %d] ", q->info.codigo, q->info.tipo, q->info.combustivel);
}
//------------------------------------------------------------------------------
void eventos(Fila *f, int nVoos, int *tempo, char cod[64][6]){
  int pistasEmUso[3] = {0, 0, 0};
  int tempoPistas[3] = {0, 0, 0};
  int pistaAtual, contadorDaMorte = 0;
  int combZeroInicial = 0;
  char codigo[7], strTempo[5];
  combZeroInicial = procura(f);
  for (int aux = 0; aux < combZeroInicial; aux++){
    f = retiraElemento(f);
  }
  for (int i = 0; i < nVoos; i++){
    if (f->ini->info.combustivel < 0 && f->ini->info.tipo == 'A'){
      for (int j = 0; j < 6; j++){
        codigo[j] = cod[i][j];
      }
      printf("Código do Voo: %s / %d\n", codigo, f->ini->info.codigo);
      printf("Status: Alerta crítico, a aeronave irá cair!\n\n");
      filaRetiraInicio(f);
    }
    else {
      if (tempoPistas[0] == 0){
        puts(" ");
        puts("-----------------------------------");
        imprimeVoo(f);
        puts(" ");
        pistaAtual = 1;
        pistasEmUso[0] = 1;
      }
      else if (tempoPistas[1] == 0){
        puts(" ");
        puts("-----------------------------------");
        imprimeVoo(f);
        puts(" ");
        pistaAtual = 2;
        pistasEmUso[1] = 1;
      }
      else if ((tempoPistas[2] == 0 && f->ini->info.tipo == 'D') || (tempoPistas[2] == 0 && f->ini->info.tipo == 'A' && f->ini->info.combustivel == 0)){
        puts(" ");
        puts("-----------------------------------");
        imprimeVoo(f);
        puts(" ");
        pistaAtual = 3;
        pistasEmUso[2] = 1;
      }
      else {
        if (tempoPistas[0] <= tempoPistas[1] && tempoPistas[0] <= tempoPistas[2]){
          confereTempo(f, *tempo);
          *tempo = relogio(*tempo, tempoPistas[0]);
          tempoPistas[1] -= tempoPistas[0];
          tempoPistas[2] -= tempoPistas[0];
          tempoPistas[0] = 0;
          pistaAtual = 1;
          puts(" ");
          puts("-----------------------------------");
          imprimeVoo(f);
          puts(" ");
        }
        else if (tempoPistas[1] <= tempoPistas[0] && tempoPistas[1] <= tempoPistas[2]){
          confereTempo(f, *tempo);
          *tempo = relogio(*tempo, tempoPistas[1]);
          tempoPistas[0] -= tempoPistas[1];
          tempoPistas[2] -= tempoPistas[1];
          tempoPistas[1] = 0;
          pistaAtual = 2;
          puts(" ");
          puts("-----------------------------------");
          imprimeVoo(f);
          puts(" ");
        }
        else if ((tempoPistas[2] <= tempoPistas[0] && tempoPistas[2] <= tempoPistas[1] && f->ini->info.tipo == 'D')){
          confereTempo(f, *tempo);
          tempoPistas[0] -= tempoPistas[2];
          tempoPistas[1] -= tempoPistas[2];
          tempoPistas[2] = 0;
          pistaAtual = 3;
          puts(" ");
          puts("-----------------------------------");
          imprimeVoo(f);
          puts(" ");
        }
        else{
          if (tempoPistas[0] <= tempoPistas[1]){
            confereTempo(f, *tempo);
            *tempo = relogio(*tempo, tempoPistas[0]);
            tempoPistas[1] -= tempoPistas[0];
            tempoPistas[0] = 0;
            pistaAtual = 1;
            puts(" ");
            puts("-----------------------------------");
            imprimeVoo(f);
            puts(" ");
          }
          else{
            confereTempo(f, *tempo);
            *tempo = relogio(*tempo, tempoPistas[1]);
            tempoPistas[0] -= tempoPistas[1];
            tempoPistas[1] = 0;
            pistaAtual = 2;
            puts(" ");
            puts("-----------------------------------");
            imprimeVoo(f);
            puts(" ");
          }
        }
      }
      printf("tempo1 = %d, tempo 2 = %d, tempo 3 = %d\n", tempoPistas[0], tempoPistas[1], tempoPistas[2]);
      if (f->ini->info.combustivel < 0 && f->ini->info.tipo == 'A'){
        for (int j = 0; j < 6; j++){
          codigo[j] = cod[i][j];
        }
        printf("Código do Voo: %s / %d\n", codigo, f->ini->info.codigo);
        printf("Status: explodiu\n\n");
        filaRetiraInicio(f);
        }
      else{
        for (int j = 0; j < 6; j++){
          codigo[j] = cod[i][j];
        }
        printf("Código do Voo: %s / %d\n", codigo, f->ini->info.codigo);
        if (f->ini->info.tipo == 'A'){
          printf("Status: Aeronave Pousou\n");
          if (pistaAtual == 1){
            tempoPistas[0] += 4 * UnidadeTempo;
          }
          else if (pistaAtual == 2){
            tempoPistas[1] += 4 * UnidadeTempo;
          }
          else if (pistaAtual == 3){
            tempoPistas[2] += 4 * UnidadeTempo;
          }
        }
        else{
          printf("Status: Aeronave Decolou\n");
          if (pistaAtual == 1){
            tempoPistas[0] += 2 * UnidadeTempo;
          }
          else if (pistaAtual == 2){
            tempoPistas[1] += 2 * UnidadeTempo;
          }
          else if (pistaAtual == 3){
            tempoPistas[2] += 2 * UnidadeTempo;
          }
        }
        strcpy(strTempo, "");
        snprintf(strTempo, 5, "%d", *tempo);

        printf("Horário do início do procedimento: %c%c:%c%c\n", strTempo[0], strTempo[1], strTempo[2], strTempo[3]);
        printf("tempo1 = %d, tempo 2 = %d, tempo 3 = %d\n", tempoPistas[0], tempoPistas[1], tempoPistas[2]);
        printf("Pista: %d\n\n\n", pistaAtual);

        filaRetiraInicio(f);
      }
    }
  }
}
//------------------------------------------------------------------------------
int relogio(int t, int n){
  int resultado;
  if (t < 1100){
    if (n + (t - 1000) < 60){
      resultado = t + n;
    }
    else if (n + (t - 1000) == 60){
      resultado = t + (40 + n);
    }
    else if (n + (t - 1000) > 60){
      resultado = t + (40 + n) + 10;
    }
  }
  else if (t < 1200){
    if (n + (t - 1100) < 60){
      resultado = t + n;
    }
    else if (n + (t - 1100) == 60){
      resultado = t + (40 + n);
    }
    else if (n + (t - 1100) > 60){
      resultado = t + (40 + n) + 10;
    }
  }
  else if (t < 1300){
    if (n + (t - 1200) < 60){
      resultado = t + n;
    }
    else if (n + (t - 1200) == 60){
      resultado = t + (40 + n);
    }
    else if (n + (t - 1200) > 60){
      resultado = t + (40 + n) + 10;
    }
  }
  else if (t < 1400){
    if (n + (t - 1300) < 60){
      resultado = t + n;
    }
    else if (n + (t - 1300) == 60){
      resultado = t + (40 + n);
    }
    else if (n + (t - 1300) > 60){
      resultado = t + (40 + n) + 10;
    }
  }
  return resultado;
}
//------------------------------------------------------------------------------
void confereTempo(Fila *f, int tempo){
  if (tempo >= 1050 && tempo < 1140){
    reduzCombustivel(f, 1);
  }
  else if (tempo >= 1140 && tempo < 1230){
    reduzCombustivel(f, 1);
  }
  else if (tempo >= 1230 && tempo < 1320){
    reduzCombustivel(f, 1);
  }
  else if (tempo >= 1320 && tempo < 1410){
    reduzCombustivel(f, 1);
  }
  else if (tempo >= 1410 && tempo < 1500){
    reduzCombustivel(f, 1);
  }
}
//------------------------------------------------------------------------------
void reduzCombustivel(Fila *f, int n){
  Lista *q;
  int combZeroInicial = 0;
  for (q = f->ini; q != NULL; q = q->prox)
    q->info.combustivel -= 1 * n;
  combZeroInicial = procura(f);
  for (int aux = 0; aux < combZeroInicial; aux++){
    f = retiraElemento(f);
  }
}
//------------------------------------------------------------------------------
Lista *busca(Fila *f){
  Lista *q;
  for (q = f->fim; q != NULL; q = q->ant)
    if (q->info.tipo == 'A')
      if (q->info.combustivel <= 0)
        return q;
  return NULL;
}
//------------------------------------------------------------------------------
int procura(Fila *f){
  Lista *q;
  int total = 0;
  for (q = f->fim; q != NULL; q = q->ant)
    if (q->info.tipo == 'A')
      if (q->info.combustivel <= 0)
        total++;
  return total;
}
//------------------------------------------------------------------------------
Fila *retiraElemento(Fila *f){
  Lista *q = busca(f);
  if (q == NULL){
    return f;
  }
  if (f->ini == q)
    f->ini = q->prox;
  else
    q->ant->prox = q->prox;
  if (q->prox != NULL)
    q->prox->ant = q->ant;

  insereFilaEmergencia(f, q->info.codigo, q->info.tipo, q->info.combustivel);
  free(q);
  return f;
}
//------------------------------------------------------------------------------
void insereFilaEmergencia(Fila *f, int codigo, char tipo, int combustivel){
  Info *i = (Info *)calloc(1, sizeof(Info));
  i->codigo = codigo;
  i->tipo = tipo;
  i->combustivel = combustivel;
  f->ini = insereInicio(f->ini, i);
  if (f->fim == NULL) 
    f->fim = f->ini;
}
//------------------------------------------------------------------------------
