/*
EXERCICIO 1
No exemplo de código disponível slide anterior, não é verificado se a função malloc
retornou zero (ocorre quando não foi possível alocar a memória). 
Altere o exemplo para realizar esta verificação.

*/
#include <string.h>
    typedef struct{
    char nome[40];
    char telefone[15];
    } contato;

    int main(){
        
    contato *teste;
    teste = (contato*)malloc(sizeof(contato));
    
    // verificação adicionada
    if(teste == NULL){
        printf("Não foi possível alocar a memória");
        return 1;
    }
	
	printf("Digite seu nome: ");
    gets((*teste).nome);
    strcpy((*teste).telefone, "1234567");
    printf("Nome = %s\nTelefone =  %s\n",(*teste).nome,(*teste).telefone);
	
	free(teste);
}
