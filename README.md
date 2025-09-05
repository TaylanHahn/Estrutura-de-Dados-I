# Estrutura de Dados I

Códigos e anotações sobre os conceitos fundamentais da linguagem C aplicados à construção de estruturas de dados, incluindo Ponteiros, Structs e Alocação Dinâmica de Memória.

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


# 2. Structs (Estruturas)
> É um tipo de dado definido pelo usuário que permite **agrupar variáveis de diferentes tipos** sob um único nome. Funciona como um "molde" para criar variáveis que representam entidades complexas do mundo real, como um aluno, um livro ou um produto. 

- **Organização de dados:** agrupa informações relacionadas, tornando o código mais limpo e lógico.
- **Criação de novos tipos:** permite definir tipos de dados personalizados e complexos.
- *Facilita a passagem de dados* para funções, agrupando múltiplos valores em um único argumento.
- **Base para estruturas de dados avançadas**, como listas ligadas, árvores e grafos.
- *Melhora a legibilidade e a manutenção* do código ao modelar conceitos de forma clara.

### 2.1 - Operadores Fundamentais

-   `.` (Operador de Acesso a Membro): Usado para acessar um membro (uma variável interna) de uma `struct`.
-   `->` (Operador de Seta): Usado para acessar um membro de uma `struct` através de um **ponteiro** para essa estrutura. É um atalho para `(*ponteiro).membro`.

### 2.2 - Simplificando com `typedef`
A palavra-chave `typedef` cria um "apelido" para um tipo de dado. Ao usá-la você elimina a necessidade de escrever a palavra struct toda vez que for declarar uma nova variável, tornando o código mais enxuto.

### Exemplo Prático: Declaração e Uso Básico

```c
#include <stdio.h>
#include <string.h> // Necessário para strcpy

// 1. Definição do molde "Produto"
typedef struct {
    char nome[50];
    int id;
    float preco;
} produto;

int main() {
    // 2. Criação de uma variável do tipo 'struct Produto'
    struct Produto caneta;

    // 3. Acessando os membros com o operador '.' para atribuir valores
    strcpy(caneta.nome, "Caneta Azul BIC");
    caneta.id = 101;
    caneta.preco = 1.99;

    // 4. Lendo e imprimindo os valores dos membros
    printf("--- Detalhes do Produto ---\n");
    printf("Nome: %s\n", caneta.nome);
    printf("ID: %d\n", caneta.id);
    printf("Preco: R$ %.2f\n", caneta.preco);

    return 0;
}
````

### 2.3 - Structs e Ponteiros
Assim como em variáveis comuns, podemos ter ponteiros que armazenam o endereço de memória de uma struct. Isso é crucial para a alocação dinâmica e para modificar uma struct dentro de uma função de forma eficiente.

````c
#include <stdio.h>

typedef struct {
    char titulo[100];
    int ano;
} Livro;

int main() {
    Livro livro1 = {"O Senhor dos Aneis", 1954};
    Livro *ptrLivro; // Declaração de um ponteiro para uma struct do tipo Livro

    ptrLivro = &livro1; // O ponteiro agora aponta para 'livro1'

    // Para acessar os membros através de um ponteiro, usamos o operador '->'
    printf("--- Acesso via Ponteiro ---\n");
    printf("Titulo: %s\n", ptrLivro->titulo);
    printf("Ano: %d\n", ptrLivro->ano);

    // Modificando o valor original através do ponteiro
    ptrLivro->ano = 1955; // Alterando o ano de publicação
    printf("\nAno alterado: %d\n", livro1.ano); // O valor original foi modificado

    return 0;
}
````

### 2.4 - Structs como Parâmetros de Funções
Passar structs para funções é uma prática comum. A passagem por referência (usando ponteiros) é geralmente preferível à passagem por valor, pois evita a cópia de grandes quantidades de dados, economizando memória e tempo de processamento.

````c
#include <stdio.h>

typedef struct {
    char nome[50];
    float salario;
} Funcionario;

// A função recebe um PONTEiro para a struct.
// Isso evita criar uma cópia e permite modificar o original.
void aumentarSalario(Funcionario *func, float percentual) {
    // Usamos '->' pois 'func' é um ponteiro
    func->salario = func->salario * (1 + percentual / 100.0);
}

int main() {
    Funcionario joao = {"Joao da Silva", 3000.00};

    printf("Salario antigo de %s: R$ %.2f\n", joao.nome, joao.salario);

    // Passamos o ENDEREÇO da struct para a função
    aumentarSalario(&joao, 10.0); // Aumento de 10%

    printf("Salario novo de %s: R$ %.2f\n", joao.nome, joao.salario);

    return 0;
}
````

### 2.5 - Arrays de Structs
É possível criar arrays onde cada elemento é uma struct. Isso é perfeito para armazenar uma coleção de registros, como uma lista de contatos, um inventário de produtos ou os dados de uma turma de alunos.

````c
#include <stdio.h>
#include <string.h>

typedef struct {
    char nome[50];
    float nota;
} Aluno;

int main() {
    // Criando um array que pode armazenar 3 alunos
    Aluno turma[3];

    // Preenchendo os dados
    strcpy(turma[0].nome, "Ana");
    turma[0].nota = 9.5;

    strcpy(turma[1].nome, "Bruno");
    turma[1].nota = 7.0;
    
    strcpy(turma[2].nome, "Carla");
    turma[2].nota = 8.2;

    printf("--- Lista de Alunos da Turma ---\n");
    for (int i = 0; i < 3; i++) {
        // Acessamos cada struct pelo índice do array
        printf("Aluno: %s, Nota: %.1f\n", turma[i].nome, turma[i].nota);
    }

    return 0;
}
````


## 3. Alocação Dinâmica

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





