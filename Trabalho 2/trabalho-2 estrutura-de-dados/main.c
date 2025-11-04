/******************************************************************************

TRABALHO 2 - ESTRUTURAS DE DADOS I

GRUPO: José Tricot Athaualpa Kolesny Tricot
       Taylan Hahn Fernandes 

Projeto: Sistema de Gerenciamento de Listas de contatos usando uma Lista Duplamente Encadeada com Header

O sistema deve permitir inserir, remover, consultar e listar contatos,
mantendo sempre a ordem alfabética crescente pelo CPF (armazenado como string). Não haverá CPFs repetidos

🧩 Situação-problema
Implementar um programa em C para armazenar uma lista de contatos, contendo:

Nome
E-mail
Telefone
CPF
Os dados devem ser inseridos na lista na posição correta segundo a ordem alfabética crescente do CPF.

⚙️ Funcionalidades mínimas
Inserir um novo contato na posição correta (ordem crescente de CPF).
Remover contatos de qualquer posição (início, meio ou fim).
Consultar contato por posição.
Listar todos os contatos, exibindo também os endereços do item atual, do próximo e do anterior.

*******************************************************************************/

#include <stdio.h>
#include "lista.h" // inclui nossas definições e funções

int main() {
	
	tLista lista;	 // cria a variável da lista (o "header")
	inicializar(&lista); // inicializa a lista como vazia
	int escolha;		// variável para o menu
	
	// variáveis locais que serão usadas dentro do switch
	tContato contatoNovo; 
	int posicao;

	printf("\n***LISTAS DUPLAMENTE ENCADEADA EM C***\n");

	do {
	printf("\n-------------- MENU -----------------\n");
	printf("\nescolha uma opcao: \n");
	printf("1 - Inserir um novo contato (em ordem de CPF)\n"); 
	printf("2 - Remover contato por posicao\n"); 
	printf("3 - Consultar contato por posicao\n"); 
	printf("4 - Listar todos os contatos\n"); 
	printf("0 - Sair\n");
	printf("-------------------------------------");
	printf("\nOpcao: ");
	
	scanf("%d", &escolha);
	
		if (escolha==0){
			printf("\nsaindo... ate logo!\n");	 
			break;
		}
	
		switch (escolha) {
			
			// inserir contato
			case 1:
				printf("\nMENU > 1. Inserir contato\n");
				// chama a função auxiliar para ler os dados
				contatoNovo = lerContato(); 
				// tenta inserir o contato lido de forma ordenada
				if (inserirOrdenado(&lista, contatoNovo)) {
					printf("\nFeito! contato '%s' inserido com sucesso.\n", contatoNovo.nome);
				}
				break;
			
			// remover contato
			case 2:
				printf("\nMENU > 2. Remover contato\n");
				if(estaVazia(&lista)) {
					printf("\nA lista esta vazia. Nao e possivel remover.\n");
				} else {
					printf("\nQual posicao voce quer remover? (1 a %d): ", lista.size);
					scanf("%d", &posicao);
					removerPorPosicao(&lista, posicao); // a função de remover já exibe a msg de sucesso/erro
				}
				break;
					
			// consultar contato
			case 3: 
				printf("\nMENU > 3. Consultar contato\n");
				if(estaVazia(&lista)) {
					printf("\nA lista esta vazia. Nao ha o que consultar.\n");
				} else {
					printf("\nQual posicao voce quer consultar? (1 a %d): ", lista.size);
					scanf("%d", &posicao);
					consultarPorPosicao(&lista, posicao); // a função de consultar já exibe os dados ou msg de erro
				}
				break;
			
			// listar todos
			case 4:
				printf("\nMENU > 4. Listar todos\n");
				// a lista completa será impressa logo após o switch
				break;
				
			default: 
				printf ("\n Opcao invalida! Tente novamente.\n");
	}
		
		// chamada para a função listarTudo ao final de CADA operação, como no trabalho 1
		// se a opção for 3 (consultar), não lista tudo, pois já mostrou a consulta
		// se a opção for 0 (sair) ou inválida, também não lista
		if (escolha != 3 && escolha != 0 && escolha <= 4) {
			 listarTodos(&lista);
		}
		
	} while (escolha != 0); // o loop continua enquanto 'escolha' não for 0
	
	// libera a memória de todos os nós antes de sair
	liberarLista(&lista);

	printf("\n");
	printf("\nProgramadores: ");
	printf("\nJose Athaualpa Kolesny Tricot");
	printf("\nTaylan Hahn Fernandes");
	printf("\n\n");
	
	return 0;
}