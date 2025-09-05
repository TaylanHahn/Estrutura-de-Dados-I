/*
EXERCICIO 2
Com base no código disponível no moodle, responda:
a - quantos bytes o vetor alunos ocupa? dica: use sizeof
b - quantos bytes uma variável do tipo aluno ocupa?
c - quanto de memória (em bytes) foi alocado para este programa? considere apenas a função principal e a alocação dinamica


*/

#include <stdio.h>
#include <stdlib.h>
#define MAX 5

    typedef struct{
    	char nome[150];
    	char telefone[15];
    	int idade;
    	char contato[150];
    } aluno;

void leitura(aluno *a){
	printf("\nDigite o nome do aluno: ");
	gets((*a).nome);
	printf("\nDigite a idade do aluno: ");
	scanf("%d",&(*a).idade); getchar();
	printf("\nNome do Contato de emergencia: ");
	gets((*a).contato);
	printf("\nDigite o Telefone do Contato: ");
	gets(a->telefone);
}
void imprime(aluno a){
	printf("Nome: %s\t Idade: %d anos\n",a.nome,a.idade);
	printf("Contato: %s \tTelefone:%s\n",a.contato,a.telefone);
}

int main(int argc, char *argv[]) {
	aluno* alunos[MAX];	
	int i,num;
	
		// a- Verificando quantos bytes o vetor aluno ocupa
	size_t tamanho = sizeof(alunos);
	printf("\nO tamanho é de %zu bytes", tamanho);
	
	// b- Verificando quantos bytes uma variável do tipo aluno ocupa
	int tbytes = sizeof(aluno);
	printf("\nO tamanho ocupado é de %d bytes", tbytes);
	
    // c - quanto de memória foi alocada
    size_t mem_stack = sizeof(alunos) + sizeof(i) + sizeof(num);
    size_t mem_heap = MAX * sizeof(aluno);
    size_t mem_total = mem_stack + mem_heap;
    printf("Memoria total alocada (Stack + Heap): %zu bytes\n", mem_total);
    printf("%zu bytes na Stack + %zu bytes na Heap)\n", mem_stack, mem_heap);
	
	
	for(i=0;i<MAX;i++){
	    alunos[i]=0;
	}
	
	for(i=0;i<MAX;i++) {
		alunos[i]=(aluno*)malloc(sizeof(aluno));
		if(alunos[i]!=0)
			leitura(alunos[i]);
	}
	do{
		printf("\nDigite um numero de 1 a %d:",MAX);
		scanf("%d",&num);
		imprime(*alunos[num-1]);
	} while(num);
	
	for(i=0;i<MAX;i++){
		if(alunos[i]!=0) free(alunos[i]);
	}
	
	return 0;
}
