#include "TadGrafo.h"
#include <stdio.h>
#include <stdlib.h>
#define INFINITO 999999

#define FIN_CICLO -1
#define false 0
#define true 1

/**
  * A função grafoInit devolve um novo grafo com vértices 0 1 .. V-1 e nenhum arco.
  */

Grafo grafoInit(int V) {
   Grafo G = malloc(sizeof *G);
   G->V = V;
   G->A = 0;
   G->visitados = malloc(sizeof(int)*G->V);
   G->adj = MatrizInt( V, V, 0);
   return G;
}

/**
  * A função MatrizInt aloca uma matriz com linhas 0..r-1 e colunas 0..c-1.
  * Cada elemento da matriz recebe valor val.
  */

float **MatrizInt( int r, int c, float val) {
   Vertice i, j;
   float **m = malloc( r * sizeof (float *));
   if( m == NULL){
        printf("\n\tErro ao alocar memoria!!!.\n");
        return NULL;
   }

   for (i = 0; i < r; i++)
      m[i] = malloc( c * sizeof (float));
   for (i = 0; i < r; i++)
      for (j = 0; j < c; j++)
         m[i][j] = val;
   return m;
}

/**
  * A função insereArestaGrafo insere um arco v-w no digrafo G.
  * A função supõe que v e w são distintos, positivos e menores que G->V. Se o digrafo já tem arco v-w, a função não faz nada.
  */

void insereArestaGrafo( Grafo G, Vertice v, Vertice w, float peso) {
   if (G->adj[v][w] == 0) {
      G->adj[v][w] = peso;
      G->adj[w][v] = peso;
      G->A++;
   }
}

/**
  * Para cada vértice v do digrafo G, esta função imprime, em uma linha, todos os vértices adjacentes a v.
  */

void imprimirGrafo( Grafo G) {
    Vertice v, w;
    for (v = 0; v < G->V; v++) {
        printf("\n\t");
        for (w = 0; w < G->V; w++){
            if (G->adj[v][w] != 0)
                printf( "[%f]", G->adj[v][w]);
            else
                printf("[0]");
        }
    }
}

/**
  * Lê um arquivo, com os dados de um grafo, com um determinado padrão para armazenar em uma estrutura de dados
  */
Grafo leGrafo(char *nomeArq){
    int  x, y;
    float z;
    int ordem;

    FILE *arq = fopen(nomeArq, "r");

    if(arq == NULL){
        return NULL;
    }
    fscanf(arq,"%d",&ordem);

    Grafo G = grafoInit(ordem);

    while(!feof(arq)){
        fscanf(arq,"%d %d %f\n",&x, &y, &z);
        --x;
        --y;
        //printf("%d %d %f\n",x, y, z);
        insereArestaGrafo(G, x, y, z);
    }

    fclose(arq);
    return G;
}

void vizinhos(Grafo G, Vertice v){
    int i;
    printf("\n\t");
    for( i = 0; i < G->V; i++){
        if(G->adj[v - 1][i] != 0)
            printf(" %d", i+1);
    }
    printf("\n");
}

int dijkstra(Grafo grafo, int vertice){
    int i, j, *fix;
    fix= malloc (sizeof(int)*(grafo->V));
    grafo->rot = malloc (sizeof(int)*(grafo->V));
    grafo->dt = malloc (sizeof(float)*(grafo->V));
    for(i=0; i<grafo->V; i++){
        fix[i] = 0;
        grafo->dt[i] = INFINITO;
    }
    grafo->dt[vertice] = 0;
    fix[0]=0;

    for(j = (grafo->V); j > 0; j--){
        int num = -1;
        for(i=0; i < grafo->V; i++)
            if(!fix[i] && (num==-1 || grafo->dt[i] < grafo->dt[num]))
                num = i;
        fix[num] = 1;

        if(grafo->dt[num] == INFINITO){
            break;
        }
        for(i=0; i<grafo->V; i++)

            if((grafo->dt[i] > grafo->dt[num]+grafo->adj[num][i]) && (grafo->adj[num][i] != 0)){
                if(grafo->adj[num][i]<0){
                    printf("\n\tErro, Peso negativo na aresta \n\n");
                    return 0;
                }
                grafo->dt[i] = grafo->dt[num]+grafo->adj[num][i];
                grafo->rot[i] = num;
            }
    }
}

void toda_menor_distancia(Grafo grafo, int a){
    int i,j=0;
    if(a <=0 || a > grafo->V){
        printf("\n\tvertice inexistente\n");
        return;
    }
    a--;
    if(dijkstra(grafo,a)==0)
        return;
    for (i=0; i<grafo->V; i++){
        j=i;
        printf("\n\tA menor distancia do vertice %d ao %d eh %f",a+1,j+1,grafo->dt[j]);
        printf("\n\tPassando pelos vertices...\n");
        printf("\t%d ",j+1);
        while(grafo->dt[j]>0){
            printf("%d ",grafo->rot[j]+1);
            j=grafo->rot[j];
        }
        printf("\n\n");
    }
}

/**
 * Atribui um numero de ordem pre[x] a um vertice x; o kesimo visitado recebe o numero de ordem k.
 **/
void Grafodfs( Grafo G, int n, int v){
    int conta, pre[n],i;
    conta = 0;
    for (i = 0; i < G->V; i++)
        pre[i] = -1;  // inicializa indicando nao marcados com -1

    for ( i = 0; i < G->V; i++){
        if(pre[i] == -1){  // se nao eh marcado chama busca p marcar
            dfsR(G, v, pre,&conta);
        }
    }
    printf("\n\tA sequencia de vertices visitados foi:\n");
     for ( i = 0; i < G->V; i++){
        if(pre[i]!= -1){  // se ja foi visitado
                printf("\t|%d|\n",pre[i]+1);
            }
     }
}

void dfsR( Grafo G, int v, int *pre, int *conta){
    int w; // vizinho
    pre[v] = (*conta)++; // vertice inicial
    for( w = 0; w < G->V; w++){
        if(G->adj[v][w] != 0 && pre[w] == -1){  //se forem vizinhos e nao foram marcados
            dfsR(G, w, pre,conta);  // chamada recursiva pra percorrer todos
        }
        else if(G->adj[v][w] != 0 && pre[w] != -1)
            printf("\n\taresta de retorno %d %d \n",v+1,w+1);
    }
}

void liberaGrafo(Grafo G){
    int i;
    for ( i = 0; i < G->V; i++){
        free(G->adj[i]);
    }
    free(G->dt);
    free(G->rot);
    free(G->visitados);
    free(G->adj);
}

int Grau( Grafo G, int vertice){
    int j, cont = 0;
     if (vertice<0 || vertice> G->V){
        printf("\n Vertice nao existe neste grafo");
        return ;
    }

    for (j=0; j < G->V; j++){
       if (G->adj[vertice-1][j] != 0){
        cont++;
       }
    }

   return cont;
}

void circuitoNegativo(Grafo G){
    float **dist;
    int i, j, k;
    dist = (float**) malloc(G->V* sizeof(float*));
    for(i = 0; i < G->V; i++)
        dist[i] = (float*) malloc(sizeof(float)*G->V);

    for (i = 0; i < G->V; i++)
        for (j = 0; j < G->V; j++)
            dist[i][j] = G->adj[i][j];

    for (k = 0; k < G->V; k++)
        for (i = 0; i < G->V; i++)
            for (j = 0; j < G->V; j++)
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];

    for (i = 0; i < G->V; i++){
        for (j = 0; j < G->V; j++){
            if( i == j){
                if (dist[i][j] < 0){
                    printf("\n\tPossui circuito negativo\n");
                    return;
                }
            }
        }
    }
    printf ("\n\tNão Possui circuito negativo\n");
}

int *encontrarCiclo( Grafo G,int vertice, int n){
     int v,i2,j;
     Grafo G2 = grafoInit(G->V);
     G2->V = G->V;
     G2->A = G->A;

    for ( i2 = 0; i2 < G->V ; i2++){
        for ( j = 0; j < G->V ; j++){
            G2->adj[i2][j] = G->adj[i2][j];
        }
    }

     int *ciclo = malloc(sizeof(int[n*n + 1]));

     ciclo[0] = FIN_CICLO;

     v = vertice;

     int i = 0;

     do{
         int j = 0;

         while (G2->adj[v][j] == 0 || dentroDeCiclo(ciclo, j)){
               j++;

               while (j == n){
                  i--;
                  if (i < 0) return NULL;
                  else if (i == 0){
                      v = vertice;
                  }
                  else{
                      v = ciclo[i-1];
                  }
                  j = ciclo[i] + 1;
                  ciclo[i] = FIN_CICLO;
                  //mostrarCiclo(ciclo);
               }
         }

         v = j;
         ciclo[i] = v;
         ciclo[i+1] = FIN_CICLO;
         i++;
         //mostrarCiclo(ciclo);
         if (i >= n*n) return NULL;

     }while(v != vertice || i<=2);

     return ciclo;
}

int EhEuleriano(Grafo G){
    int v, w, grau=0, impar1,impar2;
    int pares=0;
    int impares=0;
    int grau2[G->V + 1];

    impar1 = 0; impar2 = 0;
    for (v = 1; v <= G->V; v++) { // vendo o grau de todos os vertices do grafo
        grau = Grau(G,v);
        if(grau%2 != 0){
            impares++;
            grau2[v]=-1;
        }

    }

// Marcando quem sao os vertices de grau impar
       v = 1;
       if (impares == 2){
             while ((impar1 == 0)||(impar2 == 0)){
                  if (grau2[v] == -1){
                   if (impar1 == 0){
                    impar1 = v;
                   }
                   else impar2 = v;
                  }
             v++;
             }
       }

// Definindo a existencia ou nao de um Circuito ou Caminho Euleriano
            if (impares == 0){
             printf("\n\tTodos os vertices possuem grau par, portanto existe uma cadeia Euleriana fechada que eh: \n");
             int *ciclo = encontrarCiclo(G, 1, G->V);
                   // printf("ciclo inicial: \n");
                    mostrarCiclo(ciclo);

            }
            else{
                  printf("\n\tExiste(m) %i vertice(s) com grau impar, o que impossibilita a existencia de uma cadeia Euleriana fechada.\n", impares);
            }

            printf("\n");
}

int dentroDeCiclo(int *ciclo, int vertice){
    int enCiclo = false;

    int k = 0;

    while (ciclo[k] != FIN_CICLO && !enCiclo){
          if (vertice == ciclo[k]) enCiclo = true;
          k++;
    }

    return enCiclo;
}

void mostrarCiclo(int *ciclo){
    int i;
    printf("\n\t");
    for ( i=0; ciclo[i]!=FIN_CICLO; i++){
            printf("%d ",ciclo[i]+1);
        }
      printf("%d",ciclo[0]+1);
    printf("\n");
}

void Articulacao (Grafo grafo,int v){
    int i, j,ordem;

    if(v<0 || v>grafo->V){
        printf("\n\tVertice inexistente\n");
        return;
    }
    v--;


    ordem = grafo->V;
    Grafo grafo_aux = grafoInit(ordem);

    grafo_aux->num_componentes_conexas = 0;


    for(i = 0; i < grafo->V; i++){
        for(j = 0; j < grafo->V; j++)
            grafo_aux->adj[i][j] = grafo->adj[i][j];
    }

    for(i=0; i<grafo->V; i++){
        grafo_aux->adj[i][v] = 0;
        grafo_aux->adj[v][i] = 0;
    }

    if(grafo->num_componentes_conexas==0)
        Busca_Profundidade(grafo, 1,7);

    if(v==0){
        Busca_Profundidade(grafo_aux, 2,7);                   //se o vertice de verificaçao é o 1, a busca inicia com o 2.
        grafo_aux->num_componentes_conexas--;               //Tira-se um, para excluir a busca do próprio vertice dado.
    }
    else{
        Busca_Profundidade(grafo_aux, 1,7);                   //se o vertice de verificaçao não é o 1, a busca inicia com o 1.
        grafo_aux->num_componentes_conexas--;               //Tira-se um, para excluir a busca do próprio vertice dado.
    }

    if((grafo->num_componentes_conexas) < grafo_aux->num_componentes_conexas)  // +1 caracteriza o proprio vertice que fica desconexo
        printf("\n\tO vertice %d eh uma articulacao.\n", v+1);
    else
        printf("\n\tO vertice %d nao eh uma articulacao.\n", v+1);
}

void Busca(Grafo Grafo,int v,int op){
    int vizinho;

    Grafo->visitados[v]=1;
    printf ("\t%d", v+1);
    for(vizinho=0; vizinho<Grafo->V; vizinho++){
        if(Grafo->adj[v][vizinho]!=0 && Grafo->visitados[vizinho]==0){
            printf("\n\t|\n");
            Busca(Grafo,vizinho,op);
        }
        if(op==9)
            if(Grafo->adj[v][vizinho]!=0 && Grafo->visitados[vizinho]!=0)
                printf("\n\tAresta de retorno %d %d",v+1,vizinho+1);
    }
}

void Busca_Profundidade(Grafo Grafo, int v, int op){
    int i, j;
    if(v<0 || v>Grafo->V){
        printf("\nvertice inexistente\n");
        return;
    }
    v--;
    for(i=0; i<Grafo->V; i++)
        Grafo->visitados[i]=0;

    if(Grafo->visitados[v]==0)
    {
        if(op!=9)
            Grafo->num_componentes_conexas++;
        Busca(Grafo, v,op);
    }

    printf ("\n\t_____________\n");
    for(i=0; i<Grafo->V; i++)
    {
        if (Grafo->visitados[i]==0)
        {
            if(op!=9)
                Grafo->num_componentes_conexas++;
            Busca(Grafo, i,op);
            printf ("\n\t_____________\n");
        }
    }
}

void ordena (Titem* A, int n){
  int i, j;
  int h = 1;
  Titem aux;

  do h = h * 3 + 1; while (h < n);
  do
  {
    h = h/3;
    for( i = h ; i < n ; i++ )
    {
      aux = A[i]; j = i;
      while (A[j - h].grau < aux.grau)
      {
        A[j] = A[j - h]; j -= h;
        if (j < h) break;
      }
      A[j] = aux;
    }
  } while (h != 1);
  return;
}

void Independente(Grafo G){
    int k,aux,i,j,n,alpha=0,vetS[G->V], conjuntoN=G->V;
    Titem vertices[G->V];
    n=G->V;

 for(j = 0; j<G->V; j++)
        {
            vertices[j].grau=0;
            vertices[j].index=0;
            vertices[j].marca=-1;
            vetS[j]=-1;
        }
    for (i = 0; i<G->V; i++){
 for(j = 0; j<G->V; j++)
        {
           if (G->adj[i][j] !=0 ){
                vertices[i].grau=vertices[i].grau++;
                vertices[i].index=i;
           }
        }
    }
    ordena(vertices,n);
    aux=0;
    for(k=0;k<G->V;k++){
        if(vertices[aux].marca==-1){
                vetS[vertices[aux].index]=aux;
                vertices[aux].marca=0;
                  for(i = 0; i<G->V; i++)
                    {
                       if (G->adj[aux][i] !=0 ){
                            vertices[i].marca=i;
                            //printf("\n vizinho %d",i );
                            n--;
                       }
                    }
                    alpha++;
        }
        aux++;
    }

    for(i=0;i<G->V;i++){
        if (vetS[i]!=-1){ printf("\n\tItem do conjunto: %d",vetS[i]+1 );}

    }

    printf("\n\tALFA:  %d",alpha);

    return;
}



