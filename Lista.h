#define Vertice int

typedef struct digraph *Digraph;

/**
  * A lista de adjacência de um vértice v é composta por nós do tipo node.
  * Cada nó da lista corresponde a um arco e contém um vizinho w de v e o endereço do nó seguinte da lista. Um link é um ponteiro para um node.
  */

typedef struct node *link;
struct node {
   Vertice w;
   float peso;
   link next;
};

/**
  * A estrutura digraph representa um digrafo.
  * O campo adj é um ponteiro para o vetor de listas de adjacência,
  * o campo V contém o número de vértices e o campo A contém o número de arcos.
  * O campo aaaa é um inteiro, o campo bbbb é um vetor de inteiros indexado pelos vértices,
  * e cccc é um vetor de vértices indexado pelos inteiros 0..V-1.
  **/
struct digraph {
   int     V;
   int     A;
   link   *adj;
   int     aaaa;
   int    *bbbb;
   Vertice *cccc;
};
/**
  * Um objeto do tipo Graph contém o endereço de um digraph.
  */

Digraph DIGRAPHinit(int V);  ///Inicia estrutura de lista de adjacência
link NEWnode( Vertice w, link next, float peso);      ///Insere um novo nó na lista de adjacência
void DIGRAPHinsertA( Digraph G, Vertice v, Vertice w, float peso);  ///insere uma nova aresta na lista
void liberaLista(Digraph G);        ///Desaloca lista de adjacência da memória
void imprimeGrafoLista(Digraph G);  ///Imprime o grafo
void imprimeVizinhos(Digraph G, Vertice v); ///Imprime Vizinhos de um vertice fornecido
int grauVertice(Digraph G, Vertice v);      ///Retorna o grau de um vertice determinado
Digraph leGrafoL(char *nomeArq);            ///Le o grafo a partir de um arquivo de entrada e armazena-o em um lista de adjacência
int GRAPHtwocolor( Digraph G);                  ///A função devolve 1 se o grafo G é bipartido
int dfsRcolor( Digraph G, Vertice v, int c, int *color);  ///Funcao secundaria para verificao do bipartido
int GRAPHcc( Digraph G);   ///Devolve o número de componentes do grafo G e informa os vertices de cada componente
void dfsRcc( Digraph G, Vertice v, int id);   ///Funcao secundária para calculo do numero de componentes
int GRAPHbridges(Digraph G, Vertice a, Vertice b);   ///Retorna o numero de pontes do grafo
void bridgeR(Digraph G, Vertice v, int *pre, int *low, int *conta, int *numpts, Vertice *parent, Vertice c, Vertice b, int *i);
int BuscaEmLargura(Digraph G, int raiz); ///Imprime as arestas da busca em largura
int BuscaVertice(int vertice, int *vetor, int tamanhoVetor);  ///Funcao auxiliar para busca em largura
float retornaPeso(Digraph G, Vertice b, Vertice c);
void naivePrim( Digraph G, Vertice parent[]);
int existeAresta(Digraph G, Vertice a, Vertice b);
