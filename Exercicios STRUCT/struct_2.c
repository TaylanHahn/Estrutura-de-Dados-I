/*
EXERCICIO 02
Uma pré escola tem 5 alunos, crie uma estrutura que armazena nome, telefone de emergencia, idade, contato de emergência;

- Crie um vetor com 5 dessas estruturas
- Crie uma função para ler as informações de UM aluno; chame a função 5 vezes.
- Crie uma função que recebe como parâmetro o índice do aluno e escreva todos os dados na tela de maneira organizada.
 As funções acima recebem o índice do aluno como parâmetro e alteram o array global que contém os alunos.
*/

// struct ALuno
typedef struct {
    char nome[50];
    int idade;
    char telefone_e[15];
    char contato_e[15];
   
} Aluno;

// Vetor com 5 
Aluno pre_escola[5];

// Assinaturas das funções;
void lerAluno(int i);
void exibirAluno(int i);

// Função PRINCIPAL
int main(){
    int i;
    char opcao = '.';
    
    // laço para ler os 5 alunos
    for(i=0;i<5;i++){
        lerAluno(i);
    }
    
    printf("Gostaria de ver os dados registrados no sistema? (S/N)");
    scanf(" %c", &opcao);
    
    if(opcao == 'S' || opcao == 's'){
         printf("\n");
         // laço para exibir as infos
        for(i=0;i<5;i++){
            exibirAluno(i);
        }
    } else if (opcao == 'N' || opcao == 'n'){
        printf("encerrando o programas...");
        return 0;
    } else {
        return 0;
    }
 
   
    
}//chave main





// Função para ler UM aluno 
void lerAluno(int i){
    if(i < 0 || i >= 5){
        printf("Indice de aluno invalido.\n");
        return;
    }
    
    printf("CADASTRO DO ALUNO %d\n", i + 1);
    printf("---------------------------\n");
    
    printf("Nome: ");
    scanf(" %[^\n]", pre_escola[i].nome);
    
    printf("Idade: ");
    scanf("%d", &pre_escola[i].idade);
    
    printf("Telefone de Emergencia: ");
    scanf(" %[^\n]", pre_escola[i].telefone_e);
    
    printf("Contato de Emergencia: ");
    scanf(" %[^\n]", pre_escola[i].contato_e);
    
    printf("\n");
}// chave lerAluno

// Função para exibir o ALUNO
void exibirAluno(int i){
    if(i < 0 || i >= 5){
        printf("Indice de aluno invalido.\n");
        return;
    }
    
    printf("---------------------------\n");
    printf("DADOS DO ALUNO %d\n\n", i + 1);
    
    printf("Nome: %s\n", pre_escola[i].nome);
    printf("Idade: %d\n", pre_escola[i].idade);
    printf("Telefone de Emergencia: %s\n", pre_escola[i].telefone_e);
    printf("Contato de Emergencia: %s\n", pre_escola[i].contato_e);
    printf("---------------------------\n");
    printf("\n");
}// chave exibirAluno







