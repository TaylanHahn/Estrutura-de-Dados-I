/*
EXERCICIO 03
Crie uma estrutura que armazene o nome de um aluno, número de matrícula, 4 notas e faltas.
Crie um vetor para armazenar 5 alunos.
Crie uma função para ler os dados de um aluno.
Crie uma função para escrever na tela os dados de um aluno
Crie uma função que retorne a média do aluno
Crie uma função que escreva a situação do aluno
As funções acima recebem o índice do aluno como parâmetro e alteram o array global que contém os alunos.
*/

#include <stdio.h>
#include <stdlib.h>

// struct Aluno
typedef struct {
    char nome[50];
    char matricula[15];
    float n1, n2, n3, n4;
    int faltas;
} aluno;

// Vetor global com 5 alunos
aluno alunos[5];

// Assinaturas das funções;
void lerAluno(int i);
void exibirAluno(int i);
float mediaAluno(int i); 
void situacaoAluno(int i); 

// Função PRINCIPAL
int main(){
    int i;
    char opcao = '.';

    // laço para ler os 5 alunos
    for(i=0; i<5; i++){
        lerAluno(i);
    }

    printf("\nGostaria de ver os dados registrados no sistema? (S/N): ");
    scanf(" %c", &opcao);

    if(opcao == 'S' || opcao == 's'){
        printf("\n======== EXIBINDO DADOS DOS ALUNOS ========\n");
        // laço para exibir as infos
        for(i=0; i<5; i++){
            exibirAluno(i);
        }
    } else {
        printf("Encerrando o programa...\n");
    }
    
    return 0;
}//chave main


// -------------- FUNÇÕES ------------------

// Função para ler UM aluno
void lerAluno(int i){
    if(i < 0 || i >= 5){
        printf("Indice de aluno invalido.\n");
        return;
    }

    printf("\nCADASTRO DO ALUNO %d\n", i + 1);
    printf("---------------------------\n");

    printf("Nome do Aluno: ");
    scanf(" %[^\n]", alunos[i].nome);

    printf("Matricula: ");
    scanf(" %[^\n]", alunos[i].matricula);

    printf("Nota 1: ");
    scanf("%f", &alunos[i].n1);
    printf("Nota 2: ");
    scanf("%f", &alunos[i].n2);
    printf("Nota 3: ");
    scanf("%f", &alunos[i].n3);
    printf("Nota 4: ");
    scanf("%f", &alunos[i].n4);

    printf("Faltas: ");
    scanf("%d", &alunos[i].faltas);

    printf("\n");
}// chave lerAluno


// Função para exibir o ALUNO
void exibirAluno(int i){
    if(i < 0 || i >= 5){
        printf("Indice de aluno invalido.\n");
        return;
    }
    printf("\nDADOS DO ALUNO %d\n", i + 1);
    printf("Nome: %s\n", alunos[i].nome);
    printf("Matricula: %s\n", alunos[i].matricula);
    printf("Notas: %.1f, %.1f, %.1f, %.1f\n", alunos[i].n1, alunos[i].n2, alunos[i].n3, alunos[i].n4);
    printf("Faltas: %d\n", alunos[i].faltas);
    printf("Media: %.2f\n", mediaAluno(i));
    printf("Situacao: "); situacaoAluno(i);
    printf("---------------------------\n");

}// chave exibirAluno


// Função para calcular e retornar a média do aluno
float mediaAluno(int i){
    float media;
    media = (alunos[i].n1 + alunos[i].n2 + alunos[i].n3 + alunos[i].n4) / 4.0;
    return media;
}// chave mediaAluno


// Função para escrever a situação do aluno
void situacaoAluno(int i){
 
    // Reprovação por faltas
    int limiteFaltas =15;
    if(alunos[i].faltas > limiteFaltas){
        printf("Reprovado por faltas.\n");
        return; 
    }

    float media = mediaAluno(i); // Pega a média

    // Aprovação ou reprovação por notas
    if(media >= 7.0){
        printf("Aprovado!\n");
    } else if (media >= 4.0) {
        printf("Em recuperacao.\n");
    } else {
        printf("Reprovado por nota.\n");
    }
}// chave situacaoAluno






