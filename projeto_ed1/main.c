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

Dupla: José e Taylan

*******************************************************************************/

#include <stdio.h>

#define MAX 12 // não vai ; no final 

// funcao para imprir o vetor toda vez que é manipulando
void imprimirVetor(int vet[], int numPreenchidos ) { 
    
    // adicionei uma validação, para caso esteja vazio
    if(numPreenchidos == 0){
        printf("O vetor esta vazio.");
        return;
    }    
    
    // ESTAVA ASSIM:
        //  for (int i = 0; i < numPreenchidos; i++) {
        //     printf("Impressão atual do tamanho do vetor com as posições: ");
        //     printf("vet[%d]=%d, ", i, vet[i]);
        //   }
        //   printf("\n");
        // }
    
    // FICOU ASSIM:
        printf("\nEstado atual do vetor: [ ");
            for (int i = 0; i < numPreenchidos; i++) {
                printf("%d ", vet[i]);
            }
        printf("]\n");
    }

int main()
{

// COMO ESTAVA:
    // int vet[12];
    // int numPreenchidos=0;
    // int escolha, consulta, posicaoInsercao, valorInsercao;
    // int posicaoReal = posicaoInsercao - 1; <<--- variável que exibe a posição ajustada ao usuário
    
// COMO FICOU:
    int vet[MAX]; // o 12 foi substituido pelo MAX
    int numPreenchidos = 0; 
    int escolha; // mantive a escolha por ser uma variável global, as demais são variáveis locais e por isso movi para dentro dos cases
    
    printf("\n***LISTAS COM VETOR EM C***\n");

    do {
    printf("\n-------------- MENU -----------------\n");
    printf("\nEscolha uma opção: \n");
    printf("1 - Exibir elemento\n"); // Consulta realizada pela posição
    printf("2 - Inserir elemento\n"); // Insere um elemento, ao informar a posição
    printf("3 - Remover elemento\n"); // Remove os dados de uma posição
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
            // 1. CONSULTAR ELEMENTO
                // O else if (numPreenchidos==MAX) foi removido, pois percebi que neste primeiro caso, não faz sentido informar estar cheio, já que só desejamos consultar o item da lista e não inserir. 
            case 1:
                int consulta; // Variável local
                printf("\nMENU > Consultar");
                
                // Testa de a lista está vazia ou há dados para consultar
                if (numPreenchidos==0) {
                    printf("\nNão há dados para consultar.\n");
                } else {
                    printf("\nQual posição você quer consultar? (1 a %d): ", numPreenchidos); //ajusta o numero limite conforme o que já esta preenchido, facilitando para o usuario saber qual numero maximo ele pode consultar naquele momento
                    scanf("%d", &consulta);
                    
                    // condicional para exiir a posição pedida
                    if(consulta>numPreenchidos || consulta < 1) {
                     printf("\nPosição inválida! Informe uma posição preenchida.");
                    } else {
                        printf("\nA posição %d está ocupada com o inteiro de valor %d", consulta, vet[consulta-1]);
                    }
                } break;
            
            // 2. INSERIR ELEMENTO
            case 2:
                int posicaoInsercao, valorInsercao; // variaveis locais
                 printf("\nMENU > Inserir");
                
                if (numPreenchidos == MAX) {
                    printf("Vetor lotado! Exclua pelo menos 1 para poder inserir valores.\n");
                } else {
                    printf("\nInforme a posição: (1 a %d): ", numPreenchidos + 1);
                    scanf("%d", &posicaoInsercao);
                    
                    // teste condicional para validar a posição escolhida
                     if (posicaoInsercao < 1 || posicaoInsercao > numPreenchidos + 1 || posicaoInsercao > MAX) {
                        printf("\nPosição de inserção inválida!\n");
                    } else {
                        printf("\nInforme o valor inteiro a ser inserido: ");
                        scanf("%d", &valorInsercao);
                
                    // LÓGICA CORRIGIDA: agora move os elementos para a direita, abrindo espaço
                        int indice = posicaoInsercao - 1; // ajusta o indice para o vetor
                        for (int i = numPreenchidos; i > indice; i--) {
                            vet[i] = vet[i - 1]; // aqui copiamos o valor da posição anterior para a atual, "empurrando" o valor
                        } // nota: uso de IA para entender a lógica correta

                        // insere o novo valor na posiçaoo solicitada
                        vet[indice] = valorInsercao;
                        numPreenchidos++; // incrementa o numero de elmentos
                        printf("\nFeito! Valor %d inserido na posição %d.\n", valorInsercao, posicaoInsercao);
                    } 
                } break;
                    
            // 3. REMOVER ELEMENTO
            case 3: 
                int posicaoRemocao; // variavel local
                printf("\nMENU > Remover");
                // testa 
                if (numPreenchidos == 0) {
                    printf("\nA lista está vazia.\n");
                } else {
                    printf("\nInforme a posição do elemento a ser removido (1 a %d): ", numPreenchidos);
                    scanf("%d", &posicaoRemocao);

                    // validação da posição da remoção 
                    if (posicaoRemocao < 1 || posicaoRemocao > numPreenchidos) {
                        printf("\nPosição de remoção inválida!\n");
                    } else {
                        // declarei as variaveis que serao usadas somente nesse ponto
                        int indice = posicaoRemocao - 1; // posicaoRemocao aqui já recebeu um valor do scanf, senão pegaria lixo
                        int valorRemovido = vet[indice];

                        // move os elementos da direita para a esquerda
                        for (int i = indice; i < numPreenchidos - 1; i++) {
                            vet[i] = vet[i + 1];
                        }
                        
                        numPreenchidos--; // decrementar o número de elementos
                        printf("\nFeito! Valor %d removido da posição %d.\n", valorRemovido, posicaoRemocao);
                    }
                } break;
            
            // 4. TOTAL DE ELEMENTOS
            case 4:
                printf("\nMENU > Total");
                printf("\nA lista possui: %d elemento(s). Capacidade total de posições: %d\n", numPreenchidos, MAX);
                break;
                
            default: 
                printf ("\n Opção inválida! Tente novamente.");
        }
    // Chamada para a função imprimir todo o vetor ao final das operações
    imprimirVetor(vet, numPreenchidos);
    
    } while (escolha != 0); //  o loop continua enquanto escolha não for 0 (é a opção SAIR)
    
    return 0;

}

