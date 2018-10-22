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
Contato *carregaArquivo();
Contato *insertSort(Contato *, Contato *);

//------------------------------------------------------------------------------
main(int argc, char const *argv[]) {
  FILE *fp;
  Contato *list;
  int sel;
  char c;

  if (list = (Contato *)malloc(sizeof(Contato)), list == NULL) {
    printf("Erro ao alocar!\n");
  }

  list = readFile();
  system("clear");
  return 0;
}

//------------------------------------------------------------------------------
void menu () {
  printf("\n");
  printf("\t 1 - Inserir novo registro\n\n");
  printf("\t 2 - Remover registros que possuem o nome indicado\n\n");
  printf("\t 3 - Visualizar registros que possuem o nome indicado\n\n");
  printf("\t 4 - Visualizar todos os registros em ordem alfabética de nomes\n\n");
  printf("\t 0 - Sair\n\n");
}
//------------------------------------------------------------------------------
Contato *carregaArquivo () {
  FILE *fp;
  Contato *contatos, *primeiro;
  char c;

  if (fp = fopen ("contatos.txt", "r"), fp == NULL) {
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
    primeiro = insertSort(primeiro, contatos);
  }

  fclose(fp);

  return primeiro;
}
//------------------------------------------------------------------------------
Contato *insertSort (Contato *lista, Contato *termo) {
  Contato *aux;

  if (lista == NULL) {
    lista = termo;
    termo->ante = NULL;
    termo->prox = NULL;
    return lista;
  }
  for (aux = lista; aux != NULL; aux = aux->prox) {
    if (strcasecmp(aux->name, termo->name) > 0) {
      termo->prox = aux;
      termo->ante = aux->ante;
      aux->ante = termo;
      if (termo->ante != NULL) {
        termo->ante->prox = termo;
      }
      else {
        lista = termo;
      }
      return lista;
    }
    if (aux->prox == NULL) {
      termo->prox = NULL;
      termo->ante = aux;
      aux->prox = termo;
      return lista;
    }
  }
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
Contato *inserirRegistro(Contato *lista) {
  Contato *novo;
  int dia, mes, ano;
  char day[3], month[3], year[5];

  if (novo = (Contato *)malloc(sizeof(Contato)), novo == NULL) {
    printf("alocação falhou!\n");
  }

  printf("Digite o nome do novo contato:\n");
  scanf("%[^\n]", novo->name);
  getchar();
  do
  {
    printf("Digite o celular do novo contato:\n");
    scanf("%[^\n]", novo->cel);
    getchar();
  } while (!validaCelular(novo->cel));
  printf("Digite o endereço do novo contato:\n");
  scanf("%[^\n]", novo->adress);
  getchar();
  printf("Digite o cep do novo contato:\n");
  scanf(" %u", &novo->cep);
  printf("Digite a data de nascimento do novo contato:\n");
  do
  {
    printf("Dia:\n");
    scanf(" %d", &dia);
  } while (dia < 1 || dia > 31);
  do
  {
    printf("Mês:\n");
    scanf(" %d", &mes);
  } while (mes < 1 || mes > 12);
  printf("Ano:\n");
  scanf(" %d", &ano);
  sprintf(day, "%i", dia);
  sprintf(month, "%i", mes);
  sprintf(year, "%i", ano);
  sprintf(novo->date, "%s/%s/%s", day, month, year);
  lista = insertSort(lista, novo);
  getchar();
  return lista;
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void salvaLista(Contato *lista) {
  FILE *arq;
  Contato *aux;

  if (arq = fopen("contatos.txt", "w"), arq == NULL) {
    printf("erro ao abrir o arquivo!\n");
    exit(1);
  }

  for (aux = lista; aux != NULL; aux = aux->prox) {
    fprintf(arq, "%s\n", aux->name);
    fprintf(arq, "%s\n", aux->cel);
    fprintf(arq, "%s\n", aux->adress);
    fprintf(arq, "%u\n", aux->cep);
    fprintf(arq, "%s\n", aux->date);
    fprintf(arq, "$\n");

    if (aux != lista) {
      free(aux->ante);
    }
    if (aux->prox == NULL) {
      free(aux);
    }
  }

  fclose(arq);
//------------------------------------------------------------------------------
int validaCelular(char celular[]) {
  int aux;
  if (strlen(celular) != 10) {
    puts("Número Invalido! Digite Novamente:");
    return 0;
  }
  else {
    for (aux = 0; aux < 10; aux++) {
      if (!isdigit(celular[aux]) && aux != 5) {
        puts("Número Invalido! Digite Novamente:");
        return 0;
      }
      if (aux == 5) {
        if (celular[aux] != '-') {
          puts("Número Invalido! Digite Novamente:");
          return 0;
        }
      }
    }
  }
  return 1;
}
//------------------------------------------------------------------------------
void continuar()
{
  char c;
  printf("\naperte enter para continuar\n");
  do
  {
    c = getchar();
  } while (c != '\n');
}
//------------------------------------------------------------------------------
void visualizarTodosRegistros(Contato * lista, char modo)
{
  Contato *aux;
  if (modo == '1')
  {
    for (aux = lista; aux != NULL && lista != NULL; aux = aux->prox)
    {
      printf("%s\n", aux->nome);
      printf("%s\n", aux->celular);
      printf("%s\n", aux->endereco);
      printf("%u\n", aux->cep);
      printf("%s\n", aux->nascimento);
      printf("\n");
    }
  }
  else
  {
    for (aux = lista; aux->prox != NULL && lista != NULL; aux = aux->prox)
    {
    }
    for (; aux != NULL && lista != NULL; aux = aux->ant)
    {
      printf("%s\n", aux->nome);
      printf("%s\n", aux->celular);
      printf("%s\n", aux->endereco);
      printf("%u\n", aux->cep);
      printf("%s\n", aux->nascimento);
      printf("\n");
    }
  }
}
//------------------------------------------------------------------------------
void visualizarRegistroNome(Contato * lista, char nome[])
{
  Contato *aux;
  long long int cont = 0;

  for (aux = lista; aux != NULL && lista != NULL; aux = aux->prox)
  {
    if (!strcasecmp(aux->nome, nome))
    {
      printf("\n%s\n", aux->nome);
      printf("%s\n", aux->celular);
      printf("%s\n", aux->endereco);
      printf("%u\n", aux->cep);
      printf("%s\n", aux->nascimento);
      printf("\n");
      cont++;
    }
  }
  if (!cont)
  {
    printf("\nnome não encontrado.\n");
  }
}
//------------------------------------------------------------------------------
Contato *removerRegistros(Contato * lista, char nome[])
{
  Contato *aux, *aux1;
  int cont = 0;

  for (aux = lista; aux != NULL; aux = aux->prox)
  {
    if (!strcasecmp(aux->nome, nome))
    {
      printf("\ncontato removido:\n");
      printf("%s\n", aux->nome);
      printf("%s\n", aux->celular);
      printf("%s\n", aux->endereco);
      printf("%u\n", aux->cep);
      printf("%s\n", aux->nascimento);
      printf("\n");
      if (aux->prox == NULL & aux->ant == NULL)
      {
        free(lista);
        return NULL;
      }
      else if (aux->prox == NULL)
      {
        aux1 = aux->ant;
        free(aux);
        aux1->prox = NULL;
      }
      else if (aux->ant == NULL)
      {
        lista = aux->prox;
        lista->ant = NULL;
        free(aux);
        aux = lista;
      }
      else
      {
        aux1 = aux->ant;
        aux1->prox = aux->prox;
        aux1 = aux->prox;
        aux1->ant = aux->ant;
        free(aux);
      }
      cont++;
    }
  }
  if (!cont)
  {
    printf("\nnome não encontrado.\n");
  }
  return lista;
}
//------------------------------------------------------------------------------
