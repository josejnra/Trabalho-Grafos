/**
* Trabalho da disciplina Teoria e Modelo de Grafos - Ciência da Computação - UFV
* Autores - José Nunes e Juliana Rezende
* Foi utilizado fdsafdo seguinte repositório como referência para algumas funções
* http://www.ime.usp.br/~pf/algoritmos_para_grafos/
*/


#include <stdio.h>
#include <stdlib.h>
#include "TadGrafo.h"
#include "Lista.h"
#define TAMNOMEARQ 50

int main(){
    char nomeArquivo[TAMNOMEARQ];
    Grafo matrizGrafo;
    Digraph listagrafo;
    int cod, grafoCarregado = 0;
    int i;
    Vertice vertice, verticeB;

    do{
        printf("\n\t|----------    Menu de Opcoes    ---------------|");
        printf("\n\t|1)                               Carregar grafo|");
        printf("\n\t|2)                               Ordem do grafo|"); 
        printf("\n\t|3)                             Tamanho do grafo|");
        printf("\n\t|4)                       Vizinhos de um vertice|");
        printf("\n\t|5)                           Grau de um vertice|");
        printf("\n\t|6)              Verificar se grafo eh bipartido|");
        printf("\n\t|7)       Verificar se um vertice eh articulacao|");
        printf("\n\t|8)             Verificar se uma aresta eh ponte|");
        printf("\n\t|9)                        Busca em profundidade|");
        printf("\n\t|10)                            Busca em largura|");
        printf("\n\t|11)                         Componentes conexas|");
        printf("\n\t|12)                    Distancia/Caminho minimo|");
        printf("\n\t|13)             Ocorrencia de circuito negativo|");
        printf("\n\t|14)                      Arvore geradora minima|");
        printf("\n\t|15)                   Verificar se eh Euleriano|");
        printf("\n\t|16)         Determinar um conjunto independente|");
        printf("\n\t|17)                              Imprimir grafo|");
        printf("\n\t|18)                    Digite zero(0) para sair|");
        printf("\n\t|-----------------------------------------------|\n");
        printf("\n\tSelcione uma opcao: ");
        scanf("%d", &cod);

        if (cod >= 1 && cod <= 17){
            system("cls || clear");
            switch (cod) {
                case 1:
                    if(grafoCarregado){
                        liberaLista(listagrafo);
                        //liberaGrafo(matrizGrafo);
                        printf("\n\tGrafo desalocado da memoria\n");
                        grafoCarregado = 0;
                    }
                    do{
                        printf("\n\tInforme o nome do arquivo(com extensao): ");
                        setbuf(stdin, NULL);
                        gets(nomeArquivo);
                        printf("\n\tLendo arquivo, aguarde...\n");
                        listagrafo = leGrafoL(nomeArquivo);
                        if(listagrafo == NULL){
                            printf("\n\tArquivo nao encontrado, digite novamente!\n");
                        }
                    }while(listagrafo == NULL);
                    matrizGrafo = leGrafo(nomeArquivo);
                    grafoCarregado = 1;
                    break;
                case 2:
                    if(grafoCarregado)
                        printf("\n\tA ordem do grafo eh: %d\n ", listagrafo->V);
                    else
                        printf("\n\tCarregue algum arquivo de dados!\n");
                    break;
                case 3:
                    if(grafoCarregado)
                        printf("\n\tO tamanho do grafo eh: %d\n ", listagrafo->A);
                    else
                        printf("\n\tCarregue algum arquivo de dados!\n");
                    break;
                case 4:
                    if(grafoCarregado){
                        printf("\n\tInforme um vertice entre 1 e %d: ", listagrafo->V);
                        scanf("%d", &vertice);
                        if(vertice <= listagrafo->V)
                            imprimeVizinhos(listagrafo, vertice - 1);
                        else
                            printf("\n\tVertice nao pertence ao grafo.\n");
                    }else
                        printf("\n\tCarregue algum arquivo de dados!\n");
                    break;
                case 5:
                    if(grafoCarregado){
                        printf("\n\tInforme um vertice entre 1 e %d: ", listagrafo->V);
                        scanf("%d", &vertice);
                        if(vertice <= listagrafo->V)
                            printf("\n\tO grau do vertice fornecido eh: %d\n ", grauVertice(listagrafo, vertice - 1));
                        else
                            printf("\n\tVertice nao pertence ao grafo.\n");
                    }else
                        printf("\n\tCarregue algum arquivo de dados!\n");
                    break;
                case 6:
                    if(grafoCarregado){
                        if(GRAPHtwocolor(listagrafo))
                            printf("\n\tGrafo eh bipartido.\n");
                        else
                            printf("\n\tGrafo nao eh bipartido.\n");
                    }else
                        printf("\n\tCarregue algum arquivo de dados!\n");
                    break;
                case 7:
                    if(grafoCarregado){
                        printf("\n\tInforme um vertice entre 1 e %d: ", listagrafo->V);
                        scanf("%d", &vertice);
                        Articulacao(matrizGrafo, vertice);
                    }else
                        printf("\n\tCarregue algum arquivo de dados!\n");
                    break;
                case 8:
                    if(grafoCarregado){
                        printf("\n\tInforme um vertice entre 1 e %d: ", listagrafo->V);
                        scanf("%d", &vertice);
                        printf("\n\tInforme outro vertice entre 1 e %d: ", listagrafo->V);
                        scanf("%d", &verticeB);
                        if(existeAresta(listagrafo, vertice - 1, verticeB - 1) != 0)
                            GRAPHbridges(listagrafo,vertice - 1, verticeB - 1);
                            //printf("\n\tO numero de pontes total do grafo eh: %d\n ", GRAPHbridges(listagrafo,vertice, verticeB));
                        else
                            printf("\n\tNao existe tal aresta.\n");
                    }else
                        printf("\n\tCarregue algum arquivo de dados!\n");
                    break;
                case 9:
                    if(grafoCarregado){
                        printf("\n\tEntre com o vertice pra comecar a busca: ");
                        scanf("%d",&vertice);
                        if (vertice < 0 || vertice > matrizGrafo->V){
                            printf("\n\tVertice nao existe neste grafo!\n");
                            break;
                        }
                        Grafodfs(matrizGrafo, matrizGrafo->V, vertice);
                    }else
                        printf("\n\tCarregue algum arquivo de dados!\n");
                    break;
                case 10:
                    if(grafoCarregado){
                        printf("\n\tInforme um vertice entre 1 e %d: ", listagrafo->V);
                        scanf("%d", &vertice);
                        BuscaEmLargura(listagrafo, vertice - 1);
                    }else
                        printf("\n\tCarregue algum arquivo de dados!\n");
                    break;
                case 11:
                    if(grafoCarregado){
                        printf("\n\n\tO numero de componentes conexas eh: %d\n ", GRAPHcc(listagrafo));
                    }else
                        printf("\n\tCarregue algum arquivo de dados!\n");
                    break;
                case 12:
                    if(grafoCarregado){
                        printf("\n\tDigite um vertice para calcular a menor distancia dele para todos os outros: ");
                        scanf("%d",&vertice);
                        toda_menor_distancia(matrizGrafo,vertice);
                    }else
                        printf("\n\tCarregue algum arquivo de dados!\n");
                    break;
                case 13:
                    if(grafoCarregado){
                        printf("\n\tAnalisando, aguarde...\n");
                        circuitoNegativo(matrizGrafo);
                    }else
                        printf("\n\tCarregue algum arquivo de dados!\n");
                    break;
                case 14:
                    if(grafoCarregado){
                        if(GRAPHcc(listagrafo) == 1){
                            //printf("\n\n\tENTROU NO 14.\n");
                            int *vetor = (int*) malloc(listagrafo->V * sizeof(int));
                            system("cls || clear");
                            naivePrim(listagrafo, vetor);
                            free(vetor);
                        }else
                            printf("\n\tGrafo nao eh conexo.\n");
                    }else
                        printf("\n\tCarregue algum arquivo de dados!\n");
                    break;
                case 15:
                    if(grafoCarregado){
                        EhEuleriano(matrizGrafo);
                    }else
                        printf("\n\tCarregue algum arquivo de dados!\n");
                    break;
                case 16:
                    if(grafoCarregado){
                        Independente(matrizGrafo);
                    }else
                        printf("\n\tCarregue algum arquivo de dados!\n");
                    break;
                case 17:
                    if(grafoCarregado){
                        imprimeGrafoLista(listagrafo);
                        printf("\n");
                    }else
                        printf("\n\tCarregue algum arquivo de dados!\n");
                    break;
                }
                printf("\n\tPressione ENTER para continuar...");
                setbuf(stdin, NULL);
                getchar();
        }
        system("cls || clear");
    }while (cod!=0);
    liberaLista(listagrafo);

    return 0;
}
