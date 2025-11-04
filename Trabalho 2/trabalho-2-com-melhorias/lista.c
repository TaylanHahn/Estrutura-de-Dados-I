#include <stdio.h>
#include <stdlib.h> // para malloc e free
#include <string.h> // para strcmp (comparar strings do CPF)
#include "lista.h"

// --- MELHORIA 4: incluir a biblioteca ctype.h ---
// (necessária para a função tolower() da busca por nome)
// (e também para a 'isdigit()' da MELHORIA 1)
// #include <ctype.h> 

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
	
	// --- MELHORIA 1: validador de cpf ---
	// (implementar aqui um loop 'while' para validar o cpf)
	// 1. checar se 'c.cpf' tem exatamente 11 caracteres (usar 'strlen')
	// 2. checar se todos os 11 caracteres são números (usar 'isdigit' da ctype.h, ou comparar na tabela ascii)
	// 3. se não for válido, imprimir "cpf inválido! deve ter 11 números." e pedir para digitar de novo, até ser válido.
	// (lembre-se de incluir <ctype.h> no topo do arquivo .c para usar 'isdigit')
	
	printf("digite o Nome: ");
	scanf(" %[^\n]", c.nome);

	// --- MELHORIA 2: validar entrada vazia ---
	// (implementar aqui um loop 'while' para validar o nome)
	// 1. checar se o nome está vazio (ex: if (strlen(c.nome) == 0) )
	// 2. se estiver vazio, imprimir "nome não pode ficar em branco!" e pedir para digitar de novo.
	
	printf("digite o E-mail: ");
	scanf(" %[^\n]", c.email);
	// (opcional: implementar a melhoria 2 aqui também para o email)
	
	printf("digite o Telefone: ");
	scanf(" %[^\n]", c.telefone);
	// (opcional: implementar a melhoria 2 aqui também para o telefone)
	
	return c;
}


// inserir um novo contato (ordenado)
// (código original - sem alterações)
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

// lista todos os contatos (código original - sem alterações)
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

	// --- MELHORIA 6: otimização da busca (parte 1) ---
	// (substituir o 'for' loop abaixo por esta lógica)
	// 1. checar se a posição está na segunda metade da lista:
	//    if (pos > lista->size / 2) {
	// 2.  se sim, começar a busca pelo final (tail):
	//     atual = lista->tail;
	//     for (int i = lista->size; i > pos; i--) {
	//         atual = atual->ant;
	//     }
	// 3.  se não (else), fazer a busca normal pelo começo (head):
	//     atual = lista->head;
	//     for (int i = 1; i < pos; i++) {
	//         atual = atual->prox;
	//     }
	// }
	
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
		
		// --- MELHORIA 6: otimização da busca (parte 2) ---
		// (a lógica de otimização deve ser implementada aqui,
		// ANTES de encontrar o 'noParaRemover')
		
		// 1. checar if (pos > lista->size / 2)
		// 2.  se sim, buscar de trás para frente (usando 'tail' e 'ant')
		// 3.  se não, buscar de frente para trás (usando 'head' e 'prox')
		
		// o código abaixo é o que precisa ser otimizado:
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

// --- MELHORIA 3: implementação da função de busca por cpf ---
// (descomente o bloco abaixo para implementar a funcionalidade)
/*
void buscarPorCPF(tLista *lista) {
	if (estaVazia(lista)) {
		printf("\na lista esta vazia. nao ha o que buscar.\n");
		return;
	}
	
	char cpfBusca[12];
	printf("digite o CPF exato que deseja buscar: ");
	scanf("%11s", cpfBusca);
	
	// 1. criar um ponteiro 'tNo* atual = lista->head;'
	// 2. criar uma flag 'int achou = 0;'
	// 3. fazer um loop 'while (atual != NULL)'
	// 4.  dentro do loop, usar 'if (compararCPF(atual->dado.cpf, cpfBusca) == 0)'
	// 5.   se for igual, imprimir os dados do 'atual' (como na 'consultarPorPosicao'),
	//      mudar 'achou = 1;' e dar 'break;' no loop
	// 6.  avançar 'atual = atual->prox;'
	// 7. depois do loop, checar 'if (achou == 0)', se for, imprimir "contato não encontrado."
}
*/

// --- MELHORIA 4: implementação da função de busca por nome ---
// (descomente o bloco abaixo para implementar a funcionalidade)
/*
void buscarPorNome(tLista *lista) {
	if (estaVazia(lista)) {
		printf("\na lista esta vazia. nao ha o que buscar.\n");
		return;
	}
	
	char nomeBusca[100];
	printf("digite o nome (ou parte) para buscar: ");
	scanf(" %[^\n]", nomeBusca);

	// 1. criar uma flag 'int achou = 0;'
	// 2. criar um ponteiro 'tNo* atual = lista->head;'
	// 3. fazer um loop 'while (atual != NULL)'
	// 4.  dentro do loop, converter 'atual->dado.nome' para minúsculo (guardar em 'nomeContatoLower')
	// 5.  converter 'nomeBusca' para minúsculo (guardar em 'nomeBuscaLower')
	//     (para isso, usar um loop 'for' e a função 'tolower()' da <ctype.h>)
	// 6.  usar 'if (strstr(nomeContatoLower, nomeBuscaLower) != NULL)'
	// 7.   se encontrar (não for NULL), imprimir os dados do 'atual'
	//      e mudar 'achou = 1;' (não dar break, para achar múltiplos)
	// 8.  avançar 'atual = atual->prox;'
	// 9. depois do loop, checar 'if (achou == 0)', se for, imprimir "nenhum contato encontrado."
}
*/

// --- MELHORIA 5: implementação da função de alterar contato ---
// (descomente o bloco abaixo para implementar a funcionalidade)
/*
void alterarContato(tLista *lista) {
	if (estaVazia(lista)) {
		printf("\na lista esta vazia. nao ha o que alterar.\n");
		return;
	}
	
	// 1. pedir o cpf do contato a ser alterado
	// 2. buscar o nó (pode reusar a lógica da 'buscarPorCPF')
	//    (em vez de imprimir, guardar o ponteiro 'tNo* noParaAlterar')
	
	// 3. se 'noParaAlterar == NULL', imprimir "contato não encontrado" e sair
	
	// 4. se achou, imprimir os dados atuais dele
	// 5. perguntar ao usuário o que ele quer mudar:
	//    printf("o que deseja alterar?\n");
	//    printf("1 - nome\n 2 - email\n 3 - telefone\n");
	//    (ler a escolha)
	
	// 6. usar um 'switch' para a escolha:
	//    case 1: pedir o novo nome e salvar em 'noParaAlterar->dado.nome'
	//    case 2: pedir o novo email e salvar em 'noParaAlterar->dado.email'
	//    case 3: pedir o novo telefone e salvar em 'noParaAlterar->dado.telefone'
	
	// 7. imprimir "contato alterado com sucesso!"
	// (não é preciso alterar o cpf, pois isso mudaria a ordem da lista)
}
*/


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