#include <stdio.h>
#include "fila.h"
#include <stdlib.h>

void inicializar (tFila *f){
    f->head = f->tail = null;
    f->size = 0;
}

int vazia (tFila *f){
    if (f->head==NULL) return 1;
        else return 0;
}                              //retorna 1 se a fila está vazia
            					//retorna 0 se a fila é não-vazia

int inserir(tFila *f, int d){
    tipoNo *novo = (*tipoNo)malloc(sizeof(tipoNo));
    
    if(novo != NULL){
        novo->dado=d;
        novo->prox=NULL;
    } 
    //retorna 0 se a insercao deu errado
    //retorna 1 se a insercao deu certo
    
    
}
	
	

void imprimeFila (tFila *f);
	//imprime na tela o conteudo da fila

int remover(tFila *f, int *d);
	//retorna 0 se a remocao deu certo
	//retorna 1 se a remocao deu errado
	// se a operacao deu certo, a variavel apontada por d
	//deve receber o valor removido da fila

int tamanho(tFila *f);