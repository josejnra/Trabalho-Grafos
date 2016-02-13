//Definição do tipo Fila
struct elemento{
    int vertice;
    struct elemento *prox;
};

typedef struct elemento Elem;
//Definição do Nó Descritor da Fila
struct fila{
    struct elemento *inicio;
    struct elemento *final;
    int qtd;
};

typedef struct fila Fila;

Fila* cria_Fila();
void libera_Fila(Fila* fi);
int insere_Fila(Fila* fi, int vertice);
int remove_Fila(Fila* fi);
int Fila_vazia(Fila* fi);
int tamanho_Fila(Fila* fi);
int consulta_Fila(Fila* fi, int a);
int retornaFila(Fila* fi);
