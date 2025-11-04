#include <stdio.h>
#include <stdlib.h> // para malloc e free
#include <string.h> // para strcmp (comparar strings do CPF)
#include "lista.h"

// usa strcmp para comparar duas strings e retorna o resultado
// esta função será chamada pelo 'inserirOrdenado'
int compararCPF(const char* cpf1, const char* cpf2) {
	// strcmp é a função padrão do C (da string.h)
	// ela faz exatamente o que o exemplo do professor mostra
	// retorna < 0 se string1 vem ANTES de string2
	// retorna > 0 se string1 vem DEPOIS de string2
	// retorna 0 se são IGUAIS
	return strcmp(cpf1, cpf2);
}


// função para inicializar a lista (criar vazia)
void inicializar(tLista *lista) {
	lista->head = NULL; // o primeiro (head) aponta para nada
	lista->tail = NULL; // o último (tail) aponta para nada
	lista->size = 0;	// o tamanho é 0
}

// função para verificar se a lista está vazia
int estaVazia(tLista *lista) {
	// se o tamanho for 0, retorna 1 (verdadeiro). senão, retorna 0 (falso).
	return (lista->size == 0);
}

// função auxiliar para ler os dados de um contato
tContato lerContato() {
	tContato c;
	
	// usamos " %[^\n]" para ler strings com espaços (como o nome)
	// o espaço antes do % "consome" o Enter que sobrou do scanf anterior
	printf("digite o CPF (somente numeros): ");
	scanf("%11s", c.cpf); // lê até 11 caracteres para o CPF
	
	printf("digite o Nome: ");
	scanf(" %[^\n]", c.nome);
	
	printf("digite o E-mail: ");
	scanf(" %[^\n]", c.email);
	
	printf("digite o Telefone: ");
	scanf(" %[^\n]", c.telefone);
	
	return c;
}


// inserir um novo contato (ordenado)
// ela usa compararCPF() e os ponteiros head/tail
int inserirOrdenado(tLista *lista, tContato novoContato) {
	
	// aloca memória para o novo nó
	tNo* novoNo = (tNo*) malloc(sizeof(tNo));
	if (novoNo == NULL) {
		printf("\nErro! falha ao alocar memoria (malloc).\n");
		return 0; // retorna 0 (erro)
	}
	
	// copia os dados para o nó
	novoNo->dado = novoContato;
	novoNo->prox = NULL;
	novoNo->ant = NULL;

	// lógica para encontrar a posição correta

	// CASO 1: a lista está vazia
	if (estaVazia(lista)) {
		lista->head = novoNo;
		lista->tail = novoNo;
	} 
	// CASO 2: o novo CPF é menor que o primeiro (insere no início)
	// chamada da função compararCPF retorna < 0
	else if (compararCPF(novoContato.cpf, lista->head->dado.cpf) < 0) {
		novoNo->prox = lista->head; 
		lista->head->ant = novoNo; 
		lista->head = novoNo;	 
	}
	// CASO 3: inserir no meio ou no fim
	else {
		tNo* atual = lista->head;
		
		// loop: avança 'atual' ENQUANTO não chegar no fim E
		// o CPF novo for MAIOR que o CPF do próximo nó
		// chamada da função compararCPF retorna > 0
		while (atual->prox != NULL && compararCPF(novoContato.cpf, atual->prox->dado.cpf) > 0) {
			atual = atual->prox; // avança para o próximo
		}
		
		// checagem de CPF duplicado, requisito do trabalho
		// chamada da função compararCPF retorna == 0
		if (compararCPF(novoContato.cpf, atual->dado.cpf) == 0) {
			 printf("\nErro! CPF ja cadastrado. insercao cancelada.\n");
			 free(novoNo); 
			 return 0; 
		}
		// checa também o próximo, caso o loop tenha parado exatamente antes de um igual
		if (atual->prox != NULL && compararCPF(novoContato.cpf, atual->prox->dado.cpf) == 0) {
			 printf("\nErro! CPF ja cadastrado. insercao cancelada.\n");
			 free(novoNo); 
			 return 0; 
		}

		// se 'atual->prox' é NULL, chegamos ao fim. insere no Fim.
		if (atual->prox == NULL) {
			atual->prox = novoNo;	
			novoNo->ant = atual;	
			lista->tail = novoNo; // o tail agora é o novo nó
		}
		// senão, insere no Meio, entre 'atual' e 'atual->prox'
		else {
			novoNo->prox = atual->prox; 
			novoNo->ant = atual;	 
			atual->prox->ant = novoNo; 
			atual->prox = novoNo;	 
		}
	}

	// atualiza o tamanho
	lista->size++;
	return 1; // sucesso
}

// lista todos os contatos, com endereços
// esta função é chamada pelo main ao final de cada operação
void listarTodos(tLista *lista) {
	if (estaVazia(lista)) {
		printf("\nA lista de contatos esta vazia.\n");
		return;
	}

	printf("\n--- LISTA DE CONTATOS ATUAL (%d) ---\n", lista->size);
	
	tNo* atual = lista->head; // começa pelo primeiro (head)
	int i = 1;

	// loop que percorre a lista até 'atual' ser NULL , fim da lista
	while (atual != NULL) {
		printf("\n[%d] nome: %s\n", i, atual->dado.nome);
		printf("	CPF: %s\n", atual->dado.cpf);
		printf("	e-mail: %s\n", atual->dado.email);
		printf("	telefone: %s\n", atual->dado.telefone);
		printf("	enderecos de memoria:\n");
		printf("	- anterior (ant): %p\n", atual->ant);
		printf("	- atual (this):	 %p\n", atual);
		printf("	- proximo (prox): %p\n", atual->prox);

		atual = atual->prox; // vai para o próximo nó
		i++;
	}
	printf("\n--- FIM DA LISTA ---\n");
}


// consulta contato por posição
void consultarPorPosicao(tLista *lista, int pos) {
	// validação da posição
	if (estaVazia(lista) || pos < 1 || pos > lista->size) {
		printf("\nPosicao invalida ou lista vazia. (posicoes validas: 1 a %d)\n", lista->size);
		return;
	}

	tNo* atual = lista->head; // começa pelo primeiro (head)
	// loop para encontrar o nó na posição 'pos'
	// começa em 1 e vai até < pos
	for (int i = 1; i < pos; i++) {
		atual = atual->prox;
	}

	// exibe os dados do nó encontrado
	printf("\n--- CONSULTA POSICAO %d ---\n", pos);
	printf("nome: %s\n", atual->dado.nome);
	printf("CPF: %s\n", atual->dado.cpf);
	printf("e-mail: %s\n", atual->dado.email);
	printf("telefone: %s\n", atual->dado.telefone);
	printf("---------------------------\n");
}


// remove contatos de qualquer posição, início, meio ou fim
int removerPorPosicao(tLista *lista, int pos) {
	// validação da posição
	if (estaVazia(lista) || pos < 1 || pos > lista->size) {
		printf("\nPosicao invalida ou lista vazia. (posicoes validas: 1 a %d)\n", lista->size);
		return 0; // erro
	}

	tNo* noParaRemover = NULL;

	// CASO 1: remoção do Início, pos == 1
	if (pos == 1) {
		noParaRemover = lista->head; // guarda quem será removido
		lista->head = noParaRemover->prox; // o início (head) agora é o segundo
		
		// se a lista *não* ficou vazia após a remoção
		if (lista->head != NULL) {
			lista->head->ant = NULL; // o anterior do novo início é NULL
		} else {
			// se a lista ficou vazia, o 'tail' (último) também deve ser NULL
			lista->tail = NULL;
		}
	}
	// CASO 2: remoção do Fim (pos == lista->size)
	else if (pos == lista->size) {
		noParaRemover = lista->tail;	 // guarda quem será removido
		lista->tail = noParaRemover->ant; // o fim (tail) agora é o penúltimo
		lista->tail->prox = NULL;	 // o próximo do novo fim é NULL
	}
	// CASO 3: remoção do Meio
	else {
		// encontra o nó (como na consulta)
		noParaRemover = lista->head; // começa pelo primeiro (head)
		for (int i = 1; i < pos; i++) {
			noParaRemover = noParaRemover->prox;
		}

		// refaz as "pontes" 
		noParaRemover->ant->prox = noParaRemover->prox; // o próximo do anterior aponta para o próximo do removido
		noParaRemover->prox->ant = noParaRemover->ant; // o anterior do próximo aponta para o anterior do removido
	}

	// guarda o nome para a mensagem de sucesso
	char nomeRemovido[100];
	strcpy(nomeRemovido, noParaRemover->dado.nome);

	// libera a memória do nó removido
	free(noParaRemover);
	lista->size--; // decrementa o tamanho

	printf("\nfeito! contato '%s' removido da posicao %d.\n", nomeRemovido, pos);
	return 1; // sucesso
}

// função para liberar toda a memória da lista
void liberarLista(tLista *lista) {
	tNo* atual = lista->head; // começa pelo primeiro
	tNo* proximoNo = NULL;

	printf("\nliberando memoria da lista...\n");

	// loop: percorre a lista inteira
	while (atual != NULL) {
		// guarda quem é o próximo ,antes de apagar o atual
		proximoNo = atual->prox;
	
		// libera a memória do nó atual
		free(atual);
	
		// avança para o próximo nó
		atual = proximoNo;
	}

	// ao final, reseta o header da lista para o estado inicial (vazia)
	lista->head = NULL;
	lista->tail = NULL;
	lista->size = 0;

	printf("memoria liberada com sucesso.\n");
}