/*
EXERCICIO 6 
Reescreva o exercício 3 sem usar variáveis globais.
Você vai precisar passar o vetor como parâmetro, nos códigos que usam função;
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

// Assinaturas das funções
void lerAluno(aluno vAlunos[], int i);
void exibirAluno(aluno vAlunos[], int i);
float mediaAluno(aluno vAlunos[], int i); 
void situacaoAluno(aluno vAlunos[], int i); 

// Função PRINCIPAL
int main(){
    int i;
    char opcao = '.';
    
    // Vetor com 5 alunos (agora dentro da MAIN)
    aluno alunos[5];

    // laço para ler os 5 alunos
    for(i=0; i<5; i++){
        lerAluno(alunos, i);
    }

    printf("\nGostaria de ver os dados registrados no sistema? (S/N): ");
    scanf(" %c", &opcao);

    if(opcao == 'S' || opcao == 's'){
        printf("\n======== EXIBINDO DADOS DOS ALUNOS ========\n");
        for(i=0; i<5; i++){
            exibirAluno(alunos, i);
        }
    } else {
        printf("Encerrando o programa...\n");
    }
    
    return 0;
}//chave main


// -------------- FUNÇÕES ------------------

// Função para ler UM aluno
void lerAluno(aluno vAlunos[], int i){
    if(i < 0 || i >= 5){
        printf("Indice de aluno invalido.\n");
        return;
    }

    printf("\nCADASTRO DO ALUNO %d\n", i + 1);
    printf("---------------------------\n");

    printf("Nome do Aluno: ");
    scanf(" %[^\n]", vAlunos[i].nome);

    printf("Matricula: ");
    scanf(" %[^\n]", vAlunos[i].matricula);

    printf("Nota 1: ");
    scanf("%f", &vAlunos[i].n1);
    printf("Nota 2: ");
    scanf("%f", &vAlunos[i].n2);
    printf("Nota 3: ");
    scanf("%f", &vAlunos[i].n3);
    printf("Nota 4: ");
    scanf("%f", &vAlunos[i].n4);

    printf("Faltas: ");
    scanf("%d", &vAlunos[i].faltas);

    printf("\n");
}// chave lerAluno


// Função para exibir o ALUNO
void exibirAluno(aluno vAlunos[], int i){
    if(i < 0 || i >= 5){
        printf("Indice de aluno invalido.\n");
        return;
    }
    printf("\nDADOS DO ALUNO %d\n", i + 1);
    printf("Nome: %s\n", vAlunos[i].nome);
    printf("Matricula: %s\n", vAlunos[i].matricula);
    printf("Notas: %.1f, %.1f, %.1f, %.1f\n", vAlunos[i].n1, vAlunos[i].n2, vAlunos[i].n3, vAlunos[i].n4);
    printf("Faltas: %d\n", vAlunos[i].faltas);
    printf("Media: %.2f\n", mediaAluno(vAlunos, i));
    printf("Situacao: "); situacaoAluno(vAlunos, i);
    printf("---------------------------\n");

}// chave exibirAluno


// Função para calcular e retornar a média do aluno
float mediaAluno(aluno vAlunos[], int i){
    float media;
    media = (vAlunos[i].n1 + vAlunos[i].n2 + vAlunos[i].n3 + vAlunos[i].n4) / 4.0;
    return media;
}// chave mediaAluno


// Função para escrever a situação do aluno
void situacaoAluno(aluno vAlunos[], int i){
 
    // Reprovação por faltas
    int limiteFaltas = 15;
    if(vAlunos[i].faltas > limiteFaltas){
        printf("Reprovado por faltas.\n");
        return; 
    }

    // Repassa o vetor para a função mediaAluno
    float media = mediaAluno(vAlunos, i);

    // Aprovação ou reprovação por notas
    if(media >= 7.0){
        printf("Aprovado!\n");
    } else if (media >= 4.0) {
        printf("Em recuperacao.\n");
    } else {
        printf("Reprovado por nota.\n");
    }
}// chave situacaoAluno


