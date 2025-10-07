#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

// Inicializa a fila como vazia
void inicializar (tFila *f){
    f->head = NULL;
    f->tail = NULL;
    f->size = 0;
}

// Verifica se a fila esta vazia
int vazia (tFila *f){
    return (f->head == NULL); // retorna 1 se head for NULL
}

// Insere um elemento no final da fila
int inserir(tFila *f, int d){
    tipoNo *novo = (tipoNo*) malloc(sizeof(tipoNo));
    if(novo == NULL){
        return 0; // erro de alocacao
    }

    novo->dado = d;
    novo->prox = NULL;
    novo->ant = f->tail;

    if(vazia(f)){
        f->head = novo; // se a fila estiver vazia, o novo nó eh head e tail
    } else {
        f->tail->prox = novo; // O prox do antigo tail aponta para o novo nó
    }

    f->tail = novo; // O novo nó agora eh o tail
    f->size++;
    return 1; // inserçao bem sucedida
}

// Remove um elemento do inicio da fila
int remover(tFila *f, int *d){
    if(vazia(f)){
        return 0; // Não remove de uma fila vazia
    }

    tipoNo *aux = f->head;
    *d = aux->dado; // O valor removido eh retornado atraves do ponteiro d

    f->head = f->head->prox;
    if(f->head != NULL){
        f->head->ant = NULL;
    } else {
        f->tail = NULL; // A fila ficou vazia
    }

    free(aux);
    f->size--;
    return 1; // Remoçao bem sucedida
}

// Retorna o tamanho atual da fila
int tamanho(tFila *f){
    return f->size;
}

// Imprime o conteudo da fila
void imprimeFila(tFila *f){
    tipoNo *aux = f->head;
    printf("Fila: [ ");
    while(aux != NULL){
        printf("%d ", aux->dado);
        aux = aux->prox;
    }
    printf("] Tamanho: %d\n", tamanho(f));
}
