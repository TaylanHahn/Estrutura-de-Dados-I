/*
EXERCICIO 01

Sua empresa o contratou para desenvolver uma agenda para uma pessoa solitária
que tem apenas o telefone da mãe e um amigo. Esta agenda deve ter capacidade
para armazenar o nome, telefone fixo, celular, endereço e aniversário.

A agenda deve ser capaz de inserir os dados de todos os contatos
(máx 3: A mãe, o amigo e ele mesmo)
Após a inserção de todos os contatos deve perguntar ao usuário o número
do contato que ele quer visualizar, caso o número esteja fora do intervalo
(1 a 3), o programa termina, caso contrário o programa escreve na tela os
dados e pergunta novamente.

Este programa nao precisa ter funções além da principal

*/

#include <stdio.h>

// definição da struct "agenda"
    typedef struct{
        char nome[50];
        int telefoneFixo;
        int celular;
        char endereco[100];
        char aniversario[10];
    } agenda;

int main()
{
    int i;
    agenda ag[3]; // array para armazenar os contatos
    
    // laço para a inserção de dados na agenda
    for(i=0;i<3;i++){
        printf("Nome do contato: ");
        scanf("%s", ag[i].nome);
        
        printf("Número do Telefone Fixo: ");
        scanf("%d", &ag[i].telefoneFixo);
        
        printf("Número do Celular: ");
        scanf("%d", &ag[i].celular);
        
        printf("Endereço: ");
        scanf("%s", ag[i].endereco);
        
        printf("Data de aniversário: ");
        scanf("%s", ag[i].aniversario);
        
        printf("\n");
    }
    
    printf("\n\t\tAGENDA");
    for(i=0;i<3;i++){
        printf("\n %s\n %d\n %d\n %s\n %s\n\n", ag[i].nome, ag[i].telefoneFixo, ag[i].celular, ag[i].endereco, ag[i].aniversario);
    }
    
    
    
    do{
        int opcao = 0;
        printf("Qual o número do contato você deseja consultar?");
        scanf("%d", &opcao);
        
        if(opcao == 1){
            i=0;
            true;
            printf("\n %s\n %d\n %d\n %s\n %s\n\n", ag[i].nome, ag[i].telefoneFixo, ag[i].celular, ag[i].endereco, ag[i].aniversario);
        } else if(opcao == 2){
            i=1;
            true;
            printf("\n %s\n %d\n %d\n %s\n %s\n\n", ag[i].nome, ag[i].telefoneFixo, ag[i].celular, ag[i].endereco, ag[i].aniversario);
        } else if(opcao == 3){
            i=2;
            true;
            printf("\n %s\n %d\n %d\n %s\n %s\n\n", ag[i].nome, ag[i].telefoneFixo, ag[i].celular, ag[i].endereco, ag[i].aniversario);    
        } else{
            break;
        }
    } while(opcao != true);
    
    
    // laço para exibir os dados da agenda
    // printf("\n--- Agenda Completa ---\n");
    // for (i = 0; i < 3; i++) {
    //     printf("\nContato %d\n", i + 1);
    //     printf("Nome: %s\n", ag[i].nome);
    //     printf("Telefone Fixo: %d\n", ag[i].telefoneFixo);
    //     printf("Celular: %d\n", ag[i].celular);
    //     printf("Endereço: %s\n", ag[i].endereco);
    //     printf("Aniversário: %s\n", ag[i].aniversario);
    // }
    
    
    
}//main


