#include "Lista.h"
#include "Fila.h"
#include <stdio.h>
#include <stdlib.h>

#define cc bbbb
#define INFINITO 999999

/**
 * A função DIGRAPHinit devolve (o endereço de) um novo grafo com vértices 0 1 ... V-1 e nenhum arco.
 **/
Digraph DIGRAPHinit(int V) {
    Vertice v;
    Digraph G = malloc( sizeof *G);
    G->V = V;
    G->A = 0;
    G->adj = malloc( V * sizeof (link));
    for (v = 0; v < V; v++)
        G->adj[v] = NULL;
    G->bbbb = malloc( V * sizeof (int));
    G->cccc = malloc( V * sizeof (Vertice));
    return G;
}

/**
 * A função NEWnode recebe um vértice w e o endereço next de um nó e devolve o endereço a de um novo nó tal que a->w == w e a->next == next.
 **/
link NEWnode( Vertice w, link next, float peso) {
   link a = malloc( sizeof (struct node));
   a->w = w;
   a->peso = peso;
   a->next = next;
   return a;
}

/**
 * A função DIGRAPHinsetA insere um arco v-w no grafo G.
 * A função supõe que v e w são distintos, positivos, e menores que G->V.
 * Se o grafo já tem arco v-w, a função não faz nada.
 **/
void DIGRAPHinsertA(Digraph G, Vertice v, Vertice w, float peso) {
   link a;
/**/for (a = G->adj[v]; a != NULL; a = a->next)
      if (a->w == w) return;
   G->adj[v] = NEWnode( w, G->adj[v], peso);
   G->A++;
}

void liberaLista(Digraph G){
    int i;
    for(i = 0; i < G->V; i++)
        free(G->adj[i]);

    free(G);
}

void imprimeGrafoLista(Digraph G) {
    link a;
    int i;
    for (i = 0; i < G->V; i++){
        printf("\n\tVizinhos vertice %d: ", i + 1);
        for (a = G->adj[i]; a != NULL; a = a->next)
            //printf(" %d", a->w);
            printf(" %d(%f)", a->w + 1, a->peso);
        printf("\n");
    }
}

void imprimeVizinhos(Digraph G, Vertice v){
    link a;
    int i;
        printf("\n\tVizinhos do vertice %d: ", v + 1);
        for (a = G->adj[v]; a != NULL; a = a->next)
            printf(" %d", a->w + 1);
        printf("\n");
}

int grauVertice(Digraph G, Vertice v){
    int i, cont = 0;
    link a;

    for (a = G->adj[v]; a != NULL; a = a->next)
            cont++;

    return cont;
}

Digraph leGrafoL(char *nomeArq){
    int  vert, vert2;
    float peso;
    int ordem;

    FILE *arq = fopen(nomeArq, "r");

    if(arq == NULL){
        return NULL;
    }
    fscanf(arq,"%d",&ordem);

    Digraph G = DIGRAPHinit(ordem);

    while(!feof(arq)){
        fscanf(arq,"%d %d %f\n",&vert, &vert2, &peso);
        //printf("%d %d %f\n",vert - 1, vert2 - 1, peso);
        vert -= 1;
        vert2 -= 1;
        DIGRAPHinsertA(G, vert, vert2, peso);
        DIGRAPHinsertA(G, vert2, vert, peso);
    }
    G->A = G->A/2;
    fclose(arq);
    //printf("\n\tTerminou inserir na lista.\n");
    return G;
}

/** Se é Bipartido
 * Uso típico: if (GRAPHtwocolor( G) == 1) . . .
 * ---------------------------------------------
 * A função devolve 1 se o grafo G é bicolorido (bipartido) e devolve 0 em caso contrário.
 * Além disso, se G é bicolorido, a função atribui uma cor, 0 ou 1, a cada vértice de G de tal forma que toda aresta tenha pontas de cores diferentes.
 * As cores dos vértices são registradas no vetor color indexado pelos vértices. (Veja programa 18.6 de Sedgewick.)
 **/
int GRAPHtwocolor( Digraph G){
   int color[G->V];
   Vertice v;
   int c = 0;
   for (v = 0; v < G->V; v++)
      color[v] = -1;
   for (v = 0; v < G->V; v++)
      if (color[v] == -1)
         if (dfsRcolor( G, v, 0, color) == 0) return 0;
   return 1;
}

int dfsRcolor( Digraph G, Vertice v, int c, int *color){
   link a;
   color[v] = 1-c;
   for (a = G->adj[v]; a != NULL; a = a->next) {
      Vertice w = a->w;
      if (color[w] == -1) {
         if (dfsRcolor( G, w, 1-c, color) == 0) return 0;
      }
      else if (color[w] == 1-c) return 0;
   }
   return 1;
}

/**
 * A função abaixo devolve o número de componentes do grafo G.
 * Além disso, armazena no vetor G->cc o número da componente a que cada vértice pertence:
 * se o vértice v pertence à k-ésima componente então G->cc[v] == k.
 * (O código foi copiado do programa 18.4 de Sedgewick.)
 **/
int GRAPHcc( Digraph G){
    int i, j;
    link a;

    Vertice v;
    int id = 0;
    for (v = 0 ; v < G->V; v++)
        G->cc[v] = -1;
    for (v = 0; v < G->V; v++)
        if (G->cc[v] == -1)
        dfsRcc( G, v, id++);

    for(i = 0 ; i < id; i++){
        printf("\n\tComponente %d \n\t", i + 1);
        for(j = 0; j < G->V; j++){
            if(G->cc[j] == i)
                printf("%d ", j + 1);
        }
    }
    return id;
}

/**
 * A função dfsRcc marca com id todos os vértices que estão na mesma componente conexa que v.
 * (Ou seja, faz cc[w] = id para todo w que esteja na mesma componente que v.)
 * A função supõe que o grafo é representado por listas de adjacência.
 **/
void dfsRcc( Digraph G, Vertice v, int id){
   link a;
   G->cc[v] = id;
   for (a = G->adj[v]; a != NULL; a = a->next)
      if (G->cc[a->w] == -1)
         dfsRcc( G, a->w, id);
}

/**
 * A função abaixo calcula e devolve o número de pontes do grafo G.
 * Também imprime todas as pontes.
 * (O código foi inspirado no programa 18.7 de Sedgewick.)
 **/
int GRAPHbridges(Digraph G, Vertice a, Vertice b){
    int conta, i = 0, pre[G->V], numpts, low[G->V];
    Vertice parent[G->V];
    Vertice v;
    conta = numpts = 0;
    for (v = 0; v < G->V; v++)
        pre[v] = -1;
    for (v = 0; v < G->V; v++)
        if (pre[v] == -1) {
            parent[v] = v;
            bridgeR( G, v, &pre, &low, &conta, &numpts, parent, a, b, &i);
        }
    if(i == 0)
        printf("\n\tA aresta %d-%d Nao eh ponte\n", a + 1, b + 1);

    return numpts;
}

void bridgeR(Digraph G, Vertice v, int *pre, int *low, int *conta, int *numpts, Vertice *parent, Vertice c, Vertice b, int *i){
    link a;
    pre[v] = (*conta) + 1;
    low[v] = pre[v];
    for (a = G->adj[v]; a != NULL; a = a->next) {
        Vertice w = a->w;
        if (pre[w] == -1) {
            parent[w] = v;
            bridgeR( G, w, pre, low, conta, numpts, parent, c, b, i);
            if (low[v] > low[w])
                low[v] = low[w];
            if (low[w] == pre[w]) {
                (*numpts) = (*numpts) + 1;
                if((v == c && w == b) || (v == b &&  w == c)){
                    printf( "\n\tEh ponte a aresta %d-%d\n", v + 1, w + 1);
                    (*i) = 1;
                }
            }
        }
        else if (w != parent[v] && low[v] > pre[w])
            low[v] = pre[w];
    }
}

int BuscaEmLargura(Digraph G, int raiz){
    int *verticesMarcados = (int*)malloc(G->V * sizeof(int));//vetor de vertices marcados
    int tamVerticesMarcados = 0;
    int vertice1;
    link p;
    Fila *fi = cria_Fila();
    int i = 0;
    verticesMarcados[0] = raiz;//marca raiz
    tamVerticesMarcados++;

    insere_Fila(fi , raiz); //poe raiz na fila

    while(!Fila_vazia(fi)){//enquanto a fila nao esta vazia
        vertice1 = fi->inicio->vertice;//vertice que esta no inicio da fila
         p = G->adj[vertice1];// Ladj = lista de adjacencia de vertice1

        while(p != NULL){//enquanto a lista de adjacencia do vertice1 nao acaba
            if(!BuscaVertice(p->w, verticesMarcados, tamVerticesMarcados)){//busca p->vertice no vetor verticesMarcados
                verticesMarcados[tamVerticesMarcados++] = p->w;//marcou p->vertice
                printf("\n\tAresta %d-%d\n", vertice1 + 1, p->w + 1);
                i++;
                insere_Fila(fi , p->w);//poe p->vertice na fila
                //arestas que compoem arvore geradora mínima, aresta (vertice1, p->vertice)
            }
            else if(consulta_Fila(fi, p->w)){//se p->vertice pertence a F
                    printf("\n\tNao faz parte da arvore de busca em largura a aresta %d-%d \n", vertice1 + 1, p->w + 1);
                //arestas (vertice1, p->vertice) que não compoem árvore geradora mínima
                }
            p = p->next;
        }
        remove_Fila(fi);
    }

    //printf("\n\tTotal de vertices passados %d \n", i);
    return 0;
}

int BuscaVertice(int vertice, int *vetor, int tamanhoVetor){
    int i;
    for(i = 0; i < tamanhoVetor; i++){
        if(vetor[i] == vertice)
            return 1;
    }
    return 0;
}

float retornaPeso(Digraph G, Vertice b, Vertice c){
    link a;
    for (a = G->adj[b]; a != NULL; a = a->next)
        if(a->w == c)
            return a->peso;
    return 0;
}

void naivePrim( Digraph G, Vertice parent[]) {
    FILE *arq;
    printf("\n\tGerando arquivo, aguarde...\n");
    arq = fopen("arvore geradora min.txt", "w");
    fprintf(arq, "%d\n", G->V);
    Vertice v, w, v0, w0;
    link a;
    float pesoTotal = 0;
    for (w = 0; w < G->V; w++) parent[w] = -1;
    parent[0] = 0;
    while (1) {
        double minprice = INFINITO;
        for (v = 0; v < G->V; v++)
            if (parent[v] != -1)
                for (a = G->adj[v]; a != NULL; a = a->next)
                    if (parent[a->w] == -1 && minprice > a->peso) {
                        minprice = a->peso;
                        v0 = v, w0 = a->w;
                    }
        if (minprice == INFINITO)
            break;
        /* A */
        parent[w0] = v0;
        pesoTotal += retornaPeso(G, w0, v0);
        fprintf(arq, "%d %d %f\n", w0 + 1, v0 + 1, retornaPeso(G, w0, v0));
    }
    fprintf(arq, "Peso Total %f", pesoTotal);
    printf("\n\tArquivo 'arvore geradora min.txt' gerado.\n");
    fclose(arq);
}

int existeAresta(Digraph G, Vertice a, Vertice b){
    link p;
    int i;
    for (i = 0; i < G->V; i++){
        for (p = G->adj[i]; p != NULL; p = p->next){
            if((i == a && p->w == b)|| (i == b && p->w == a))
                return 1;
        }
    }
    return 0;
}

