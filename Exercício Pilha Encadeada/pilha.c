#include "pilha.h"
#include <stdio.h>

void inicializar(pilha *p){
    p->topo = NULL;    
}

int tamanho(pilha *p){
    int num=0;
    no * aux = p->topo;
    while(aux!=NULL){
        num++;
        aux=aux->prox;   
    }
    return num;
}

int empty(pilha *p){
    if(p->topo==NULL) return 1;//retorna 1 se vazio;
    return 0;//retorna 0 se não-vazio
}

int push (pilha *p, contato c){
    no *novo = (no*) malloc(sizeof(no));
    if(novo!=NULL){
        strcpy(novo->c.nome,c.nome);
        strcpy(novo->c.email,c.email);
        strcpy(novo->c.fone,c.fone);
        novo->prox = p->topo;
        p->topo = novo;
        return 1; //deu certo;
    } else return 0;// deu errado;
}

int pop  (pilha *p, contato *c){
    no* aux = p->topo; 
    if(!empty(p)){
        strcpy(c->nome, aux->c.nome);
        strcpy(c->email, aux->c.email);
        strcpy(c->fone, aux->c.fone);
        p->topo = aux->prox;
        free(aux);
    } else{
        printf("ERRO: Pilha vazia");
        return 0;
    } 
	return 1;
}

int top  (pilha *p, contato *c){
    no* aux = p->topo; 
    if(!empty(p)){
        strcpy(c->nome, aux->c.nome);
        strcpy(c->email, aux->c.email);
        strcpy(c->fone, aux->c.fone);
    } else{
        printf("ERRO: Pilha vazia");
        return 0;
    } 
	return 1;
}
