/*
EXERCICIO 05
Reescreva o exercício 2 sem usar variáveis globais.
Você vai precisar passar o vetor como parâmetro, nos códigos que usam função;
*/

#include <stdio.h>

// struct Aluno
typedef struct {
    char nome[50];
    int idade;
    char telefone_e[15];
    char contato_e[15];
} Aluno;

// Assinaturas das funções
void lerAluno(Aluno vetor_alunos[], int i);
void exibirAluno(Aluno vetor_alunos[], int i);

// Função PRINCIPAL
int main(){
    int i;
    char opcao = '.';
    
    // Vetor com 5 alunos (agora dentro da MAIN)
    Aluno pre_escola[5];
    
    for(i=0;i<5;i++){
        lerAluno(pre_escola, i);
    }
    
    printf("\nGostaria de ver os dados registrados no sistema? (S/N): ");
    scanf(" %c", &opcao);
    
    if(opcao == 'S' || opcao == 's'){
         printf("EXIBINDO REGISTROS DOS ALUNOS\n");
        for(i=0;i<5;i++){
            exibirAluno(pre_escola, i);
        }
    } else if (opcao == 'N' || opcao == 'n'){
        printf("Encerrando o programa...\n");
        return 0;
    } else {
        return 0;
    }
    
    return 0;
}//chave main

// Função para ler UM aluno 
void lerAluno(Aluno vetor_alunos[], int i){
    if(i < 0 || i >= 5){
        printf("Indice de aluno invalido.\n");
        return;
    }
    
    printf("\nCADASTRO DO ALUNO %d\n", i + 1);
    printf("---------------------------\n");
    
    printf("Nome: ");
    scanf(" %[^\n]", vetor_alunos[i].nome);
    
    printf("Idade: ");
    scanf("%d", &vetor_alunos[i].idade);
    
    printf("Telefone de Emergencia: ");
    scanf(" %[^\n]", vetor_alunos[i].telefone_e);
    
    printf("Contato de Emergencia: ");
    scanf(" %[^\n]", vetor_alunos[i].contato_e);
    
    printf("\n");
}// chave lerAluno

// Função para exibir o ALUNO
void exibirAluno(Aluno vetor_alunos[], int i){
    if(i < 0 || i >= 5){
        printf("Indice de aluno invalido.\n");
        return;
    }
    
    printf("---------------------------\n");
    printf("DADOS DO ALUNO %d\n\n", i + 1);
    
    printf("Nome: %s\n", vetor_alunos[i].nome);
    printf("Idade: %d\n", vetor_alunos[i].idade);
    printf("Telefone de Emergencia: %s\n", vetor_alunos[i].telefone_e);
    printf("Contato de Emergencia: %s\n", vetor_alunos[i].contato_e);
    printf("---------------------------\n");
    printf("\n");
}// chave exibirAluno