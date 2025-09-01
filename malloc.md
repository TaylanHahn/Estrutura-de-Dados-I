# Alocação Dinâmica

> A alocação dinâmica de memória é um recurso poderoso na linguagem C que permite reservar espaço na memória em tempo de execução. Diferente da alocação estática (ex: `int v[10];`), onde o tamanho é fixo e definido em tempo de compilação, a alocação dinâmica nos dá flexibilidade para gerenciar a memória conforme a necessidade do programa.

### O que é a Heap?

Em C, a memória é geralmente dividida em segmentos, sendo os mais comuns a **Stack** (pilha) e a **Heap**.

-   **Stack**: Usada para variáveis locais e chamadas de função. É gerenciada automaticamente pelo compilador. O espaço é limitado e a alocação e liberação são muito rápidas.
-   **Heap**: Uma área de memória maior e mais flexível, usada para alocação dinâmica. É aqui que funções como `malloc` atuam. **O programador é responsável por gerenciar o ciclo de vida da memória alocada na Heap.**

# A Função `malloc`

A função `malloc` (memory allocation) é a principal ferramenta para alocação dinâmica. Ela está declarada na biblioteca `<stdlib.h>`.

 **O que faz?**
-  Reserva um bloco de memória do tamanho especificado (em bytes).

  **O que retorna?**
-   Um ponteiro do tipo `void*` (ponteiro genérico) para o primeiro byte do bloco de memória alocado.
-   Se a alocação falhar (por exemplo, por falta de memória), ela retorna `NULL = 0`.

### Sintaxe

````c
void* malloc(size_t tamanho_em_bytes);
````

- Para usar o ponteiro normalmente, é necessário indicar o tipo da variável.
- Quando não precisar mais da memória, libere-a com a função `free()`.

### A importância do `free`
> Para cada chamada a `malloc`, deve haver uma chamada correspondente a free.
A função free "devolve" o bloco de memória previamente alocado para o sistema operacional, marcando-o como disponível para uso futuro.

**O que acontece se não usarmos free?**

O programa continuará "segurando" aquela memória até sua finalização. Se isso ocorrer repetidamente (ex: dentro de um loop), pode causar um vazamento de memória (memory leak), consumindo toda a memória disponível e podendo travar o sistema.

````c
void free(void *ponteiro_para_memoria_alocada);
````

# Boas Práticas e Erros Comuns

- **Verifique o retorno de malloc:** Sempre confira se o ponteiro retornado é `NULL`. Tentar acessar um ponteiro NULL resulta em Undefined Behavior, geralmente causando o crash do programa.

- **Use `sizeof`:** Não use valores fixos como malloc(n * 4). Use `malloc(n * sizeof(int))` para garantir que seu código funcione em diferentes arquiteturas.

- **Evite Memory Leaks:** Garanta que toda memória alocada com `malloc` seja liberada com `free` quando não for mais necessária.

- **Evite Dangling Pointers:** Após usar free(ptr), o ponteiro ptr ainda aponta para a antiga localização de memória, que agora é inválida. Tentar acessá-la é um erro. Uma boa prática é atribuir NULL ao ponteiro após liberá-lo:

````c
free(ptr);
ptr = NULL;
````

- **Não libere a mesma memória duas vezes:** Chamar free duas vezes para o mesmo ponteiro (double free) pode corromper a Heap e causar falhas imprevisíveis no programa.


### EXEMPLO
> Exemplo básico de alocação de um inteiro.
Para alocar espaço para um único inteiro, usamos o operador `sizeof` para garantir a portabilidade do código, já que o tamanho de um int pode variar entre sistemas.

````c
#include <stdio.h>
#include <stdlib.h> // Essencial para malloc e free

int main() {
    // Declara um ponteiro que apontará para a memória alocada
    int *ptr;

    // Aloca memória para um único inteiro
    ptr = (int *) malloc(sizeof(int));

    // SEMPRE verifique se a alocação foi bem-sucedida
    if (ptr == NULL) {
        printf("Erro: Falha na alocação de memória!\n");
        return 1; // Retorna um código de erro
    }

    // A memória foi alocada com sucesso. Agora podemos usá-la.
    *ptr = 42;
    printf("O valor armazenado é: %d\n", *ptr);
    printf("Endereço de memória alocado: %p\n", ptr);

    // Libera a memória alocada para evitar vazamentos (memory leak)
    free(ptr);

    return 0;
}
````


