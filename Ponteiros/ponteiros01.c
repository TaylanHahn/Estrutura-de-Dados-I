/*
Atividade Ponteiros
1 - Descreva o que cada linha faz:
*/

#include<stdio.h>
int main (){
  int x, *px; // Cria a variável x e o ponteiro
  x = 1; // 
  px = &x;
  printf ("01. x= %d\n", x); // Está imprimindo o valor armazenado na variável x.
  printf ("02. px= %u\n", px); // Está imprimindo o endereço da variável x, já que px é igual a &x.
  printf ("03. *px+1= %d\n", *px + 1); // *px está apontando para o valor que está em x(1) e somando +1, resultando em 2.
  printf ("04. px= %u\n", px); // Aqui px é a variável, que guarda um endereço de memória e é justamente este endereço que está sendo impresso no terminal.
  printf ("05. *px= %d\n", *px); // *px está apontando para o valor que está na variável x.
  printf ("06. *px+=1= %d\n", *px += 1); // Deixando mais visual, está sendo feito *px = *px + 1. *px está apontando para o valor que está na variável x, que é 1 e somando com +1 resultando em 2.
  printf ("07. px= %u\n", px); // Está imprimindo o endereço da variável x, já que px é igual a &x.
  printf ("08. (*px)++= %d\n", (*px)++); // Seguindo a precedência, primeiro (*px) está apontando para o valor na variável x (que é 1) e por fim, o ++ está incrementando esse valor, resultando em 2.
  printf ("09. px= %u\n", px); // px está se referindo ao endereço de x, imprimindo o mesmo.
  printf ("10. *(px++)= %d\n", *(px++)); // Esse entendi para explicar e preferi não perguntar a IA.
  printf ("11. px= %u\n", px); // Está imprimindo o endereço da variável x, já que px é igual a &x.
  printf ("12. *px++= %d\n", *px++); // Pulou o endereço da memória em 1 byte
  printf ("13. px= %u\n", px); // Foi impresso o novo endereço de memória
}

