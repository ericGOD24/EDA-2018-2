/*  Max Henrique Barbosa - 16/0047013
    Érico Maximiano - 16/0070287 */

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

void menu();
void voltar();
void salvaLista(Contato *);
void visualizarContato(Contato *, char name[]); 
void visualizarTodosContatos(Contato *, char);
int validaNumero(char cel[]);
Contato *carregaArquivo();
Contato *insertionSort(Contato *, Contato *);
Contato *inserirContato(Contato *);
Contato *removerContato(Contato *, char name[]);

//------------------------------------------------------------------------------
int main(int argc, char const *argv[]){
  FILE *fp;
  Contato *lista;
  char select, c, modo, name[101];

  lista = carregaArquivo();

  do {
    menu();
    scanf("%c", &select);
    do {
      c = getchar();
    } 
    while (c != '\n');

    switch (select) {
    
    case '1':
      system("clear");
      lista = inserirContato(lista);
      voltar();
    break;
   
    case '2':
      system("clear");
      printf("Digite o nome que deseja remover dos contatos:\n");
      scanf("%[^\n]", name);
      getchar();
      lista = removerContato(lista, name);
      strcpy(name, "");
      voltar();
    break;
   
    case '3':
      system("clear");
      printf("Digite o nome do contato que deseja ver:\n");
      scanf("%[^\n]", name);
      getchar();
      visualizarContato(lista, name);
      strcpy(name, "");
      voltar();
    break;
    
    case '4':
      system("clear");
      
      do{
        printf("Digite o modo que deseja visualizar os contatos:\n");
        printf("1 - ordem crescente\n");
        printf("2 - ordem decrescente\n");
        scanf("%c", &modo);  
        
        do{
          c = getchar();
        } 
        while (c != '\n');
      } 
      while (modo < '1' || modo > '2');
      system("clear");
      visualizarTodosContatos(lista, modo);
      voltar(); 
      break;
    
    case '0':
      if (fp = fopen("contatos.txt", "w"), fp == NULL) {
        printf("erro ao abrir o arquivo!\n");
        exit(1);
      }
      salvaLista(lista);
      fclose(fp);
    }
    system("clear");
  } 
  while (select != '0');
  return 0;
}

//------------------------------------------------------------------------------
void menu() {
  printf("\n=========================================================================\n");
  printf("||\t0. Sair                                                        ||\n");
  printf("||\t1. Inserir novo registro                                       ||\n");
  printf("||\t2. Remover registros que possuem o nome indicado               ||\n");
  printf("||\t3. Visualizar registros que possuem o nome indicado            ||\n");
  printf("||\t4. Visualizar todos os registros em ordem alfabética de nomes  ||\n");
  printf("=========================================================================\n\n");
}
//------------------------------------------------------------------------------
Contato *carregaArquivo() {
  FILE *fp;
  Contato *contatos, *primeiro;
  char c;

  if (fp = fopen("contatos.txt", "r"), fp == NULL) {
    printf("erro ao abrir o arquivo!\n");
    exit(1);
  }

  if (!feof(fp)) {
    if (contatos = (Contato *)malloc(sizeof(Contato)), contatos == NULL) {
      printf("alocação falhou!\n");
    }

    fscanf(fp, "%[^\n]\n%s\n%[^\n]\n%u\n%s\n%c\n", contatos->name, contatos->cel, contatos->adress, &contatos->cep, contatos->date, &c);
    if (!strcasecmp(contatos->name, "")) {
      return NULL;
    }
    contatos->ante = NULL;
    contatos->prox = NULL;
    primeiro = contatos;
  }

  while (!feof(fp)) {
    if (contatos = (Contato *)malloc(sizeof(Contato)), contatos == NULL) {
      printf("alocação falhou!\n");
    }
    fscanf(fp, "%[^\n]\n%s\n%[^\n]\n%u\n%s\n%c\n", contatos->name, contatos->cel, contatos->adress, &contatos->cep, contatos->date, &c);
    primeiro = insertionSort(primeiro, contatos);
  }

  fclose(fp);

  return primeiro;
}
//------------------------------------------------------------------------------
Contato *insertionSort(Contato * lista, Contato * termo) {
  Contato *aux;

  if (lista == NULL)
  {
    lista = termo;
    termo->ante = NULL;
    termo->prox = NULL;
    return lista;
  }

  for (aux = lista; aux != NULL; aux = aux->prox)
  {
    if (strcasecmp(aux->name, termo->name) > 0)
    {
      termo->prox = aux;
      termo->ante = aux->ante;
      aux->ante = termo;
      if (termo->ante != NULL)
      {
        termo->ante->prox = termo;
      }
      else
      {
        lista = termo;
      }
      return lista;
    }
    if (aux->prox == NULL)
    {
      termo->prox = NULL;
      termo->ante = aux;
      aux->prox = termo;
      return lista;
    }
  }
}
//------------------------------------------------------------------------------
Contato *inserirContato(Contato * lista){
  Contato *novo;
  int dia, mes, ano;
  char day[3], month[3], year[5];

  if (novo = (Contato *)malloc(sizeof(Contato)), novo == NULL) {
    printf("alocação falhou!\n");
  }

  printf("Digite o nome do novo contato:\n");
  scanf("%[^\n]", novo->name);
  getchar();
  
  do {
    printf("Digite o celular do novo contato:\n");
    scanf("%[^\n]", novo->cel);
    getchar();
  }

  while (!validaNumero(novo->cel));
  printf("Digite o endereço do novo contato:\n");

  scanf("%[^\n]", novo->adress);
  getchar();

  printf("Digite o cep do novo contato:\n");

  scanf(" %u", &novo->cep);
  printf("Digite a data de nascimento do novo contato:\n");

  do {
    printf("Dia:\n");
    scanf(" %d", &dia);
  }

  while (dia < 1 || dia > 31);

  do {
    printf("Mês:\n");
    scanf(" %d", &mes);
  }

  while (mes < 1 || mes > 12);
  printf("Ano:\n");
  scanf(" %d", &ano);
  sprintf(day, "%i", dia);
  sprintf(month, "%i", mes);
  sprintf(year, "%i", ano);
  sprintf(novo->date, "%s/%s/%s", day, month, year);
  lista = insertionSort(lista, novo);
  getchar();
  return lista;
}
//------------------------------------------------------------------------------
void salvaLista(Contato * lista){
  FILE *fp;
  Contato *aux;

  if (fp = fopen("contatos.txt", "w"), fp == NULL) {
    printf("erro ao abrir o arquivo!\n");
    exit(1);
  }

  for (aux = lista; aux != NULL; aux = aux->prox) {
    fprintf(fp, "%s\n", aux->name);
    fprintf(fp, "%s\n", aux->cel);
    fprintf(fp, "%s\n", aux->adress);
    fprintf(fp, "%u\n", aux->cep);
    fprintf(fp, "%s\n", aux->date);
    fprintf(fp, "$\n");

    if (aux != lista) {
      free(aux->ante);
    }
    if (aux->prox == NULL) {
      free(aux);
    }
  }

  fclose(fp);
}
//------------------------------------------------------------------------------
int validaNumero(char cel[]){
  int aux;
  if (strlen(cel) != 10) {
    puts("Número Invalido! Digite Novamente:");
    return 0;
  }
  else {
    for (aux = 0; aux < 10; aux++) {
      if (!isdigit(cel[aux]) && aux != 5) {
        puts("Número Invalido! Digite Novamente:");
        return 0;
      }
      if (aux == 5) {
        if (cel[aux] != '-') {
          puts("Número Invalido! Digite Novamente:");
          return 0;
        }
      }
    }
  }
  return 1;
}
//------------------------------------------------------------------------------
void voltar(){
  char c;
  printf("\nAperte enter para voltar ao menu.\n");
  do {
    c = getchar();
  } while (c != '\n');
}
//------------------------------------------------------------------------------
void visualizarTodosContatos(Contato * lista, char modo){
  Contato *aux;
  if (modo == '1') {
    for (aux = lista; aux != NULL && lista != NULL; aux = aux->prox){
      printf("%s\n", aux->name);
      printf("%s\n", aux->cel);
      printf("%s\n", aux->adress);
      printf("%u\n", aux->cep);
      printf("%s\n", aux->date);
      printf("\n");
    }
  }
  else {
    for (aux = lista; aux->prox != NULL && lista != NULL; aux = aux->prox){
    }
    
    for (; aux != NULL && lista != NULL; aux = aux->ante){
      printf("%s\n", aux->name);
      printf("%s\n", aux->cel);
      printf("%s\n", aux->adress);
      printf("%u\n", aux->cep);
      printf("%s\n", aux->date);
      printf("\n");
    }
  }
}
//------------------------------------------------------------------------------
void visualizarContato(Contato * lista, char name[]){
  Contato *aux;
  long long int cont = 0;

  for (aux = lista; aux != NULL && lista != NULL; aux = aux->prox) {
    if (!strcasecmp(aux->name, name)) {
      printf("\n%s\n", aux->name);
      printf("%s\n", aux->cel);
      printf("%s\n", aux->adress);
      printf("%u\n", aux->cep);
      printf("%s\n", aux->date);
      printf("\n");
      cont++;
    }
  }
  if (!cont) {
    printf("\nnome não encontrado.\n");
  }
}
//------------------------------------------------------------------------------
Contato *removerContato(Contato * lista, char name[]){
  Contato *aux, *aux1;
  int cont = 0;

  for (aux = lista; aux != NULL; aux = aux->prox){
    if (!strcasecmp(aux->name, name)) {
      printf("\nContato removido:\n");
      printf("%s\n", aux->name);
      printf("%s\n", aux->cel);
      printf("%s\n", aux->adress);
      printf("%u\n", aux->cep);
      printf("%s\n", aux->date);
      printf("\n");

      if (aux->prox == NULL & aux->ante == NULL){
        free(lista);
        return NULL;
      }

      else if (aux->prox == NULL){
        aux1 = aux->ante;
        free(aux);
        aux1->prox = NULL;
      }

      else if (aux->ante == NULL){
        lista = aux->prox;
        lista->ante = NULL;
        free(aux);
        aux = lista;
      }

      else {
        aux1 = aux->ante;
        aux1->prox = aux->prox;
        aux1 = aux->prox;
        aux1->ante = aux->ante;
        free(aux);
      }
      cont++;
    }
  }
  if (!cont){
    printf("\nnome não encontrado.\n");
  }
  return lista;
}
//------------------------------------------------------------------------------
