/******************************************************************************

Pilha Encadeada Ex1

Criar uma pilha encadeada em C
1- inserir contatos de 1 a 3
2- remover um Contato  e imprimir em tela os dados
3 - remover um Contato  e imprimir em tela os dados
4 -  empilhar um novo contato
5 - remover um Contato  e imprimir em tela os dados
6 - remover um Contato  e imprimir em tela os dados
7 – tentar remover contato (deve dar erro)

*******************************************************************************/

#include <stdio.h>
#include "pilha.h"
#include <stdlib.h>

int main() {
    int i;
    contato pessoa, pAux;
    pilha p;
    inicializar(&p);
    
    for(i=0;i<3;i++){//inserir 
        printf("Digite o Nome: ");
        gets(pessoa.nome);
        
        printf("Digite o email: ");
        gets(pessoa.email);
        
        printf("Digite o fone : ");
        gets(pessoa.fone);
        
        push(&p, pessoa);
        puts(""); //pular uma linha;
    }
    
    for(i=0;i<2;i++){//remover 2
        pop(&p,&pAux);
        printf("Nome: %s \tFone: %s\n",pAux.nome, pAux.fone);
        printf("Email: %s\n\n",pAux.email);
    }
    
    //Inserir mais 1
    printf("Digite o Nome: ");
    gets(pessoa.nome);
    printf("Digite o email: ");
    gets(pessoa.email);
    printf("Digite o fone :");
    gets(pessoa.fone);
    
    push(&p, pessoa);
    puts("");//pular uma linha;
    
    for(i=0;i<2;i++){//remover 2
        pop(&p,&pAux);
        printf("Nome: %s \tFone: %s\n",pAux.nome, pAux.fone);
        printf("Email: %s\n\n",pAux.email);
    }
    
    //passo 7 tentar remover da pilha vazia
     printf("\nTentando remover da pilha vazia...\n");
    if (pop(&p, &pAux)) {
     printf("Contato Removido: %s\n", pAux.nome);
    } else {
    printf("Erro: Nao foi possivel remover. A pilha esta vazia.\n");
    }
}