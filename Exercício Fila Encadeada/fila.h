typedef struct{
	int dado;
	struct tipoNo* prox;
	struct tipoNo* ant;
} tipoNo;

typedef struct{
	tipoNo* head;//primeiro
	tipoNo* tail;//ultimo
	int size;//tamanho: opcional
} tFila;

void inicializar (tFila *f);

int vazia (tFila *f);//retorna 1 se a fila está vazia
					//retorna 0 se a fila é não-vazia

int inserir(tFila *f, int d);
	//retorna 1 se a insercao deu certo
	//retorna 0 se a insercao deu errado

void imprimeFila (tFila *f);
	//imprime na tela o conteudo da fila

int remover(tFila *f, int *d);
	//retorna 0 se a remocao deu certo
	//retorna 1 se a remocao deu errado
	// se a operacao deu certo, a variavel apontada por d
	//deve receber o valor removido da fila

int tamanho(tFila *f);