#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para armazenar os dados de um Contato
typedef struct {
    char nome[50];
    char telefone[20];
} Contato;

// Estrutura do Nó da pilha (cada "caixinha" da nossa lista)
// Contém um contato e um ponteiro para o próximo nó
typedef struct no {
    Contato contato;
    struct no *proximo;
} No;

// --- Funções da Pilha ---

// Função para empilhar (push) um novo contato no topo da pilha
// Recebe o ponteiro para o ponteiro do topo (**topo) para poder modificá-lo
void push(No **topo, Contato c) {
    // 1. Aloca memória para um novo nó
    No *novo = malloc(sizeof(No));

    if (novo) {
        // 2. Copia os dados do contato para o novo nó
        novo->contato = c;
        // 3. O "próximo" do novo nó aponta para o antigo topo
        novo->proximo = *topo;
        // 4. O topo da pilha agora é o novo nó
        *topo = novo;
    } else {
        printf("Erro ao alocar memoria!\n");
    }
}

// Função para desempilhar (pop) um contato do topo da pilha
// Retorna o Contato que foi removido
Contato pop(No **topo) {
    // Verifica se a pilha não está vazia
    if (*topo != NULL) {
        No *remover = *topo; // Guarda o nó do topo que será removido
        Contato c = remover->contato; // Pega os dados do contato antes de remover

        // O topo da pilha passa a ser o próximo elemento
        *topo = remover->proximo;

        // Libera a memória do nó que foi removido
        free(remover);

        return c; // Retorna o contato que estava no topo
    } else {
        // Se a pilha estiver vazia, imprime o erro
        printf("ERRO: A pilha esta vazia! Nao e possivel remover.\n");
        // Retorna um contato vazio para indicar o erro
        Contato c_vazio = {"VAZIO", "VAZIO"};
        return c_vazio;
    }
}

// Função auxiliar para imprimir os dados de um contato
void imprimir_contato(Contato c) {
    // Verifica se o contato não é o de erro
    if (strcmp(c.nome, "VAZIO") != 0) {
       printf("--> Contato Removido: | Nome: %-10s | Telefone: %-15s |\n", c.nome, c.telefone);
    }
}


// --- Função Principal com os 7 Passos ---

int main() {
    // A pilha começa vazia, então o ponteiro do topo aponta para NULL
    No *topo = NULL;
    Contato c;

    printf("### INICIO DA OPERACAO DA PILHA ###\n\n");

    // 1- Inserir contatos de 1 a 3
    printf("--- Passo 1: Inserindo 3 contatos ---\n");
    strcpy(c.nome, "Alice");
    strcpy(c.telefone, "9999-1111");
    push(&topo, c);
    printf("Empilhado: Alice\n");

    strcpy(c.nome, "Beto");
    strcpy(c.telefone, "8888-2222");
    push(&topo, c);
    printf("Empilhado: Beto\n");

    strcpy(c.nome, "Carlos");
    strcpy(c.telefone, "7777-3333");
    push(&topo, c);
    printf("Empilhado: Carlos\n\n");
    // Pilha atual: Carlos -> Beto -> Alice

    // 2- Remover um Contato e imprimir em tela os dados
    printf("--- Passo 2: Removendo um contato ---\n");
    c = pop(&topo);
    imprimir_contato(c);
    printf("\n");
    // Pilha atual: Beto -> Alice

    // 3 - Remover um Contato e imprimir em tela os dados
    printf("--- Passo 3: Removendo um contato ---\n");
    c = pop(&topo);
    imprimir_contato(c);
    printf("\n");
    // Pilha atual: Alice

    // 4 - Empilhar um novo contato
    printf("--- Passo 4: Empilhando um novo contato ---\n");
    strcpy(c.nome, "Daniel");
    strcpy(c.telefone, "6666-4444");
    push(&topo, c);
    printf("Empilhado: Daniel\n\n");
    // Pilha atual: Daniel -> Alice

    // 5 - Remover um Contato e imprimir em tela os dados
    printf("--- Passo 5: Removendo um contato ---\n");
    c = pop(&topo);
    imprimir_contato(c);
    printf("\n");
    // Pilha atual: Alice

    // 6 - Remover um Contato e imprimir em tela os dados
    printf("--- Passo 6: Removendo um contato ---\n");
    c = pop(&topo);
    imprimir_contato(c);
    printf("\n");
    // Pilha atual: VAZIA

    // 7 – Tentar remover contato (deve dar erro)
    printf("--- Passo 7: Tentando remover de uma pilha vazia ---\n");
    c = pop(&topo);
    imprimir_contato(c); // Não vai imprimir nada útil, pois a função pop já mostrou o erro
    printf("\n");

    printf("### FIM DA OPERACAO ###\n");

    return 0;
}
