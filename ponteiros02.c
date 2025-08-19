/* Atividade Ponteiros - Questão 2 */

#include<stdio.h>

// assinatura das funções
    float calculaMedia(int *pw, int *px, int *py, int *pz);
    int maiorValor(int *pw, int *px, int *py, int *pz);
    int *maiorValorEnd(int *pw, int *px, int *py, int *pz);

// a - Crie um programa que leia 4 variáveis int, informe o endereço e o conteúdo de cada uma delas
    int main (){
        
      int w, x, y, z, *pw, *px, *py, *pz;
      pw = &w; px = &x; py = &y; pz = &z;
      
      printf("Digite quatro numeros inteiros: ");
      scanf("%d %d %d %d", &w, &x, &y, &z);
      
      printf("\nO conteúdo de W é: %d", *pw);
      printf("\nO endereço de W é: %p", (void*)pw); // %p para ponteiros e convertido para void*, o tipo genérico esperado por %p 
      
      printf("\nO conteúdo de X é: %d", *px);
      printf("\nO endereço de X é: %p", (void*)px);
      
      printf("\nO conteúdo de P é: %d", *py);
      printf("\nO endereço de P é: %p", (void*)py);
      
      printf("\nO conteúdo de Z é: %d", *pz);
      printf("\nO endereço de Z é: %p", (void*)pz);
      
      // usando a função para calcular a média
        float media = calculaMedia(pw, px, py, pz);
        printf("\n\nA média dos valores é: %.2f\n", media);
        
        //usando a função para retornar o maior valor
        int maior = maiorValor(pw, px, py, pz);
        printf("\n\nO maior valores é: %d\n", maior);
        
        // usando a função para retornar endereço do maior valor
        int *endereco = maiorValorEnd(pw, px, py, pz);
        printf("\n O endereço do maior valor é %p", (void*)endereco);
      
    }//main


// b- Crie uma função que recebe quatro ponteiros para inteiros como parâmetros e devolva a media aritmética dos conteúdos apontados (float); (fazer a média dos números, não dos endereços)

    float calculaMedia(int *pw, int *px, int *py, int *pz) {
        int soma = *pw + *px + *py + *pz;
        float media = soma / 4.0; // divide por float
        return media;
    }


//c - Crie uma função que receba como parâmetro 4 ponteiros variáveis inteiras e devolva o maior valor (maior conteúdo, não o maior endereço);

    int maiorValor(int *pw, int *px, int *py, int *pz){
        int maior = *pw;
        if(*px > maior) maior = *px;
        if(*py > maior) maior = *py;
        if(*pz > maior) maior = *pz;
        return maior;
    }

//d - Crie uma função que receba como parâmetro 3 ponteiros para inteiro e devolva o endereço que aponta para a variável de maior valor; (importante: quero o endereço do maior valor, não o maior endereço...)

    int *maiorValorEnd(int *pw, int *px, int *py, int *pz){
        int *maior = pw;
        if(*px > *maior) maior = px;
        if(*py > *maior) maior = py;
        if(*pz > *maior) maior = pz;
        return maior;
    }

