#include <stdio.h>
#include <stdlib.h> // para malloc e free
#include <string.h> // para strcmp (comparar strings do CPF)
#include <ctype.h>  // add por Taylan: (Req 1 e 4) para isdigit() e tolower()
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

// add por Taylan: (Req 1) Função auxiliar para validar o CPF
//               Verifica se tem 11 dígitos e se são todos numéricos
static int validarCPF(const char* cpf) {
	// checa o tamanho
	if (strlen(cpf) != 11) {
		return 0; // inválido (tamanho diferente de 11)
	}
	
	// checa se todos os caracteres são dígitos
	for (int i = 0; i < 11; i++) {
		if (!isdigit(cpf[i])) {
			return 0; // inválido (não é um dígito)
		}
	}
	return 1; // válido
}

// add por Taylan: (Req 2) Função auxiliar para checar strings vazias ou só com espaços
static int ehStringVazia(const char* str) {
	if (str == NULL) return 1;
	while (*str) {
		// se encontrar qualquer caractere que não seja espaço, a string não é vazia
		if (!isspace((unsigned char)*str)) {
			return 0;
		}
		str++;
	}
	return 1; // a string é vazia ou só contém espaços
}

// função auxiliar para ler os dados de um contato
// AGORA COM VALIDAÇÃO
tContato lerContato() {
	tContato c;
	char buffer[150]; // buffer temporário para leitura
	
	// add por Taylan: (Req 1) Loop de validação do CPF
	do {
		printf("digite o CPF (exatos 11 numeros): ");
		scanf("%11s", c.cpf); // lê até 11 caracteres para o CPF
		// consome o resto da linha (ex: o Enter) para não atrapalhar o próximo scanf
		while (getchar() != '\n'); 
		
		if (!validarCPF(c.cpf)) {
			printf("\nErro! CPF invalido. Deve conter 11 digitos numericos.\n");
		}
	} while (!validarCPF(c.cpf)); // repete enquanto for inválido

	// add por Taylan: (Req 2) Loop de validação de entrada vazia (Nome)
	do {
		printf("digite o Nome: ");
		scanf(" %[^\n]", buffer); // lê a string no buffer
		if (ehStringVazia(buffer)) {
			printf("\nErro! O nome nao pode ser vazio.\n");
		}
	} while (ehStringVazia(buffer));
	strcpy(c.nome, buffer); // copia do buffer para o contato

	// add por Taylan: (Req 2) Loop de validação de entrada vazia (E-mail)
	do {
		printf("digite o E-mail: ");
		scanf(" %[^\n]", buffer);
		if (ehStringVazia(buffer)) {
			printf("\nErro! O e-mail nao pode ser vazio.\n");
		}
	} while (ehStringVazia(buffer));
	strcpy(c.email, buffer);

	// add por Taylan: (Req 2) Loop de validação de entrada vazia (Telefone)
	do {
		printf("digite o Telefone: ");
		scanf(" %[^\n]", buffer);
		if (ehStringVazia(buffer)) {
			printf("\nErro! O telefone nao pode ser vazio.\n");
		}
	} while (ehStringVazia(buffer));
	strcpy(c.telefone, buffer);
	
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
// AGORA OTIMIZADO
void consultarPorPosicao(tLista *lista, int pos) {
	// validação da posição
	if (estaVazia(lista) || pos < 1 || pos > lista->size) {
		printf("\nPosicao invalida ou lista vazia. (posicoes validas: 1 a %d)\n", lista->size);
		return;
	}

	tNo* atual; // add por Taylan: movida a declaração para fora

	// add por Taylan: (Req 6) Otimização de busca
	// Se a posição está na segunda metade da lista, busca de trás para frente (pelo tail)
	if (pos > lista->size / 2) {
		// printf("debug: buscando pelo FIM\n"); // (opcional para debug)
		atual = lista->tail; // começa pelo último
		// loop para encontrar o nó na posição 'pos' (andando para trás)
		for (int i = lista->size; i > pos; i--) {
			atual = atual->ant; // vai para o anterior
		}
	} 
	// Senão (está na primeira metade), faz a busca normal (pelo head)
	else {
		// printf("debug: buscando pelo INICIO\n"); // (opcional para debug)
		atual = lista->head; // começa pelo primeiro (head)
		// loop para encontrar o nó na posição 'pos' (andando para frente)
		for (int i = 1; i < pos; i++) {
			atual = atual->prox;
		}
	}
	// add por Taylan: fim da otimização
	

	// exibe os dados do nó encontrado
	printf("\n--- CONSULTA POSICAO %d ---\n", pos);
	printf("nome: %s\n", atual->dado.nome);
	printf("CPF: %s\n", atual->dado.cpf);
	printf("e-mail: %s\n", atual->dado.email);
	printf("telefone: %s\n", atual->dado.telefone);
	printf("---------------------------\n");
}


// remove contatos de qualquer posição, início, meio ou fim
// AGORA OTIMIZADO
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
	// CASO 3: remoção do Meio (AGORA OTIMIZADO)
	else {
		// add por Taylan: (Req 6) Otimização de busca para remoção no meio
		// Se a posição está na segunda metade da lista, busca de trás para frente (pelo tail)
		if (pos > lista->size / 2) {
			// printf("debug: removendo (busca pelo FIM)\n"); // (opcional para debug)
			noParaRemover = lista->tail; // começa pelo último
			for (int i = lista->size; i > pos; i--) {
				noParaRemover = noParaRemover->ant; // vai para o anterior
			}
		} 
		// Senão (está na primeira metade), faz a busca normal (pelo head)
		else {
			// printf("debug: removendo (busca pelo INICIO)\n"); // (opcional para debug)
			noParaRemover = lista->head; // começa pelo primeiro (head)
			for (int i = 1; i < pos; i++) {
				noParaRemover = noParaRemover->prox;
			}
		}
		// add por Taylan: fim da otimização

		// refaz as "pontes" (esta lógica é a mesma, independente da direção da busca)
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


// add por Taylan: (Req 3 e 5) Função auxiliar para BUSCAR UM NÓ por CPF
// Esta função é interna (static) e será usada por consultarPorCPF e alterarContato
// Retorna o ponteiro para o nó (tNo*) se achar, ou NULL se não achar.
static tNo* buscarNoPorCPF(tLista *lista, const char* cpfBusca) {
	if (estaVazia(lista)) {
		return NULL;
	}
	
	tNo* atual = lista->head;
	
	// percorre a lista
	while(atual != NULL) {
		// compara o CPF buscado com o CPF do nó atual
		int cmp = compararCPF(cpfBusca, atual->dado.cpf);
		
		if (cmp == 0) {
			return atual; // achou! retorna o ponteiro para o nó
		}
		
		// Otimização: se o CPF buscado já é MENOR que o atual,
		// e a lista está ordenada, não precisamos procurar mais.
		if (cmp < 0) {
			return NULL; // não vai achar
		}
		
		atual = atual->prox; // avança para o próximo
	}
	
	return NULL; // não achou (chegou ao fim da lista)
}


// add por Taylan: (Req 3) Implementação da função de Consultar por CPF
void consultarPorCPF(tLista *lista) {
	if (estaVazia(lista)) {
		printf("\nA lista esta vazia. Nao ha o que consultar.\n");
		return;
	}
	
	char cpfBusca[12];
	printf("\nQual CPF voce quer consultar? (11 digitos): ");
	scanf("%11s", cpfBusca);
	
	// usa a função auxiliar para encontrar o nó
	tNo* noEncontrado = buscarNoPorCPF(lista, cpfBusca);
	
	// se a função retornou um ponteiro (não NULL)
	if (noEncontrado != NULL) {
		// exibe os dados do nó encontrado
		printf("\n--- CONSULTA CPF %s ---\n", cpfBusca);
		printf("nome: %s\n", noEncontrado->dado.nome);
		printf("CPF: %s\n", noEncontrado->dado.cpf);
		printf("e-mail: %s\n", noEncontrado->dado.email);
		printf("telefone: %s\n", noEncontrado->dado.telefone);
		printf("---------------------------\n");
	} else {
		// se a função retornou NULL
		printf("\nErro! CPF '%s' nao encontrado na lista.\n", cpfBusca);
	}
}

// add por Taylan: (Req 4) Implementação da função de Buscar por Nome (parcial)
void buscarPorNome(tLista *lista) {
	if (estaVazia(lista)) {
		printf("\nA lista esta vazia. Nao ha o que buscar.\n");
		return;
	}
	
	char nomeBusca[100];
	char nomeBuscaLower[100];
	char nomeContatoLower[100];
	int encontrou = 0; // flag para saber se achamos alguém
	
	printf("\nQual nome (ou parte do nome) voce quer buscar? ");
	scanf(" %[^\n]", nomeBusca);
	
	// converte o termo de busca para minúsculo
	for(int i = 0; nomeBusca[i]; i++){
		nomeBuscaLower[i] = tolower(nomeBusca[i]);
	}
	nomeBuscaLower[strlen(nomeBusca)] = '\0'; // finaliza a string

	
	printf("\n--- RESULTADOS DA BUSCA POR '%s' ---\n", nomeBusca);
	
	tNo* atual = lista->head;
	while (atual != NULL) {
		// copia o nome do contato para um buffer temporário
		strcpy(nomeContatoLower, atual->dado.nome);
		// converte o nome do contato para minúsculo
		for(int i = 0; nomeContatoLower[i]; i++){
			nomeContatoLower[i] = tolower(nomeContatoLower[i]);
		}
		
		// usa strstr() para ver se o termo de busca (minúsculo)
		// está contido no nome do contato (minúsculo)
		if (strstr(nomeContatoLower, nomeBuscaLower) != NULL) {
			// exibe os dados do nó encontrado
			printf("\nNome: %s (CPF: %s)\n", atual->dado.nome, atual->dado.cpf);
			printf("  E-mail: %s\n", atual->dado.email);
			printf("  Telefone: %s\n", atual->dado.telefone);
			encontrou = 1; // marca que encontramos pelo menos 1
		}
		
		atual = atual->prox; // vai para o próximo
	}
	
	// se a flag 'encontrou' continuar 0, ninguém foi achado
	if (encontrou == 0) {
		printf("\nNenhum contato encontrado com o termo '%s'.\n", nomeBusca);
	}
	
	printf("-------------------------------------\n");
}


// add por Taylan: (Req 5) Implementação da função de Alterar Contato
void alterarContato(tLista *lista) {
	if (estaVazia(lista)) {
		printf("\nA lista esta vazia. Nao ha o que alterar.\n");
		return;
	}
	
	char cpfBusca[12];
	printf("\nQual o CPF do contato que voce quer ALTERAR? (11 digitos): ");
	scanf("%11s", cpfBusca);
	
	// usa a função auxiliar para encontrar o nó
	tNo* noParaAlterar = buscarNoPorCPF(lista, cpfBusca);
	
	// se a função retornou NULL, não achou
	if (noParaAlterar == NULL) {
		printf("\nErro! CPF '%s' nao encontrado. Nao e possivel alterar.\n", cpfBusca);
		return;
	}
	
	// se achou, mostra os dados atuais e pede os novos
	printf("\nContato encontrado: '%s' (CPF: %s)\n", noParaAlterar->dado.nome, noParaAlterar->dado.cpf);
	printf("AVISO: O CPF nao pode ser alterado (e a chave da lista).\n");
	
	char buffer[150]; // buffer temporário para leitura
	
	// Pede o NOVO NOME (com a mesma validação de entrada vazia)
	do {
		printf("Digite o NOVO Nome (atual: %s): ", noParaAlterar->dado.nome);
		scanf(" %[^\n]", buffer);
		if (ehStringVazia(buffer)) {
			printf("\nErro! O nome nao pode ser vazio.\n");
		}
	} while (ehStringVazia(buffer));
	strcpy(noParaAlterar->dado.nome, buffer); // atualiza o nome no nó

	// Pede o NOVO E-MAIL
	do {
		printf("Digite o NOVO E-mail (atual: %s): ", noParaAlterar->dado.email);
		scanf(" %[^\n]", buffer);
		if (ehStringVazia(buffer)) {
			printf("\nErro! O e-mail nao pode ser vazio.\n");
		}
	} while (ehStringVazia(buffer));
	strcpy(noParaAlterar->dado.email, buffer); // atualiza o e-mail no nó

	// Pede o NOVO TELEFONE
	do {
		printf("Digite o NOVO Telefone (atual: %s): ", noParaAlterar->dado.telefone);
		scanf(" %[^\n]", buffer);
		if (ehStringVazia(buffer)) {
			printf("\nErro! O telefone nao pode ser vazio.\n");
		}
	} while (ehStringVazia(buffer));
	strcpy(noParaAlterar->dado.telefone, buffer); // atualiza o telefone no nó
	
	printf("\nFeito! Contato (CPF: %s) alterado com sucesso.\n", cpfBusca);
}