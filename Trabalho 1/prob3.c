#include <stdio.h>
#include <stdlib.h>

//========================================================================
int main (int argc, char *argv[]){
  int discos;

  printf("Forneca o numero de discos");
  scanf("%d\n", &discos);

  hanoi (discos, 'A', 'C', 'B');
  return 0;
}
//=========================================================================
void hanoi (int d, char ori, char dest, char aux){
    if(d==1){
      printf("Mover disco %d de %c para %c\n", d, ori, dest);
    }
    else{
      hanoi(d-1, ori, aux, dest);
      printf("Mover disco %d de %c para %c\n", d, ori, dest);
      hanoi(d-1, aux, dest, ori);
    }
}
