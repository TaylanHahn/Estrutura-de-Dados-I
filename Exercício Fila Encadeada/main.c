/*

Fila Duplamente Encadeada

1.CRIAR FILA DE NÚMEROS INTEIROS
2. INSERIR 7 NÚMEROS, 
3. REMOVER 2 NÚMEROS, 
4. SOMAR E INSERIR O RESULTADO  NA FILA, 
REPITA 3 E 4 ATÉ QUE RESTE APENAS 1 ELEMENTO NA FILA.

*/
#include <stdio.h>
#include "fila.h"

int main()
{
    int i;
    int r, a, b; 
    tFila fila; 
    inicializar(&fila);

    imprimeFila(&fila);    
    for(i=0;i<7;i++){
        inserir(&fila, i);
        printf("inserindo %d. ",i);
        imprimeFila(&fila);
    }

    while(tamanho(&fila)>1){
        remover(&fila,&a);
        remover(&fila,&b);
        r = a+b;
        inserir(&fila, r);
        imprimeFila(&fila); 
    }
    return 0;
}
