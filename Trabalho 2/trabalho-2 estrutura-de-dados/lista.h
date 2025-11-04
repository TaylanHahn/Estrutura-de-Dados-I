
// o que vamos armazenar
typedef struct {
	char nome[100];	 // nome do contato
	char email[150]; // e-mail do contato
	char telefone[20]; // telefone do contato
	char cpf[12];	 // cpf *chave de ordenação*
} tContato;

// nó
typedef struct tipoNo {
	tContato dado;		// o contato que estamos guardando
	struct tipoNo* prox;	// ponteiro para o próximo nó
	struct tipoNo* ant;	// ponteiro para o nó anterior
} tNo;

// "header" ou cabeça da lista
typedef struct {
	tNo* head; // ponteiro para o primeiro nó (como no seu exemplo)
	tNo* tail; // ponteiro para o último nó (como no seu exemplo)
	int size; // quantidade de elementos na lista (tamanho)
} tLista;

void inicializar(tLista *lista);
	// prepara a lista para ser usada, definindo head/tail como NULL e size como 0

int estaVazia(tLista *lista);
	// verifica se a lista esta vazia
	// retorna 1 (verdadeiro) se a lista esta vazia (size == 0)
	// retorna 0 (falso) se a lista contem elementos

tContato lerContato();
	// funçãozinha auxiliar para ler os dados de um novo contato do teclado
	// retorna uma struct tContato preenchida

int inserirOrdenado(tLista *lista, tContato novoContato);
	// insere um novo contato na lista, mantendo a ordem crescente de CPF
	// usa a função 'compararCPF' para achar a posição correta.
	// retorna 1 se a insercao deu certo (conseguiu alocar memoria)
	// retorna 0 se a insercao deu errado (erro no malloc ou CPF duplicado)

int removerPorPosicao(tLista *lista, int pos);
	// remove um contato da lista com base na sua posicao (1, 2, 3...)
	// trata os casos de remocao no inicio, meio e fim.
	// retorna 1 se a remocao deu certo
	// retorna 0 se a remocao deu errado (posicao invalida ou lista vazia)

void consultarPorPosicao(tLista *lista, int pos);
	// busca um contato na lista pela sua posicao (1, 2, 3...)
	// imprime os dados do contato na tela se encontrado
	// imprime uma mensagem de erro se a posicao for invalida

void listarTodos(tLista *lista);
	// imprime na tela o conteudo completo da lista (igual ao 'imprimeFila' do trabalho anteior)
	// exibe todos os dados do contato e os enderecos de memoria (ant, atual, prox)
	// se a lista estiver vazia, imprime uma mensagem.

int compararCPF(const char* cpf1, const char* cpf2);
	// funcao auxiliar para comparar dois CPFs (strings), baseada slide do semestre passado
	// retorna < 0 se cpf1 vem ANTES de cpf2
	// retorna 0 se cpf1 e IGUAL a cpf2
	// retorna > 0 se cpf1 vem DEPOIS de cpf2
	
void liberarLista(tLista *lista);
	// libera toda a memoria alocada para os nós da lista
	// e reseta o header para o estado de "lista vazia"