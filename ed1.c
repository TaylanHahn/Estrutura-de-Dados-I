/******************************************************************************

TRABALHO 1 - ESTRUTURAS DE DADOS I

Projeto: Sistema de Gerenciamento de Listas com Vetor em C
🎯 Descrição do Problema
Sua equipe, composta por até 3 integrantes, deverá desenvolver um sistema em linguagem C para gerenciar Listas numéricas armazenados em um vetor de inteiros de tamanho 12. O sistema deverá permitir as seguintes operações:

Consulta de código por posição;
Inserção em posição informada (com reorganização dos elementos, se necessário);
Remoção de um código (com ajuste das posições subsequentes);
Exibição da quantidade de elementos ocupados;
Apresentação de menu interativo para escolha de operações.;

1. Checkpoint de Desenvolvimento (1,5 pontos)
Cada equipe deverá apresentar o andamento do trabalho ao professor até 08 de setembro. Será avaliado:

Estrutura inicial do código;
Planejamento das funcionalidades;
Organização da equipe;
Compreensão dos elementos implementados até o momento.

*******************************************************************************/
#include <stdio.h>
#define MAX 12; // trocar os máximos (12)

void imprimirVetor(int vet[12], int numPreenchidos ) { //funcao para imprir o vetor toda vez que é manipulando
  for (int i = 0; i < numPreenchidos; i++) {
    printf("Impressão atual do tamanho do vetor com as posições: ");
    printf("vet[%d]=%d, ", i, vet[i]);
  }
  printf("\n");
}

int main()
{
    int vet[12];
    int numPreenchidos=0;
    int escolha, consulta, posicaoInsercao, valorInsercao;
    int posicaoReal = posicaoInsercao - 1; // variável que exibe a posição ajustada ao usuário
    
    printf("\n***LISTAS COM VETOR EM C***\n");

    do {
    printf("-------------- MENU -----------------");
    printf("\nEscolha uma opção: \n");
    printf("1 - Exibir elemento\n"); // Consulta realizada pela posição
    printf("2 - Inserir elemento\n"); // Insere um elemento, ao informar a posição
    printf("3 - Remover elemento\n"); // Remove od dados de uma posição
    printf("4 - Total de elementos\n"); // Exibi a quantidade de elementos ocupados
    printf("0 - Sair\n");
    printf("-------------------------------------");
    printf("\n");
    
    scanf("%d", &escolha);
    
        if (escolha==0){
            printf("\nAté logo!");    
            break;
        }
    
        switch (escolha) {
            case 1:
                if (numPreenchidos==0) {
                    printf("\nNenhum inteiro informado na lista até o momento.\n");
                }
                else if (numPreenchidos==MAX) {
                    printf("\nTodas as posição estão ocupadas!");
                }
                else {
                    printf("\nQual posição gostaria de consultar? \n");
                    scanf("%d", &consulta);
                        if (consulta>numPreenchidos) {
                            printf("\nPosição ainda não preenchida!");
                            
                        
                        //colocar mais uma condição se estiver fora do intervalor de MAX informando fora do intervalo     
                        
                            
                        }
                        else {
                            printf("\nA posição %d está ocupada com o inteiro de valor %d", consulta, vet[consulta-1]);
                        }
                    }
            break;
            
            case 2:
                if (numPreenchidos == MAX) {
                    printf("Vetor lotado! Exclua pelo menos 1 para poder inserir valores.");
                }
            printf("Informe a posição: (1 até %d): ", MAX);
            scanf("%d", &posicaoInsercao);
            printf("Informe um valor inteiro positivo: ");
            scanf("%d", &valorInsercao);
                
                // se posicaoReal menor que preenchidos, adicionar vet[preenchidos+1]
                if (posicaoReal < numPreenchidos) {
                    vet[numPreenchidos] = valorInsercao;
                    numPreenchidos++;  // Atualiza o contador
                }
                
                // se posicaoReal > preenchidos, valorInsercao=vet[preenchidos]
                else {
                
                    // Move todos os elementos a partir da posição de inserção para a direita
                    for (int i = numPreenchidos; i > posicaoReal; i--) {
                    vet[i] = vet[i-1];  // Cada elemento recebe o valor do anterior
                    }

                // Agora insere o novo valor na posição liberada
                vet[posicaoReal] = valorInsercao;
                numPreenchidos++;  // Atualiza o contador de elementos
                }
            // Só trata dois casos, falta:
            // - Validar se posicaoInsercao está entre 1-12
            // - Tratar caso onde posicaoReal > numPreenchidos
            // - Lógica completa de deslocamento        
            break;
        
            case 3: 
            //...
            printf("...");
            break;
            
            case 4:
            //...
            printf("...");
            break;
            
            default:
            //...
            printf ("\n Opção inválida!");
            
        }
    // Função para imprimir todo o vetor ao final das operações
    imprimirVetor(vet, numPreenchidos);
    
    } while ((escolha > 0) && (escolha < 5));
    
    return 0;
}
