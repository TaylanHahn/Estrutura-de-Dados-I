# Estrutura de Dados I

Bem-vindo ao repositório de estudos da disciplina de Estrutura de Dados I. Este espaço contém códigos e anotações sobre os conceitos fundamentais da linguagem C aplicados à construção de estruturas de dados, incluindo Ponteiros, Structs e Alocação Dinâmica de Memória.

---

## 1. Ponteiros 
> São variáveis que, em vez de armazenar um valor, armazenam um **endereço de memória** de outra variável. Dominar ponteiros é essencial para criar estruturas de dados eficientes e para manipular a memória de forma avançada.

- **Acesso direto à memória:** permite ler e alterar valores diretamente na memória.
- **Passagem por referência:** permite que funções modifiquem variáveis fora delas, usando endereços.
- *Manipulação de `Arrays` e `Strings`.*
- **Alocação dinâmica de memória**, essencialmente para usar `malloc`, `calloc`, free e etc.
- *Construção de estruturas mais complexas*, com listas ligadas, árvores, pilhas, filas e etc.

### 1.1 - Operadores Fundamentais

-   `&` (Operador "Endereço de"): Retorna o endereço de memória de uma variável.
-   `*` (Operador "Diferenciação" ou "Conteúdo de"): Acessa o valor armazenado no endereço de memória para o qual o ponteiro aponta.

### Exemplo Prático

```c
#include <stdio.h>

int main() {
    int valor = 42;
    int *ponteiro; // Declaração de um ponteiro para um inteiro

    ponteiro = &valor; // O ponteiro agora guarda o endereço da variável 'valor'

    printf("Valor da variável 'valor': %d\n", valor);
    printf("Endereço onde 'valor' está armazenado: %p\n", &valor);
    printf("Endereço que o 'ponteiro' guarda: %p\n", ponteiro);
    printf("Valor acessado através do 'ponteiro': %d\n", *ponteiro);

    // Modificando o valor original através do ponteiro
    *ponteiro = 100;
    printf("Novo valor da variável 'valor': %d\n", valor);

    return 0;
}
````

## 1.2 - Regras básicas para usar o `printf`
- Quero o valor (conteúdo) de uma variável "normal", **não usa nada.**
  ````c
  int x = 10;
  printf("%d", x); // imprime 10
  ````

- Quero o endereço de memória de uma variável, **uso `&` para obter o endereço.**
  ````c
  int x = 10;
  printf("%p", &x); // imprime algo como 0x77fffff...
  ````
    - `%p` para imprimir endereços, P de *pointer*.

 - Quero o valor apontado por um ponteiro, **uso `*` para acessá-lo.** Isso se chama *desreferenciação*.
   ````c
   int x = 10;
   int *ptr = &x;
   printf("%d", *ptr); // imprime 10
   ````
   - NUNCA use `*ptr` se o ponteiro não foi inicializado corretamente.
  
- Usar `%p` para endereços de memória.
- `(void*)px` converte o pointer para um tipo genérico que o `%p` espera.
- Usar o `%u` funciona, mas não é o ideal.

### Resumindo
    _________VOCÊ QUER_________|________Código________|_______Explicação__________     
    
      valor de uma variável               x                   só o valor        
    ______________________________________________________________________________
      endereço da variável               &x               usa o & para obter
    ______________________________________________________________________________
    valor apontado por um              *ptr            usa o * para desreferenciar
            ponteiro
    ________________________________________________________________________________
    endereço de um ponteiro           &ptr             o ponteiro tbm é uma variável

