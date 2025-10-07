/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
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