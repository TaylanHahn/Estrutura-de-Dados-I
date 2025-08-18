/*
Atividade Ponteiros
2)
a - Crie um programa que leia 4 variáveis int, informe o endereço e o conteúdo de cada uma delas
b- Crie uma função que recebe quatro ponteiros para inteiros como parâmetros e devolva a media aritmética dos conteúdos apontados (float); (fazer a média dos números, não dos endereços)
c - Crie uma função que receba como parâmetro 3 ponteiros variáveis inteiras e devolva o maior valor (maior conteúdo, não o maior endereço);
d - Crie uma função que receba como parâmetro 3 ponteiros para inteiro e devolva o endereço que aponta para a variável de maior valor; (importante: quero o endereço do maior valor, não o maior endereço...)
*/

#include<stdio.h>
int main (){
  int w, x, y, z, *pw, *px, *py, *pz;
  pw = &w; px = &x; py = &y; pz = &z;
  
  printf("Digite quatro numeros inteiros: ");
  scanf("%d %d %d %d", &w, &x, &y, &z);
  
  printf("\nO conteúdo de W é: %d", *pw);
  printf("\nO endereço de W é: %u", pw);
  
  printf("\nO conteúdo de W é: %d", *px);
  printf("\nO endereço de W é: %u", px);
  
  printf("\nO conteúdo de W é: %d", *py);
  printf("\nO endereço de W é: %u", py);
  
  printf("\nO conteúdo de W é: %d", *pz);
  printf("\nO endereço de W é: %u", pz);
  
}

