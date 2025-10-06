/*
#ifndef PILHA_H
#define PILHA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
*/

//armazena dados a cada nó
typedef struct{
    char nome[100];
    char email[150];
    char fone[15];
} contato;

//estrutura cada nó com dados e ponteiro
typedef struct { //ou typedef struct no
	contato c;
	struct no* prox; //ponteiro para próximo elemento
} no;

//estrutura pilha (repesentaada pelo seu topo)
typedef struct{
     no *topo;
} pilha;

int push (pilha *p, contato c);	// retorna 1 se o empilhamento deu certo; retorna 0 se o empilhamento deu errado
								// recebe como parametro um contato c, os dados dessa struct devem ser copiados para o novo elemento criado

int pop  (pilha *p, contato *c);//retorna 1 se a remo��o deu certo, retorna 0 se deu errado;
								//recebe como parametro um ponteiro para um contato c, que deve receber as informa��es removidas da pilha

int top  (pilha *p, contato *c);// mesmo que o pop, mas n�o remove;

int tamanho(pilha *p);

int empty(pilha *p); //retorna 1 se est� vazia, sen�o retorna 0;

void inicializar(pilha *p);// atribui nulo para o topo da pilha

//#endif /* PILHA_H */