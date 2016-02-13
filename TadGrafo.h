/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIA:
 * A estrutura grafo representa um grafo.
 * O campo adj é um ponteiro para a matriz de adjacência do grafo.
 * O campo V contém o número de vértices e o campo A contém o número de arestas do grafo.
 */

/* Tipo dos vertices são referenciados como Vertice */
#define Vertice int

struct grafo {
   int V;
   int A;
   float **adj;
   float *dt;
   int *rot;
   int *visitados;
   int num_componentes_conexas;
};

typedef struct item
{
    int grau;
    int index;
    int marca;
}Titem;


/* Ponteiro para um grafo */
typedef struct grafo *Grafo;


/* Protótipos dos métodos usados no trabalho */
Grafo grafoInit(int V);
float **MatrizInt( int r, int c, float val);
void insereArestaGrafo( Grafo G, Vertice v, Vertice w, float peso);
void imprimirGrafo( Grafo G);
Grafo leGrafo(char *nomeArq);
void vizinhos(Grafo G, Vertice v);  ///imprime vizinhos vertice
int dijkstra(Grafo grafo,int vertice);
void toda_menor_distancia(Grafo grafo,int a);
void Grafodfs( Grafo G, int n, int v);
void dfsR( Grafo G, int v, int *pre, int *conta);
int Grau( Grafo G, int vertice);
void circuitoNegativo(Grafo G);
int *encontrarCiclo( Grafo G,int vertice, int n);
int EhEuleriano(Grafo G);
int dentroDeCiclo(int *ciclo, int vertice);
void mostrarCiclo(int *ciclo);
void Articulacao (Grafo grafo,int v);
void Busca(Grafo Grafo,int v,int op);
void Busca_Profundidade(Grafo Grafo, int v, int op);
void ordena (Titem* A, int n);
void Independente(Grafo G);
