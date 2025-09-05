/*
EXERCICIO 3
Criar agenda:
Cada registro deve ter capacidade para armazenar o nome, telefone, celular, endereço e aniversário.
A agenda deve ser apresentar as opções: 
1- inserir
2-visualizar os dados de uma posição (perguntar a posição)
3-sair; (ficar em laço até o usuário escolher sair). 
Máximo de 100 registros. (criar vetor de 100 posições, cada posição é um ponteiro para contato).
Cada contato é criado dinamicamente ocupando as posições no vetor sequencialmente.
Não esqueça de liberar a memória no final do programa, antes de sair.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#define MAX 100 // maximo definido em 100

typedef struct {
    char nome[100];
    char telefone[15];
    char celular[15];
    char endereco[150];
    char aniversario[11];
} contato;

// Função para inserir um novo contato na agenda
void inserir(Contato* agenda[], int *total_contatos) {
    // Verifica se a agenda está cheia
    if (*total_contatos == MAX) {
        printf("\nAgenda cheia! Nao e possivel adicionar mais contatos.\n");
        return;
    }

    // alocação de memória
    Contato* novo_contato = (Contato*) malloc(sizeof(Contato));
    
    // verifica se a alocação deu certo
    if (novo_contato == NULL) {
        printf("\nFalha ao alocar memoria para o novo contato!\n");
        return;
    }

    printf("\n--- Inserindo Novo Contato ---\n");
    
    printf("Digite o nome: ");
    gets(novo_contato->nome); 
    printf("Digite o telefone fixo: ");
    gets(novo_contato->telefone);
    printf("Digite o celular: ");
    gets(novo_contato->celular);
    printf("Digite o endereco: ");
    gets(novo_contato->endereco);
    printf("Digite o aniversario (DD/MM/AAAA): ");
    gets(novo_contato->aniversario);
    
    // adiciona o ponteiro do novo contato no vetor, na próxima posição livre
    agenda[*total_contatos] = novo_contato;
    (*total_contatos)++; // incrementa o contador de contatos

    printf("\nContato inserido com sucesso na posicao %d!\n", *total_contatos);
}

// Função para ver um contato em uma posição específica
void visualizar(Contato* agenda[], int total_contatos) {
    int posicao;

    if (total_contatos == 0) {
        printf("\nAVISO: A agenda esta vazia. Nao ha contatos para visualizar.\n");
        return;
    }
    
    printf("\n--- Visualizar Contato ---\n");
    printf("Atualmente ha %d contato(s) na agenda.\n", total_contatos);
    printf("Digite a posicao que deseja visualizar (de 1 a %d): ", total_contatos);
    scanf("%d", &posicao);
    getchar(); // limpa o buffer

    if (posicao < 1 || posicao > total_contatos) {
        printf("\nPosicao invalida!\n");
        return;
    }
    
    // Pega o ponteiro do contato na posição desejada 
    Contato* contato_selecionado = agenda[posicao - 1];
    
    printf("\n--- Dados do Contato na Posicao %d ---\n", posicao);
    printf("Nome: %s\n", contato_selecionado->nome);
    printf("Telefone: %s\n", contato_selecionado->telefone);
    printf("Celular: %s\n", contato_selecionado->celular);
    printf("Endereco: %s\n", contato_selecionado->endereco);
    printf("Aniversario: %s\n", contato_selecionado->aniversario);
}

int main(int argc, char *argv[]) {
    Contato* agenda[MAX];
    int total_contatos = 0;
    int opcao;
    int i;

    for (i = 0; i < MAX; i++) {
        agenda[i] = NULL;
    }

    do {
        printf("\n--- AGENDA DE CONTATOS ---\n");
        printf("1 - Inserir novo contato\n");
        printf("2 - Visualizar contato por posicao\n");
        printf("3 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); 
        
        // switch do menu
        switch(opcao) {
            case 1:
                inserir(agenda, &total_contatos);
                break;
            case 2:
                visualizar(agenda, total_contatos);
                break;
            case 3:
                printf("\nSaindo do programa...\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }

    } while (opcao != 3); // O laço continua até o usuário digitar 3

    printf("Liberando a memoria alocada...\n");
    for (i = 0; i < total_contatos; i++) {
        // se o ponteiro naquela posição não for nulo, libera a memória
        if (agenda[i] != NULL) {
            free(agenda[i]);
        }
    }
    printf("Memoria liberada. Programa encerrado.\n");
    
    return 0;
}

