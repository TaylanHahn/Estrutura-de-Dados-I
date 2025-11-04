#include <stdio.h>
#include <stdlib.h> // para malloc e free
#include <string.h> // para strcmp (comparar strings do CPF)
#include "lista.h"
#include <ctype.h> // para isspace e isdigit

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

	// Funcao para verificar se a lista está vazia
	int estaVazia(tLista *lista){
	    if(lista->size==0){
	        printf("A lista esta vazia!");
	        return 1;
	    } else {
	        return 0;
	    }
	}
	
	// Funcao com validacoes para CPF
	int validarCPF(const char* cpf){
	    // aqui verifica se a quantidade inserida eh de exatamente 11 digitos
	    if(strlen(cpf)!=11){
	        printf("CPF invalido! Deve conter 11 digitos.");
	        return 0;
	    } 
	    
	    // aqui verifica se o que foi inserido eh numero ou nao
	    for(int i=0;i<11;i++){
	        if(!isdigit(cpf[i])){
	            printf("CPF invalido! Deve conter apenas digitos.");
	            return 0;
	        }
	    }
	    printf("CPF valido!");
	    return 1; // retorna true se passar nas duas validacoes
	}
	
	// Funcao com validacao de String vazia
	int ehStringVazia(const char* str) {
    	// checa se o ponteiro str eh nulo
    	if (str == NULL){
    	    return 1;
    	} 
    	
    	// faz o while enquanto o caractere atual não for nulo
    	while (*str) {
    		// se encontrar qualquer caractere que não seja espaço, a string NÃO é vazia
    		if (!isspace((unsigned char)*str)) { // verifica se o caractere é um espaço em branco
    			return 0;
    		}
    		str++; // incrementa o ponteiro para que aponte para o próximo caractere
    	}
    	return 1; // a string é vazia ou só contém espaços
    }
	
// função auxiliar para ler os dados de um contato
    // do-while dentro de lerContato para as validacoes
tContato lerContato() {
	tContato c;
	char buffer[150]; // buffer temporario para leitura
	// o buffer eh uma forma segura de testar o valor, antes de efetivamente grava-lo na struct
	
	// usamos " %[^\n]" para ler strings com espaços (como o nome)
	// o espaço antes do % "consome" o Enter que sobrou do scanf anterior
    	do{
    	    printf("digite o CPF (somente numeros): ");
    	    scanf("%11s", c.cpf); 
    	    while (getchar() != '\n'); // limpa o buffer de entrada
    	    
    	} while (validarCPF(c.cpf)==0);
    	
    	do {
    		printf("digite o Nome: ");
    		scanf(" %[^\n]", buffer); // lê a string no buffer
    		if (ehStringVazia(buffer)) {
    			printf("\nErro! O nome nao pode ser vazio.\n");
    		}
    	} while (ehStringVazia(buffer));
    	strcpy(c.nome, buffer); // copia do buffer para o contato
    
    	do {
    		printf("digite o E-mail: ");
    		scanf(" %[^\n]", buffer);
    		if (ehStringVazia(buffer)) {
    			printf("\nErro! O e-mail nao pode ser vazio.\n");
    		}
    	} while (ehStringVazia(buffer));
    	strcpy(c.email, buffer);
    
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
    
        // Busca otimizada
    	tNo* atual; // declaração para antes dos testes
    	
    	// Se a posição está na segunda metade da lista, busca de trás para frente (pelo tail)
    	if (pos > lista->size / 2) {
    		atual = lista->tail; // começa pelo último
    		
    		// loop para encontrar o nó
    		for (int i = lista->size; i > pos; i--) {
    			atual = atual->ant; // vai para o anterior
    		}
    	} 
    	// Senão faz a busca normal (pelo head)
    	else {
    		atual = lista->head; // começa pelo primeiro
    		// loop para encontrar o nó 
    		for (int i = 1; i < pos; i++) {
    			atual = atual->prox;
    		}
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
		// Se a posição está na segunda metade da lista, busca pelo tail
		if (pos > lista->size / 2) {
			noParaRemover = lista->tail; 
			for (int i = lista->size; i > pos; i--) {
				noParaRemover = noParaRemover->ant; 
			}
		} 
		// Senão faz a busca normal pelo head
		else {
			noParaRemover = lista->head;
			for (int i = 1; i < pos; i++) {
				noParaRemover = noParaRemover->prox;
			}
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


    // Função auxiliar para BUSCAR UM NÓ por CPF
    // Esta função é interna (static) e será usada por consultarPorCPF e alterarContato

    // Retorna o ponteiro para o nó (tNo*) ou NULL se não achar.
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
        		if (cmp < 0) {
        			return NULL;
        		}
        		atual = atual->prox; // avança para o próximo
        	}
        	return NULL; // não achou (chegou ao fim da lista)
        }

        // função para consultar a lista pelo CPF
        void buscarPorCPF(tLista *lista) {
        	if (estaVazia(lista)) {
        		printf("\nA lista esta vazia. Nao ha o que consultar.\n");
        		return;
        	}
        	
        	char cpfBusca[12];
        	printf("\nQual CPF voce quer consultar? (11 digitos): ");
        	scanf("%11s", cpfBusca);
        	
        	// usa a função auxiliar para encontrar o nó
        	tNo* noEncontrado = buscarNoPorCPF(lista, cpfBusca);
        	
        	// se a função retornou um ponteiro (nao nulo)
        	if (noEncontrado != NULL) {
        		printf("\n--- CONSULTA CPF %s ---\n", cpfBusca);
        		printf("nome: %s\n", noEncontrado->dado.nome);
        		printf("CPF: %s\n", noEncontrado->dado.cpf);
        		printf("e-mail: %s\n", noEncontrado->dado.email);
        		printf("telefone: %s\n", noEncontrado->dado.telefone);
        		printf("---------------------------\n");
        	} else {
        		printf("\nErro! CPF '%s' nao encontrado na lista.\n", cpfBusca);
        	}
        }
        
        
        // Função para buscar pelo nome
        void buscarPorNome(tLista *lista) {
        	if (estaVazia(lista)) {
        		printf("\nA lista esta vazia. Nao ha o que buscar.\n");
        		return;
        	}
        	
        	char nomeBusca[100];
        	char nomeBuscaLower[100];
        	char nomeContatoLower[100];
        	int encontrou = 0; // para saber se achou alguem
        	
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
        		// copia o nome do contato para uma variavel temporária
        		strcpy(nomeContatoLower, atual->dado.nome);
        		// converte o nome do contato para minúsculo
        		for(int i = 0; nomeContatoLower[i]; i++){
        			nomeContatoLower[i] = tolower(nomeContatoLower[i]);
        		}
        		
        		// usa strstr() para ver se o termo de busca (minúsculo) está contido no nome do contato (minúsculo)
        		if (strstr(nomeContatoLower, nomeBuscaLower) != NULL) {
        			// exibe os dados do nó encontrado
        			printf("\nNome: %s (CPF: %s)\n", atual->dado.nome, atual->dado.cpf);
        			printf("  E-mail: %s\n", atual->dado.email);
        			printf("  Telefone: %s\n", atual->dado.telefone);
        			encontrou = 1; // marca que encontramos pelo menos 1
        		}
        		atual = atual->prox; // vai para o próximo
        	}
        	
        	// se "encontrou" continuar 0, ninguem foi achado
        	if (encontrou == 0) {
        		printf("\nNenhum contato encontrado com o termo '%s'.\n", nomeBusca);
        	}
        	
        	printf("-------------------------------------\n");
        }
        
        
        // Função para alterar contato
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
        	
        	// se a função retornar NULL, nao foi achado
        	if (noParaAlterar == NULL) {
        		printf("\nErro! CPF '%s' nao encontrado. Nao e possivel alterar.\n", cpfBusca);
        		return;
        	}
        	
        	// se achou, mostra os dados atuais e pede os novos
        	printf("\nContato encontrado: '%s' (CPF: %s)\n", noParaAlterar->dado.nome, noParaAlterar->dado.cpf);
        	printf("AVISO: O CPF nao pode ser alterado (e a chave da lista).\n");
        	
        	char buffer[150]; // buffer temporário para leitura
        	
        	
        // Os novos dados são solicitados respectivamente, todos com validação de entrada vazia (como feito inicialmente)
        	// NOVO NOME
        	do {
        		printf("Digite o NOVO Nome (atual: %s): ", noParaAlterar->dado.nome);
        		scanf(" %[^\n]", buffer);
        		if (ehStringVazia(buffer)) {
        			printf("\nErro! O nome nao pode ser vazio.\n");
        		}
        	} while (ehStringVazia(buffer));
        	strcpy(noParaAlterar->dado.nome, buffer); // atualiza o nome no nó
        
        	// NOVO E-MAIL
        	do {
        		printf("Digite o NOVO E-mail (atual: %s): ", noParaAlterar->dado.email);
        		scanf(" %[^\n]", buffer);
        		if (ehStringVazia(buffer)) {
        			printf("\nErro! O e-mail nao pode ser vazio.\n");
        		}
        	} while (ehStringVazia(buffer));
        	strcpy(noParaAlterar->dado.email, buffer); // atualiza o e-mail no nó
        
        	// NOVO TELEFONE
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