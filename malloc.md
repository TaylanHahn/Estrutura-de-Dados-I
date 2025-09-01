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
-   Se a alocação falhar (por exemplo, por falta de memória), ela retorna `0 ou NULL`.

### Sintaxe

````c
void* malloc(size_t tamanho_em_bytes);
````

- Para usar o ponteiro normalmente, é necessário indicar o tipo da variável.
- Quando não precisar mais da memória, libere-a com a função `free()`.

### A Importância do free
> Para cada chamada a `malloc`, deve haver uma chamada correspondente a free.
A função free "devolve" o bloco de memória previamente alocado para o sistema operacional, marcando-o como disponível para uso futuro.

**O que acontece se não usarmos free?**
O programa continuará "segurando" aquela memória até sua finalização. Se isso ocorrer repetidamente (ex: dentro de um loop), pode causar um vazamento de memória (memory leak), consumindo toda a memória disponível e podendo travar o sistema.

````c
void free(void *ponteiro_para_memoria_alocada);
````
